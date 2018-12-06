#include "Buffer.h"


Buffer::Buffer(GLfloat * data, unsigned int count, GLuint numComponents)
	:m_numComponents(numComponents)
{
	glGenBuffers(1, &m_ID);
	glBindBuffer(GL_ARRAY_BUFFER, m_ID);

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
	glDeleteBuffers(1, &m_ID);
}
