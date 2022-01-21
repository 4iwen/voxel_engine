#include "GLVertexArray.h"

GLVertexArray::GLVertexArray()
{
	glGenVertexArrays(1, &_rendererID);
}

GLVertexArray::~GLVertexArray()
{
	glDeleteVertexArrays(1, &_rendererID);
	_rendererID = 0;
}

void GLVertexArray::Bind() const
{
	glBindVertexArray(_rendererID);
}

void GLVertexArray::Unbind() const
{
	glBindVertexArray(0);
}

void GLVertexArray::AddVertexBuffer(const Ref<GLVertexBuffer>& vertexBuffer)
{
	DEBUGBREAK(vertexBuffer->GetLayout().GetElements().size());

	glBindVertexArray(_rendererID);
	vertexBuffer->Bind();

	const auto& layout = vertexBuffer->GetLayout();
	for (const auto& element : layout)
	{
		switch (element.Type)
		{
			case GLShaderDataType::Float:
			case GLShaderDataType::Float2:
			case GLShaderDataType::Float3:
			case GLShaderDataType::Float4:
			{
				glEnableVertexAttribArray(_vertexBufferIndex);
				glVertexAttribPointer(_vertexBufferIndex,
					element.GetComponentCount(),
					GLUtils::GetBaseTypeFromGLShaderDataType(element.Type),
					element.Normalized ? GL_TRUE : GL_FALSE,
					layout.GetStride(),
					(const void*)element.Offset);
				_vertexBufferIndex++;
				break;
			}
			case GLShaderDataType::Int:
			case GLShaderDataType::Int2:
			case GLShaderDataType::Int3:
			case GLShaderDataType::Int4:
			case GLShaderDataType::Bool:
			{
				glEnableVertexAttribArray(_vertexBufferIndex);
				glVertexAttribIPointer(_vertexBufferIndex,
					element.GetComponentCount(),
					GLUtils::GetBaseTypeFromGLShaderDataType(element.Type),
					layout.GetStride(),
					(const void*)element.Offset);
				_vertexBufferIndex++;
				break;
			}
			case GLShaderDataType::Mat3:
			case GLShaderDataType::Mat4:
			{
				uint8_t count = element.GetComponentCount();
				for (uint8_t i = 0; i < count; i++)
				{
					glEnableVertexAttribArray(_vertexBufferIndex);
					glVertexAttribPointer(_vertexBufferIndex,
						count,
						GLUtils::GetBaseTypeFromGLShaderDataType(element.Type),
						element.Normalized ? GL_TRUE : GL_FALSE,
						layout.GetStride(),
						(const void*)(element.Offset + sizeof(float) * count * i));
					DEBUGBREAK(element.Divisor == 1);
					glVertexAttribDivisor(_vertexBufferIndex, 1);
					_vertexBufferIndex++;
				}
				break;
			}
		default:
			DEBUGBREAK(false);
		}
	}

	_vertexBuffers.push_back(vertexBuffer);
}

void GLVertexArray::SetIndexBuffer(const Ref<GLIndexBuffer>& indexBuffer)
{
	glBindVertexArray(_rendererID);
	indexBuffer->Bind();

	_indexBuffer = indexBuffer;
}
