#include "GLVertexBuffer.h"

GLVertexBuffer::GLVertexBuffer(const void* vertices, uint32_t size, GLBufferUsageHint bufferUsage)
{
	glGenBuffers(1, &_rendererID);

	SetData(vertices, size, bufferUsage);
}

GLVertexBuffer::~GLVertexBuffer()
{
	glDeleteBuffers(1, &_rendererID);
	_rendererID = 0;
}

void GLVertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, _rendererID);
}

void GLVertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GLVertexBuffer::SetData(const void* data, uint32_t size)
{
	glBindBuffer(GL_ARRAY_BUFFER, _rendererID);
	glBufferData(GL_ARRAY_BUFFER, size, data, _usage);
}

void GLVertexBuffer::SetData(const void* data, uint32_t size, GLBufferUsageHint bufferUsage)
{
	_usage = bufferUsage;

	SetData(data, size);
}
