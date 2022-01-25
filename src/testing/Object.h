#pragma once

#include "../core/Base.h"
#include <glad/glad.h>
#include "../rendering/GL/GL.h"

class Object
{
public:
	static Ref<GLVertexArray> create(float vertices[], unsigned int indices[]);
};