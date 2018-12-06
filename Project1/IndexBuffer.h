#pragma once
#include <glad/glad.h>

class IndexBuffer
{
public:
	IndexBuffer(GLuint* data, unsigned int count);
	void Bind();
	void Unbind();
	unsigned int getCount();
	~IndexBuffer();
private:
	//OpenGL ID for this buffer
	GLuint m_ID;
	//Number of items in this buffer
	unsigned int m_count;
};

