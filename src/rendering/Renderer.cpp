#include "../window/Window.h"
#include "../shader/Shader.h"
#include "../camera/Camera.h"
#include "Renderer.h"
#include <windows.h>

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
}

void Renderer::get_max_vertex_count()
{
    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    printf("Maximum of vertex attributes supported: %i\n", nrAttributes);
}

void Renderer::loop()
{
    const char* glsl_version = "#version 330"; // tell imgui what version of glsl are we using

    Window main_window(1280, 720, "voxel engine"); // create window
    Shader main_shader(Shader::default_vertex_shader_source, Shader::default_fragment_shader_source); // create shader

    main_shader.create_program(); // create our program

    printf("Using renderer: %s\n", glGetString(GL_RENDERER));

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // set color for clearing the screen
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // GL_LINE -> wireframe | GL_FILL -> fill  
    main_shader.use(); // use our program we created

    get_max_vertex_count();

    IMGUI_CHECKVERSION();
    ImGui::CreateContext(); // setup imgui context
    ImGuiIO& io = ImGui::GetIO(); (void)io; // imgui io settings

    ImGui::StyleColorsDark(); // apply imgui theme

    ImGui_ImplGlfw_InitForOpenGL(main_window.window_handle, true); // imgui glfw init
    ImGui_ImplOpenGL3_Init(glsl_version); // imgui opengl init

    while (!glfwWindowShouldClose(main_window.window_handle)) // check if window is closed -> stop rendering, exit
    {
        main_window.process_input(main_window.window_handle); // handle input

        glClear(GL_COLOR_BUFFER_BIT); // clear with the set color ( glClearColor )

        for (size_t i = 0; i < 2; i++)
        {
            glm::mat4 transform = glm::mat4(1.0f);
            transform = glm::translate(transform, glm::vec3(-0.5f + i, 0.0f, 0.0f)); // move
            transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(1.0f, 1.0f, 1.0f)); // rotate

            main_shader.set_mat4("transform", transform);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0); // opengl drawing
        }


        ImGui_ImplOpenGL3_NewFrame(); // imgui frame setup
        ImGui_ImplGlfw_NewFrame();    // 

        ImGui::NewFrame(); // start new imgui drawing area
        draw_debug_window(); // draw imgui stuff

        ImGui::Render();                                        // pass all imgui things to imgui render
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData()); //

        glfwSwapBuffers(main_window.window_handle); // swap front and back buffers (double buffering) -> computer will render one whole frame in the background, then just display it -> makes some screen tearing disappear
        glfwPollEvents();
    }

    // cleanup
    ImGui_ImplOpenGL3_Shutdown(); //
    ImGui_ImplGlfw_Shutdown();    // destroy imgui context
    ImGui::DestroyContext();      //

    glfwDestroyWindow(main_window.window_handle); // glfw cleanup
    glfwTerminate();                               //
}