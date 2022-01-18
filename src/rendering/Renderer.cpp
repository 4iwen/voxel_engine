#include "../window/Window.h"
#include "Renderer.h"
#include "../../RenderTriangles.h"

Renderer::Renderer()
{
	loop();
}

void Renderer::loop()
{
    unsigned int chunks_loaded = 0;
    unsigned int voxels_loaded = 0;
    const char* glsl_version = "#version 130";

    Window* main_window = new Window(1280, 720, "voxel engine");

    RenderTriangles* rend = new RenderTriangles();
    rend -> RenderTriangle();

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(main_window->window_handle, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, rend->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rend->vertices), rend->vertices, GL_STATIC_DRAW);

    while (!glfwWindowShouldClose(main_window->window_handle))
    {
        glfwSwapBuffers(main_window->window_handle);
        main_window->process_input(main_window->window_handle);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();

        ImGui::NewFrame();
        ImGui::ShowDemoWindow();

        ImGui::SetNextWindowSize(ImVec2(0, 0), ImGuiCond_Once);
        ImGui::Begin("debug", NULL, ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::Text("fps: %.1f", ImGui::GetIO().Framerate);
        ImGui::Text("chunks loaded: %u", chunks_loaded);
        ImGui::Text("voxels loaded: %u", voxels_loaded);
        ImGui::End();
        ImGui::EndFrame();

        ImGui::Render();
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(rend-> shaderProgram);
        glBindVertexArray(rend-> VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(main_window->window_handle);
    glfwTerminate();
}