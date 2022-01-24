#include "GLRendererAPI.h"

#include "GLVertexArray.h"

void GLRendererAPI::Init()
{

}

void GLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{
	glViewport(x, y, width, height);
}

void GLRendererAPI::SetClearColor(glm::vec4 color)
{
	glClearColor(color.x, color.y, color.z, color.w);
}

void GLRendererAPI::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void GLRendererAPI::DrawIndexed(const Ref<GLVertexArray> vertexArray, uint32_t indexCount)
{
	vertexArray->Bind();
	uint32_t count = indexCount != 0 ? indexCount : vertexArray->GetIndexBuffer()->GetCount();
	glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
}
