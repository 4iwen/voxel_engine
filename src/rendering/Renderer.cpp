#include "../window/Window.h"
#include "Renderer.h"
#include <glad/glad.h>
#include <iostream>

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(aPos.x , aPos.y, aPos.z, 1.0); \n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f); \n"
"}\n\0";

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

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(main_window->window_handle, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Positions of verticies.
    GLfloat vertices[] =
    {
        -0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
    };

    // Creates a vertex shader.
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Creates a fragment shader.
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << infoLog << std::endl;
    }

    // Creates a shader program.
    GLuint shaderProgram = glCreateProgram();
    glUseProgram(shaderProgram);
    // Attaches our vertex and fragment shader into the program shader.
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    // Links the program shader into the scene.
    glLinkProgram(shaderProgram);

    // Deletes the now unused shaders.
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // I forgor :skull:.
    GLuint VAO, VBO;

    // VERY IMPORTANT !!! VAO ALWAYS FIRST !!! VERY IMPORTANT
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    //Enables
    glEnableVertexAttribArray(0);

    // VERY IMPORTANT !!! BUFFER ALWAYS FIRST !!! VERY IMPORTANT
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glClearColor(0.0f, 1.0f, 0.0f, 1.0f);

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

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
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