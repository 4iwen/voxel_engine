#pragma once

#include <glad/glad.h>

#include <stdio.h>
#include <string>

class Shader
{
public:
	unsigned int program_id;

	Shader();

	void CreateProgram();
};