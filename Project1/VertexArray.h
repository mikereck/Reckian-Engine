#pragma once
#include "Buffer.h"
#include "Shader.h"

#include <vector>
class VertexArray
{
public:
	VertexArray();
	void AttachBuffer(Buffer* buffer, GLuint index);
	void AttachBuffer(Buffer* buffer, Shader& shader, char* name);
	void Bind();
	void Unbind();
	~VertexArray();
private:
	GLuint m_ID;
	std::vector<Buffer*> buffers;
};

