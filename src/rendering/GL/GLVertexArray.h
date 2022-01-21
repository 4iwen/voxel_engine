#pragma once

#include <vector>
#include "GLBase.h"

#include "GLVertexBuffer.h"
#include "GLIndexBuffer.h"

class GLVertexArray
{
public:
	GLVertexArray();
	~GLVertexArray();

	void Bind() const;
	void Unbind() const;

	void AddVertexBuffer(const Ref<GLVertexBuffer>& vertexBuffer);
	void SetIndexBuffer(const Ref<GLIndexBuffer>& indexBuffer);

	const std::vector<Ref<GLVertexBuffer>>& GetVertexBuffers() const { return _vertexBuffers; }
	const Ref<GLIndexBuffer>& GetIndexBuffer() const { return _indexBuffer; }
private:
	uint32_t _rendererID;
	uint32_t _vertexBufferIndex = 0;
	std::vector<Ref<GLVertexBuffer>> _vertexBuffers;
	Ref<GLIndexBuffer> _indexBuffer;
};
