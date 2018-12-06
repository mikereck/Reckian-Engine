#pragma once
#include "Buffer.h"
#include "Shader.h"

#include <vector>
class VertexArray
{
public:
	VertexArray();
	//Attach the provided buffer to the input index provided in the current shader
	void AttachBuffer(Buffer* buffer, GLuint index);
	//Attach the provided buffer to the variable with the provided name in the provided shader
	void AttachBuffer(Buffer* buffer, Shader& shader, char* name);
	void Bind();
	void Unbind();
	~VertexArray();
private:
	//OpenGL ID for the Vertex Shader
	GLuint m_ID;

	//Stores a pointer to the provided buffers so that any attached buffers can be deleted when the Vertex Array is deleted
	std::vector<Buffer*> m_buffers;
};

