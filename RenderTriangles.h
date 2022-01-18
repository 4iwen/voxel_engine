#pragma once
#include<stdio.h>
class RenderTriangles
{
public:
	 void RenderTriangle();
	 GLfloat vertices;
	 GLuint shaderProgram;
	 GLuint VAO, VBO;
};

