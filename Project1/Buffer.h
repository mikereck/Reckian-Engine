#pragma once
#include <glad/glad.h>

class Buffer
{
public:
	Buffer(GLfloat* data, unsigned int count, GLuint numComponents);
	void Bind();
	void Unbind();
	GLuint getNumComponents();
	~Buffer();
private:
	GLuint m_ID;
	GLuint m_numComponents;
};

