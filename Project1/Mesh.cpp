#include "Mesh.h"


Mesh::Mesh(Shader* shader) : m_shader(shader)
{
}

void Mesh::createPlane()
{
	//Unite square centered on (0,0,0) with the normal facing -z
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

	//Create and assign values to the Vertex Buffer (VBO) and Element Buffer (EBO)
	VBO = new Buffer(vertices, 4, 3);
	EBO = new IndexBuffer(indices, 6);

	//Attach the Vertex Buffer to the Vertex Array
	VAO.AttachBuffer(VBO, 0);

	//set the loaded bool to true to allow for rendering
	m_loaded = true;
}

void Mesh::createSphere()
{

}

void Mesh::draw(glm::vec3 color, glm::vec3 position, glm::vec3 scale)
{
	//Check to see if a mesh has been loaded before rendering
	if (m_loaded)
	{
		//enable the shader for this mesh
		m_shader->use();
		//bind the vertex array and the element buffer
		VAO.Bind();
		EBO->Bind();

		//Create  the transform matrix described by the provided position and scale
		glm::mat4 MVMatrix;
		MVMatrix = glm::translate(MVMatrix, position);
		MVMatrix = glm::scale(MVMatrix,scale);


		//Send the transform matrix and the color to the shader as uniforms
		glUniform3f(glGetUniformLocation(m_shader->ID, "color"), color.x, color.y, color.z);
		glUniformMatrix4fv(glGetUniformLocation(m_shader->ID, "MVMatrix"), 1, GL_FALSE, glm::value_ptr(MVMatrix));

		//Drawthe shape to the screen
		glDrawElements(GL_TRIANGLES, EBO->getCount(), GL_UNSIGNED_INT, 0);

		//Unbind the vertex array and the element buffer
		EBO->Unbind();
		VAO.Unbind();
	}
}



Mesh::~Mesh()
{
	//Since the element buffer is stored as a pointer, we need to delete it when the Mesh object is deleted
	delete EBO;
}
