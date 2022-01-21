#pragma once

#include <cstdint>
#include "glad/glad.h"
#include "../../core/Base.h"

enum GLBufferUsageHint : uint32_t
{
    StaticDraw = GL_STATIC_DRAW,
    DynamicDraw = GL_DYNAMIC_DRAW,
    StreamDraw = GL_STREAM_DRAW,
};

enum GLShaderDataType
{
    Float,
    Float2,
    Float3,
    Float4,

    Mat3,
    Mat4,

    Int,
    Int2,
    Int3,
    Int4,

    Bool,
};

static class GLUtils
{
public:
    static GLenum GetBaseTypeFromGLShaderDataType(GLShaderDataType dataType)
    {
        switch (dataType)
        {
        case GLShaderDataType::Float: return GL_FLOAT;
        case GLShaderDataType::Float2: return GL_FLOAT;
        case GLShaderDataType::Float3: return GL_FLOAT;
        case GLShaderDataType::Float4: return GL_FLOAT;

        case GLShaderDataType::Mat3: return GL_FLOAT;
        case GLShaderDataType::Mat4: return GL_FLOAT;

        case GLShaderDataType::Int: return GL_INT;
        case GLShaderDataType::Int2: return GL_INT;
        case GLShaderDataType::Int3: return GL_INT;
        case GLShaderDataType::Int4: return GL_INT;

        case GLShaderDataType::Bool: return GL_BOOL;
        }

        DEBUGBREAK(false);
        return 0;
    }

    static GLsizei GetGLShaderDataTypeSize(GLShaderDataType type)
    {
        switch (type)
        {
        case GLShaderDataType::Float: return sizeof(float);
        case GLShaderDataType::Float2: return sizeof(float) * 2;
        case GLShaderDataType::Float3: return sizeof(float) * 3;
        case GLShaderDataType::Float4: return sizeof(float) * 4;

        case GLShaderDataType::Mat3: return sizeof(float) * 3 * 3;
        case GLShaderDataType::Mat4: return sizeof(float) * 4 * 4;

        case GLShaderDataType::Int: return sizeof(int);
        case GLShaderDataType::Int2: return sizeof(int) * 2;
        case GLShaderDataType::Int3: return sizeof(int) * 3;
        case GLShaderDataType::Int4: return sizeof(int) * 4;

        case GLShaderDataType::Bool: return sizeof(bool);
        }

        DEBUGBREAK(false);
        return 0;
    }
};
