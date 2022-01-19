#include "Objects.h"
#include <glad/glad.h>

unsigned int VBO, VAO, EBO;

float _vertices[] = {
	 0.5f,  0.5f, 0.0f,  // top right   
	 0.5f, -0.5f, 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f,  // bottom left 
	-0.5f,  0.5f, 0.0f   // top left    
};

unsigned int _indices[] = {  // note that we start from 0!
	0, 1, 3,   // first triangle
	1, 2, 3    // second triangle
};


Objects::Objects()
{
	create_vertex_buffer_object();
	create_vertex_array_object();
	create_entity_buffer_object();

	glEnableVertexAttribArray(0);

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
}

void Objects::create_entity_buffer_object()
{
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indices), _indices, GL_STATIC_DRAW);
}