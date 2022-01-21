#pragma once

#include "GLBase.h"

#include "GLBufferLayout.h"

class GLVertexBuffer
{
public:
	GLVertexBuffer(const void* vertices, uint32_t size, GLBufferUsageHint bufferUsage = GLBufferUsageHint::StaticDraw);
	~GLVertexBuffer();

	void Bind() const;
	void Unbind() const;

	void SetData(const void* data, uint32_t size);
	void SetData(const void* data, uint32_t size, GLBufferUsageHint bufferUsage);
	const GLBufferLayout& GetLayout() const { return _layout; }
	void SetLayout(const GLBufferLayout& layout) { _layout = layout; }
private:
	uint32_t _rendererID;
	GLBufferUsageHint _usage;
	GLBufferLayout _layout;
};

