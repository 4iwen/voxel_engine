#pragma once

#include <glad/glad.h>

#include <stdio.h>
#include <string>
#include <vector>

class Shader
{
public:
	unsigned int program_id;

	Shader(const char* vertex_shader_source, const char* fragment_shader_source);

	void create_program();

private:
	const char* _vertex_shader_source;
	const char* _fragment_shader_source;

	unsigned int create_vertex_shader(const char* vertex_shader_source);
	unsigned int create_fragment_shader(const char* fragment_shader_source);
	void check_vertex_shader(unsigned int vertex_shader);
	void check_fragment_shader(unsigned int fragment_shader);
};