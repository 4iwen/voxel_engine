#include "../window/Window.h"
#include "../shader/Shader.h"
#include "../camera/Camera.h"
#include "../gui/Gui.h"
#include "Renderer.h"
#include "../core/Base.h"
#include "GL/GL.h"

Renderer::Renderer()
{

}

const char* GetGLErrorStr(GLenum err)
{
    switch (err)
    {
    case GL_NO_ERROR:          return "No error";
    case GL_INVALID_ENUM:      return "Invalid enum";
    case GL_INVALID_VALUE:     return "Invalid value";
    case GL_INVALID_OPERATION: return "Invalid operation";
    case GL_STACK_OVERFLOW:    return "Stack overflow";
    case GL_STACK_UNDERFLOW:   return "Stack underflow";
    case GL_OUT_OF_MEMORY:     return "Out of memory";
    default:                   return "Unknown error";
    }
}

void CheckGLError()
{
    while (true)
    {
        const GLenum err = glGetError();
        if (GL_NO_ERROR == err)
            break;

        printf("GL Error: %s\n", GetGLErrorStr(err));
    }
}

void Renderer::loop()
{
    Window main_window(1280, 720, "voxel engine"); // assing window variables
    main_window.create(); // create the window

    glfwSwapInterval(1); // vsync | 1 -> enabled | 0 -> disabled

    float triverts[] = {
        0.0f, 0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
    };
    uint32_t triinds[] = { 0,1,2 };

    Ref<GLVertexBuffer> vb = CreateRef<GLVertexBuffer>(triverts, 9 * sizeof(float));
    Ref<GLIndexBuffer> ib = CreateRef<GLIndexBuffer>(triinds, 3);
    Ref<GLVertexArray> va = CreateRef<GLVertexArray>();
    vb->SetLayout(GLBufferLayout({ BufferElement(GLShaderDataType::Float3, "position") }));
    va->SetIndexBuffer(ib);
    va->AddVertexBuffer(vb);
    va->Unbind();
    GLRendererAPI rapi = GLRendererAPI();

    Shader main_shader(Shader::default_vertex_shader_source, Shader::default_fragment_shader_source); // create shader
    main_shader.create_program(); // create our program
    main_shader.use(); // use our program we created

    Camera main_camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)); // create our 3d camera
    main_camera.setup(main_window.window_handle);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // set color for clearing the screen
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // GL_LINE -> wireframe | GL_FILL -> fill 
    //glPointSize(5);

    Gui::init(main_window.window_handle); // initialize imgui

    while (!glfwWindowShouldClose(main_window.window_handle)) // check if window is closed -> stop rendering, exit
    {
        glClear(GL_COLOR_BUFFER_BIT); // clear with the set color ( glClearColor ) -> ALWAYS CLEAR

        main_camera.update(main_window.window_handle, main_shader);

        for (unsigned int i = 0; i < 1; i++)
        {
            for (unsigned int j = 0; j < 1; j++)
            {
                glm::mat4 transform = glm::mat4(1.0f);                                                 //
                transform = glm::translate(transform, glm::vec3(0.0f + j, 0.0f, 0.0f + i));            // transform object
                transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(1.0f, 2.0f, 3.0f)); //
                main_shader.set_mat4("transform", transform);                                          //

                glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0); // opengl drawing
            }
        }

        GLint sus;
        glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &sus);
        main_shader.set_mat4("transform", glm::mat4(1));
        rapi.DrawIndexed(va);
        glBindVertexArray(sus);

        CheckGLError();

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