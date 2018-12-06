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
	GLuint m_ID;
	unsigned int m_count;
};

