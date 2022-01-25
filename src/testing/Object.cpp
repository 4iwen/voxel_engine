#include "Object.h"

Ref<GLVertexArray> Object::create(float vertices[], unsigned int indices[])
{
	Ref<GLVertexBuffer> vb = CreateRef<GLVertexBuffer>(vertices, (sizeof(vertices) / sizeof(vertices[0])) * sizeof(float));
	Ref<GLIndexBuffer> ib = CreateRef<GLIndexBuffer>(indices, (sizeof(indices) / sizeof(indices[0])));
	Ref<GLVertexArray> va = CreateRef<GLVertexArray>();
	vb->SetLayout(GLBufferLayout({ BufferElement(GLShaderDataType::Float3, "position") }));
	va->SetIndexBuffer(ib);
	va->AddVertexBuffer(vb);
	va->Unbind();

	return va;
}