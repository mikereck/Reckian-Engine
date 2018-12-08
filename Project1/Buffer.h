#pragma once
#include <glad/glad.h>
#include <iostream>

class Buffer
{
public:
	Buffer(GLfloat* data, unsigned int count, GLuint numComponents);
	void Bind();
	void Unbind();
	GLuint getNumComponents();
	~Buffer();
private:
	//The OpenGL buffer ID for this buffer
	GLuint m_ID;

	//Number of components per item in the buffer
	GLuint m_numComponents;
};

