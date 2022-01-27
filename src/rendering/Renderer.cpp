#include "../window/Window.h"
#include "../shader/Shader.h"
#include "../camera/Camera.h"
#include "../testing/Object.h"
#include "../gui/Gui.h"
#include "Renderer.h"

Renderer::Renderer()
{

}

void Renderer::loop()
{
    Window main_window(1280, 720, "voxel engine"); // assing window variables
    main_window.create(); // create the window

    Shader main_shader(Shader::default_vertex_shader_source, Shader::default_fragment_shader_source); // create shader
    main_shader.create_program(); // create our programA
    main_shader.use(); // use our program we created

    Camera main_camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)); // create our 3d camera
    main_camera.setup(main_window.window_handle);
    
    Ref<GLVertexArray> va = Object::create(); // create our cube and then link it with opengl

    GLRendererAPI api = GLRendererAPI();

    api.SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f)); // set color for clearing the screen
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // GL_LINE -> wireframe | GL_FILL -> fill | GL_POINT -> dots

    Gui::init(main_window.window_handle); // initialize imgui

    while (!glfwWindowShouldClose(main_window.window_handle)) // check if window is closed -> stop rendering, exit
    {
        api.Clear(); // clear with the set color

        if (Window::show_mouse)
        {
            glfwSetInputMode(main_window.window_handle, GLFW_CURSOR, GLFW_CURSOR_NORMAL); // show the cursor
        }
        else if (!Window::show_mouse)
        {
            glfwSetInputMode(main_window.window_handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // hide the cursor
            main_camera.update(main_window.window_handle, main_shader);
        }

        for (unsigned int i = 0; i < 10; i++)
        {
            for (unsigned int j = 0; j < 10; j++)
            {
                for (unsigned int k = 0; k < 10; k++)
                {
                    glm::mat4 transform = glm::mat4(1.0f);                                                 //
                    transform = glm::translate(transform, glm::vec3(0.0f + i, 0.0f + j, 0.0f + k));        // transform object
                    transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(1.0f, 2.0f, 3.0f)); //
                    main_shader.set_mat4("transform", transform);

                    api.DrawIndexed(va);
                }
            }                                
        }

        Gui::new_frame();
        ImGui::ShowDemoWindow();
        Gui::draw_debug_window(); // draw imgui stuff
        Gui::render(); // render imgui stuff

        glfwSwapBuffers(main_window.window_handle); // swap front and back buffers (double buffering) -> computer will render one whole frame in the background, then just display it -> makes some screen tearing disappear
        glfwPollEvents();//cause im a island boy and ive been tryna make it
    }

    Gui::cleanup();
    glfwDestroyWindow(main_window.window_handle); // glfw cleanup
    glfwTerminate();                              //
}