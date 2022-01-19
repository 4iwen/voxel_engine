#include "../window/Window.h"
#include "../shader/Shader.h"
#include "Renderer.h"

const char* vertex_shader_source =
"#version 330 core\n"

"layout (location = 0) in vec3 position;\n"

"void main()\n"
"{\n"
"   gl_Position = vec4(position, 1.0);\n"
"}\0";

const char* fragment_shader_source =
"#version 330 core\n"

"out vec4 FragColor; \n"

"void main()\n"
"{\n"
"    FragColor = vec4(1.0f, 0.0f, 0.1f, 1.0f);\n"
"}\0";

Renderer::Renderer()
{
	loop();
}

void Renderer::draw_debug_window()
{
    unsigned int chunks_loaded = 0;
    unsigned int voxels_loaded = 0;

    ImGui::SetNextWindowSize(ImVec2(0, 0), ImGuiCond_Once);
    ImGui::Begin("debug", NULL, ImGuiWindowFlags_AlwaysAutoResize);
    ImGui::Text("fps: %.1f", ImGui::GetIO().Framerate);
    ImGui::Text("chunks loaded: %u", chunks_loaded);
    ImGui::Text("voxels loaded: %u", voxels_loaded);
    ImGui::End();
    ImGui::EndFrame();
}

void Renderer::loop()
{
    const char* glsl_version = "#version 330";

    Window* main_window = new Window(1280, 720, "voxel engine"); // create window
    Shader* main_shader = new Shader(vertex_shader_source, fragment_shader_source); // create shader
    main_shader->create_program();

    printf("Using renderer: %s", glGetString(GL_RENDERER));

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // GL_LINE -> wireframe | GL_FILL -> fill 
    glUseProgram(main_shader->program_id);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(main_window->window_handle, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    while (!glfwWindowShouldClose(main_window->window_handle))
    {
        main_window->process_input(main_window->window_handle);

        glClear(GL_COLOR_BUFFER_BIT);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();

        ImGui::NewFrame();
        ImGui::ShowDemoWindow();

        draw_debug_window();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(main_window->window_handle);
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(main_window->window_handle);
    glfwTerminate();
}