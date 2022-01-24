#include "GLIndexBuffer.h"

GLIndexBuffer::GLIndexBuffer(const uint32_t* indices, uint32_t count, GLBufferUsageHint bufferUsage)
{
	glGenBuffers(1, &_rendererID);

	SetData(indices, count, bufferUsage);
}

GLIndexBuffer::~GLIndexBuffer()
{
	glDeleteBuffers(1, &_rendererID);
	_rendererID = 0;
}

void GLIndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _rendererID);
}

void GLIndexBuffer::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void GLIndexBuffer::SetData(const uint32_t* indices, uint32_t count)
{
	_count = count;

	glBindBuffer(GL_ARRAY_BUFFER, _rendererID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(uint32_t) * count, indices, (uint32_t)_usage);
}

void GLIndexBuffer::SetData(const uint32_t* indices, uint32_t count, GLBufferUsageHint bufferUsage)
{
	_usage = bufferUsage;

	SetData(indices, count);
}
