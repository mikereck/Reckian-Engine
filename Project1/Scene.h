#pragma once
#include "PhysObject.h"
#include "Shader.h"

#include <vector>

class Scene
{
public:
	Scene(Shader* shader);

	void addPhysObj(Mesh* mesh, glm::vec3 position = glm::vec3(0, 0, 0), float scale = 1, glm::vec3 color = glm::vec3(1, 0, 0), float mass = 1, glm::vec3 velocity = glm::vec3(0, 0, 0), glm::vec3 accel = glm::vec3(0, 0, 0));

	~Scene();
private:
	Shader* m_shader;

	std::vector<PhysObject*> m_physObjs;
};

