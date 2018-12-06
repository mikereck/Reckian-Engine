#include "IndexBuffer.h"



IndexBuffer::IndexBuffer(GLuint * data, unsigned int count)
	:m_count(count)
{
	//Generate the buffer ID for this buffer
	glGenBuffers(1, &m_ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);

	//Store data in the buffer and unbind it
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void IndexBuffer::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
}

void IndexBuffer::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

GLuint IndexBuffer::getCount()
{
	return m_count;
}


IndexBuffer::~IndexBuffer()
{
	//Make sure that the OpenGL reference to this buffer is cleared when this buffer is deleted
	glDeleteBuffers(1, &m_ID);
}
