#include "../objects/Objects.h"
#include "Shader.h"

unsigned int program_id;

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
    unsigned int vertex_shader = create_vertex_shader(_vertex_shader_source);       // 
    check_vertex_shader(vertex_shader);                                             // compile both shaders, 
    unsigned int fragment_shader = create_fragment_shader(_fragment_shader_source); // check for compile errors
    check_fragment_shader(fragment_shader);                                         //

    glAttachShader(program_id, vertex_shader);   // attach both shaders to our program
    glAttachShader(program_id, fragment_shader); //
    glLinkProgram(program_id); // link our program with opengl

    glDeleteShader(vertex_shader);   // delete both shaders cuz we already attached them
    glDeleteShader(fragment_shader); //

    new Objects(); // create our triangle and then link it with opengl
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