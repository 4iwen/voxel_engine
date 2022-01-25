#include "../window/Window.h"
#include "../shader/Shader.h"
#include "../camera/Camera.h"
#include "../testing/Object.h"
#include "../gui/Gui.h"
#include "Renderer.h"

float vertices[] =
{
    // pos			
   -0.5f, -0.5f, -0.5f, // bottom left  front
    0.5f, -0.5f, -0.5f, // bottom right front
   -0.5f,  0.5f, -0.5f, // top    left  front
    0.5f,  0.5f, -0.5f, // top    right front

   -0.5f, -0.5f,  0.5f, // bottom left  back
    0.5f, -0.5f,  0.5f, // bottom right back
   -0.5f,  0.5f,  0.5f, // top    left  back
    0.5f,  0.5f,  0.5f, // top    right back
};

unsigned int indices[] =
{
    // always start from 0
    0, 1, 3, // front side
    0, 2, 3, //

    4, 5, 7, // back side
    4, 6, 7, //

    0, 5, 1, // bottom side
    0, 4, 5, //

    2, 7, 3, // top side
    2, 6, 7, // 

    0, 4, 6, // left side
    0, 2, 6, // 

    1, 5, 7, // right side
    1, 3, 7, // 
};

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
    
    Ref<GLVertexArray> va = Object::create(vertices, indices); // create our cube and then link it with opengl

    GLRendererAPI api = GLRendererAPI();

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // set color for clearing the screen
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // GL_LINE -> wireframe | GL_FILL -> fill | GL_POINT -> dots

    Gui::init(main_window.window_handle); // initialize imgui

    while (!glfwWindowShouldClose(main_window.window_handle)) // check if window is closed -> stop rendering, exit
    {
        glClear(GL_COLOR_BUFFER_BIT); // clear with the set color ( glClearColor ) -> ALWAYS CLEAR

        main_camera.update(main_window.window_handle, main_shader);

        for (unsigned int i = 0; i < 16; i++)
        {
            for (unsigned int j = 0; j < 16; j++)
            {   
                glm::mat4 transform = glm::mat4(1.0f);                                                 //
                transform = glm::translate(transform, glm::vec3(0.0f + j, 0.0f, 0.0f + i));            // transform object
                transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(1.0f, 2.0f, 3.0f)); //
                main_shader.set_mat4("transform", transform);                                          //
        
                api.DrawIndexed(va);
                glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0); // opengl drawing
            }
        }

        //GLint sus;
        //glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &sus);
        //main_shader.set_mat4("transform", glm::mat4(1));
        //glBindVertexArray(sus);

        Gui::new_frame();
        Gui::draw_debug_window(); // draw imgui stuff
        Gui::render(); // render imgui stuff

        glfwSwapBuffers(main_window.window_handle); // swap front and back buffers (double buffering) -> computer will render one whole frame in the background, then just display it -> makes some screen tearing disappear
        glfwPollEvents();
    }

    Gui::cleanup();
    glfwDestroyWindow(main_window.window_handle); // glfw cleanup
    glfwTerminate();                              //
}