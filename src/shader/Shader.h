#pragma once

#include <glad/glad.h>

#include <stdio.h>
#include <string>
#include <vector>

class Shader
{
public:
	unsigned int program_id;

	static const char* default_vertex_shader_source;
	static const char* default_fragment_shader_source;

	Shader(const char* vertex_shader_source, const char* fragment_shader_source);

	void create_program();
	void use();
	void set_bool(const std::string& name, bool value) const;
	void set_int(const std::string& name, int value) const;
	void set_float(const std::string& name, float value) const;

private:
	const char* _vertex_shader_source;
	const char* _fragment_shader_source;

	unsigned int create_vertex_shader(const char* vertex_shader_source);
	unsigned int create_fragment_shader(const char* fragment_shader_source);
	void check_vertex_shader(unsigned int vertex_shader);
	void check_fragment_shader(unsigned int fragment_shader);
};