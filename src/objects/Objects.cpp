#include "Objects.h"
#include <glad/glad.h>

unsigned int VBO, VAO, EBO;

float _vertices[] = {
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

unsigned int _indices[] = {  
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


Objects::Objects()
{
	create_vertex_buffer_object();
	create_vertex_array_object();
	create_entity_buffer_object();

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Objects::create_vertex_buffer_object()
{
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(_vertices), _vertices, GL_STATIC_DRAW);
}

void Objects::create_vertex_array_object()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void Objects::create_entity_buffer_object()
{
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indices), _indices, GL_STATIC_DRAW);
}