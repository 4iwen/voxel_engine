#pragma once

#include <string>
#include <vector>
#include "GLBase.h"

struct BufferElement
{
	std::string Name;
	GLShaderDataType Type;
	uint32_t Size;
	size_t Offset;
	bool Normalized;
	uint32_t Divisor;

	BufferElement() = default;

	BufferElement(GLShaderDataType type, const std::string& name, bool normalized = false)
		: Name(name), Type(type), Size(GLUtils::GetGLShaderDataTypeSize(type)), Offset(0), Normalized(normalized), Divisor(1)
	{
	}

	uint32_t GetComponentCount() const
	{
		switch (Type)
		{
			case GLShaderDataType::Float:   return 1;
			case GLShaderDataType::Float2:  return 2;
			case GLShaderDataType::Float3:  return 3;
			case GLShaderDataType::Float4:  return 4;
			// they get handled on a differnt place while adding them to vertex array
			case GLShaderDataType::Mat3:    return 3; // 3* float3
			case GLShaderDataType::Mat4:    return 4; // 4* float4

			case GLShaderDataType::Int:     return 1;
			case GLShaderDataType::Int2:    return 2;
			case GLShaderDataType::Int3:    return 3;
			case GLShaderDataType::Int4:    return 4;

			case GLShaderDataType::Bool:    return 1;
		}

		DEBUGBREAK(false);
		return 0;
	}
};

class GLBufferLayout
{
public:
	GLBufferLayout() {}

	GLBufferLayout(std::initializer_list<BufferElement> elements)
		: _elements(elements)
	{
		CalculateOffsetsAndStride();
	}

	uint32_t GetStride() const { return _stride; }
	const std::vector<BufferElement>& GetElements() const { return _elements; }

	std::vector<BufferElement>::iterator begin() { return _elements.begin(); }
	std::vector<BufferElement>::iterator end() { return _elements.end(); }
	std::vector<BufferElement>::const_iterator begin() const { return _elements.begin(); }
	std::vector<BufferElement>::const_iterator end() const { return _elements.end(); }

private:
	void CalculateOffsetsAndStride()
	{
		size_t offset = 0;
		_stride = 0;
		for (auto& element : _elements)
		{
			element.Offset = offset;
			offset += element.Size;
			_stride += element.Size;
		}
	}

	std::vector<BufferElement> _elements;
	uint32_t _stride = 0;
};
