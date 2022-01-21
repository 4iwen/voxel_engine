#pragma once

#include "glm.hpp"
#include "GLBase.h"

#include "GLVertexArray.h"

class GLRendererAPI
{
public:
	void Init();

	void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
	void SetClearColor(glm::vec4 color);
	void Clear();

	void DrawIndexed(const Ref<GLVertexArray> vertexArray, uint32_t indexCount = 0);
};

