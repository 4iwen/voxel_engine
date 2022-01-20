#include "../objects/Objects.h"
#include "Shader.h"

unsigned int program_id;

const char* Shader::default_vertex_shader_source =
"#version 330 core\n"

"layout (location = 0) in vec3 position;\n"

"uniform mat4 transform;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"
 
"void main()\n"
"{\n"
"   gl_Position = projection * view * transform * vec4(position, 1.0);\n"
"}\0";

const char* Shader::default_fragment_shader_source =
"#version 330 core\n"

"out vec4 FragColor;\n"

"void main()\n"
"{\n"
"    FragColor = vec4(0.15f, 0.85f, 0.15f, 1.0f);\n"
"}\0";

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

void Shader::use()
{
    glUseProgram(program_id);
}

void Shader::set_bool(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(program_id, name.c_str()), (int)value);
}

void Shader::set_int(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(program_id, name.c_str()), value);
}

void Shader::set_float(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(program_id, name.c_str()), value);
}

void Shader::set_vec2(const std::string& name, const glm::vec2& value) const
{
    glUniform2fv(glGetUniformLocation(program_id, name.c_str()), 1, &value[0]);
}

void Shader::set_vec2(const std::string& name, float x, float y) const
{
    glUniform2f(glGetUniformLocation(program_id, name.c_str()), x, y);
}

void Shader::set_vec3(const std::string& name, const glm::vec3& value) const
{
    glUniform3fv(glGetUniformLocation(program_id, name.c_str()), 1, &value[0]);
}

void Shader::set_vec3(const std::string& name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(program_id, name.c_str()), x, y, z);
}

void Shader::set_vec4(const std::string& name, const glm::vec4& value) const
{
    glUniform4fv(glGetUniformLocation(program_id, name.c_str()), 1, &value[0]);
}

void Shader::set_vec4(const std::string& name, float x, float y, float z, float w) const
{
    glUniform4f(glGetUniformLocation(program_id, name.c_str()), x, y, z, w);
}

void Shader::set_mat2(const std::string& name, const glm::mat2& mat) const
{
    glUniformMatrix2fv(glGetUniformLocation(program_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::set_mat3(const std::string& name, const glm::mat3& mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(program_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::set_mat4(const std::string& name, const glm::mat4& mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(program_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
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