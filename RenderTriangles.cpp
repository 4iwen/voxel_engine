#include <glad/glad.h>
#include "RenderTriangles.h"

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



void RenderTriangles::RenderTriangle()
{
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
}