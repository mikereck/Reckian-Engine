#pragma once
#include "Shader.h"
#include "BufferInclude.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>


class Mesh
{
public:
	Mesh(Shader* shader);

	//create a unit square on the x-y plane
	void createPlane();

	//create a unit sphere centered at the origin
	void createSphere();

	//Draw the mesh to the screen
	void draw(glm::vec3 color, glm::vec3 position, glm::vec3 scale);
	~Mesh();
private:
	Shader* m_shader;
	//Vertex Array for this mesh
	VertexArray VAO;

	//Vertex Buffer for this mesh
	Buffer* VBO;

	//Element Buffer for this mesh
	IndexBuffer* EBO;

	//When true, allows the draw command to execute and draw the mesh to the screen
	bool m_loaded = false;
};

