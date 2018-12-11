#pragma once
#include "PhysObject.h"
#include "Shader.h"

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

class Scene
{
public:
	Scene(Shader* shader, glm::vec3 gravity, float gravityConst, float permitivity, float permeability);

	void addPhysObj(Mesh* mesh, glm::vec3 color = glm::vec3(1, 0, 0), glm::vec3 position = glm::vec3(0, 0, 0), float mass = 1, float charge = 0 , float scale = 1, glm::vec3 velocity = glm::vec3(0, 0, 0), glm::vec3 accel = glm::vec3(0, 0, 0));

	void physUpdate();

	glm::vec3 getCOM();

	void renderUpdate(int width, int height);

	void dumpStats();

	~Scene();
private:
	Shader* m_shader;

	glm::vec3 m_gravity;
	float m_gravityConstant;
	float m_permittivity;
	float m_permeability;

	std::vector<PhysObject*> m_physObjs;
};

