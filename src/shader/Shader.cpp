#include "Shader.h"

unsigned int program_id;

float _vertices[] = {
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left 
};
unsigned int _indices[] = {  // note that we start from 0!
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
};

const char* _vertex_shader_source; 
const char* _fragment_shader_source;

Shader::Shader(const char* vertex_shader_source, const char* fragment_shader_source)
{
    program_id = glCreateProgram();
    _vertex_shader_source = vertex_shader_source;
    _fragment_shader_source = fragment_shader_source;
}

void Shader::create_program()
{
    unsigned int vertex_shader = create_vertex_shader(_vertex_shader_source);
    check_vertex_shader(vertex_shader);
    unsigned int fragment_shader = create_fragment_shader(_fragment_shader_source);
    check_fragment_shader(fragment_shader);

    glAttachShader(program_id, vertex_shader); // attach both shaders
    glAttachShader(program_id, fragment_shader);
    glLinkProgram(program_id);

    glDeleteShader(vertex_shader); // delete both shaders cuz we already attached them
    glDeleteShader(fragment_shader);

    unsigned int VBO, VAO, EBO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(_vertices), _vertices, GL_STATIC_DRAW); // create vertex buffer object

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indices), _indices, GL_STATIC_DRAW); 

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

unsigned int Shader::create_vertex_shader(const char* vertex_shader_source)
{
    unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
    glCompileShader(vertex_shader);

    return vertex_shader;
}

unsigned int Shader::create_fragment_shader(const char* fragment_shader_source)
{
    unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
    glCompileShader(fragment_shader);

    return fragment_shader;
}

void Shader::check_vertex_shader(unsigned int vertexShader)
{
    int vertexSuccess;
    char vertexInfoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertexSuccess);
    if (!vertexSuccess)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, vertexInfoLog);
        printf("Vertex shader compilation failed:\n%s", vertexInfoLog);
    }
}

void Shader::check_fragment_shader(unsigned int fragmentShader)
{
    int fragmentSuccess;
    char fragmentInfoLog[512];
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragmentSuccess);
    if (!fragmentSuccess)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, fragmentInfoLog);
        printf("Fragment shader compilation failed:\n%s", fragmentInfoLog);
    }
}