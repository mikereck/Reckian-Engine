#pragma once
#include "Mesh.h"
#include <glm/glm.hpp>

class PhysObject
{
public:
	PhysObject(Mesh* mesh, glm::vec3 position = glm::vec3(0,0,0), float scale = 1, glm::vec3 color = glm::vec3(1, 0, 0));
	void draw();
	~PhysObject();
private:
	Mesh* m_mesh;

	//physics variables
	glm::vec3 m_position;

	//drawing variables
	float m_scale;
	glm::vec3 m_color;


};

