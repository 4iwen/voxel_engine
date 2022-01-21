#pragma once

#include "GLBase.h"

class GLIndexBuffer
{
public:
	GLIndexBuffer(const uint32_t* indices, uint32_t size, GLBufferUsageHint bufferUsage = GLBufferUsageHint::StaticDraw);
	~GLIndexBuffer();

	void Bind() const;
	void Unbind() const;

	void SetData(const uint32_t* indices, uint32_t size);
	void SetData(const uint32_t* indices, uint32_t size, GLBufferUsageHint bufferUsage);

	uint32_t GetCount() { return _count; }
private:
	uint32_t _rendererID;
	uint32_t _count;
	GLBufferUsageHint _usage;
};

