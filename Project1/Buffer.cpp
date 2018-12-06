#include "Buffer.h"


Buffer::Buffer(GLfloat * data, unsigned int count, GLuint numComponents)
	:m_numComponents(numComponents)
{
	//generate the buffer ID for this buffer
	glGenBuffers(1, &m_ID);
	glBindBuffer(GL_ARRAY_BUFFER, m_ID);

	//Store provided data in the provided buffer
	glBufferData(GL_ARRAY_BUFFER, count * numComponents * sizeof(float), data, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void Buffer::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_ID);
}

void Buffer::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

GLuint Buffer::getNumComponents()
{
	return m_numComponents;
}


Buffer::~Buffer()
{
	//Make sure that the buffer reference is removed when this buffer is deleted
	glDeleteBuffers(1, &m_ID);
}
