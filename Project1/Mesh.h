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
	void createPlane();
	void createSphere();
	void draw(glm::vec3 color, glm::vec3 position, glm::vec3 scale);
	~Mesh();
private:
	Shader* m_shader;

	VertexArray VAO;
	Buffer* VBO;
	IndexBuffer* EBO;

	bool m_loaded = false;
};

