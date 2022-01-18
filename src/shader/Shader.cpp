#include "Shader.h"

unsigned int program_id;

std::vector<float> _vertices;
const char* _vertex_shader_source; 
const char* _fragment_shader_source;

Shader::Shader(std::vector<float> vertices, const char* vertex_shader_source, const char* fragment_shader_source)
{
    _vertices = vertices;
    _vertex_shader_source = vertex_shader_source;
    _fragment_shader_source = fragment_shader_source;
}

void Shader::create_program(std::vector<float> vertices)
{
    unsigned int vertex_shader = create_vertex_shader(_vertex_shader_source);
    check_vertex_shader(vertex_shader);
    unsigned int fragment_shader = create_fragment_shader(_fragment_shader_source);
    check_fragment_shader(fragment_shader);

    program_id = glCreateProgram();

    glAttachShader(program_id, vertex_shader); // attach both shaders
    glAttachShader(program_id, fragment_shader);
    glLinkProgram(program_id);

    glDeleteShader(vertex_shader); // delete both shaders cuz we already attached them
    glDeleteShader(fragment_shader);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW); // create vertex buffer object

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
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