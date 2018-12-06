#include "VertexArray.h"



VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_ID);
}

void VertexArray::AttachBuffer(Buffer* buffer, GLuint index)
{
	buffers.push_back(buffer);

	Bind();
	buffer->Bind();

	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, buffer->getNumComponents(), GL_FLOAT, GL_FALSE, 0, 0);

	buffer->Unbind();
	Unbind();
}

void VertexArray::AttachBuffer(Buffer * buffer, Shader& shader, char * name)
{
	buffers.push_back(buffer);

	Bind();
	buffer->Bind();

	GLuint index = glGetAttribLocation(shader.ID, name);

	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, buffer->getNumComponents(), GL_FLOAT, GL_FALSE, 0, 0);

	buffer->Unbind();
	Unbind();
}

void VertexArray::Bind()
{
	glBindVertexArray(m_ID);
}

void VertexArray::Unbind()
{
	glBindVertexArray(0);
}

VertexArray::~VertexArray()
{
	for (int i = 0; i < buffers.size(); i++)
		delete buffers[i];
	glDeleteVertexArrays(1, &m_ID);
}
