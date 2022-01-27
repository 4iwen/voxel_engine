#include "Object.h"

float vertices[] =
{
    // pos			
   -0.5f, -0.5f, -0.5f, // bottom left  front
    0.5f, -0.5f, -0.5f, // bottom right front
   -0.5f,  0.5f, -0.5f, // top    left  front
    0.5f,  0.5f, -0.5f, // top    right front

   -0.5f, -0.5f,  0.5f, // bottom left  back
    0.5f, -0.5f,  0.5f, // bottom right back
   -0.5f,  0.5f,  0.5f, // top    left  back
    0.5f,  0.5f,  0.5f, // top    right back
};

unsigned int indices[] =
{
    // always start from 0
    0, 1, 3, // front side
    0, 2, 3, //

    4, 5, 7, // back side
    4, 6, 7, //

    0, 5, 1, // bottom side
    0, 4, 5, //

    2, 7, 3, // top side
    2, 6, 7, // 

    0, 4, 6, // left side
    0, 2, 6, // 

    1, 5, 7, // right side
    1, 3, 7, // 
};

Ref<GLVertexArray> Object::create()
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