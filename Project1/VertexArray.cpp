#include "VertexArray.h"



VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_ID);
}

void VertexArray::AttachBuffer(Buffer* buffer, GLuint index)
{
	//Push the buffer pointer onto our vector for storage
	m_buffers.push_back(buffer);

	//Bind the vertex array and provided buffer
	Bind();
	buffer->Bind();

	//std::cout << "Attaching Buffer to " << index << std::endl;

	//Attach the buffer to the provided index
	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, buffer->getNumComponents(), GL_FLOAT, GL_FALSE, 0, 0);

	//Unbind everything
	buffer->Unbind();
	Unbind();
}

void VertexArray::AttachBuffer(Buffer * buffer, Shader& shader, char * name)
{
	//Push the buffer pointer onto our vector for storage
	m_buffers.push_back(buffer);

	//Bind the vertex array and provided buffer
	Bind();
	buffer->Bind();

	//Find the index of the attribute with the provided name
	GLuint index = glGetAttribLocation(shader.ID, name);

	//Attach the buffer to the attribute
	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, buffer->getNumComponents(), GL_FLOAT, GL_FALSE, 0, 0);

	//Unbind everything
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
	for (int i = 0; i < m_buffers.size(); i++)
		delete m_buffers[i];
	glDeleteVertexArrays(1, &m_ID);
}
