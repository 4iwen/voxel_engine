#pragma once

#include <glad/glad.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

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
	void set_vec2(const std::string& name, const glm::vec2& value) const;
	void set_vec2(const std::string& name, float x, float y) const;
	void set_vec3(const std::string& name, const glm::vec3& value) const;
	void set_vec3(const std::string& name, float x, float y, float z) const;
	void set_vec4(const std::string& name, const glm::vec4& value) const;
	void set_vec4(const std::string& name, float x, float y, float z, float w) const;
	void set_mat2(const std::string& name, const glm::mat2& mat) const;
	void set_mat3(const std::string& name, const glm::mat3& mat) const;
	void set_mat4(const std::string& name, const glm::mat4& mat) const;

private:
	const char* _vertex_shader_source;
	const char* _fragment_shader_source;

	unsigned int create_vertex_shader(const char* vertex_shader_source);
	unsigned int create_fragment_shader(const char* fragment_shader_source);
	void check_vertex_shader(unsigned int vertex_shader);
	void check_fragment_shader(unsigned int fragment_shader);
};