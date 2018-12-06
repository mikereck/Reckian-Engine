#include "Mesh.h"


Mesh::Mesh(Shader* shader) : m_shader(shader)
{
}

void Mesh::createPlane()
{
	m_shader->use();
	float vertices[] =
	{
		-0.5, -0.5, 0,
		-0.5,  0.5, 0,
		 0.5,  0.5, 0,
		 0.5, -0.5, 0
	};

	unsigned int indices[] =
	{
		0, 1, 2,
		2, 3, 0
	};

	VBO = new Buffer(vertices, 4, 3);
	EBO = new IndexBuffer(indices, 6);
	VAO.AttachBuffer(VBO, 0);

	m_loaded = true;
}

void Mesh::createSphere()
{

}

void Mesh::draw(glm::vec3 color, glm::vec3 position, glm::vec3 scale)
{
	if (m_loaded)
	{
		m_shader->use();
		VAO.Bind();
		EBO->Bind();

		glm::mat4 MVMatrix;
		MVMatrix = glm::translate(MVMatrix, position);
		MVMatrix = glm::scale(MVMatrix,scale);

		glUniform3f(glGetUniformLocation(m_shader->ID, "color"), color.x, color.y, color.z);
		glUniformMatrix4fv(glGetUniformLocation(m_shader->ID, "MVMatrix"), 1, GL_FALSE, glm::value_ptr(MVMatrix));
		glDrawElements(GL_TRIANGLES, EBO->getCount(), GL_UNSIGNED_INT, 0);

		EBO->Unbind();
		VAO.Unbind();
	}
}



Mesh::~Mesh()
{
	delete EBO;
}
