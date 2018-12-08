#include "Scene.h"

Scene::Scene(Shader * shader) 
	: m_shader(shader)
{
}

void Scene::addPhysObj(Mesh * mesh, glm::vec3 position, float scale, glm::vec3 color, float mass, glm::vec3 velocity, glm::vec3 accel)
{
	m_physObjs.push_back(new PhysObject(mesh, position, scale, color, mass, velocity, accel));
}

Scene::~Scene()
{
	for (int i = 0; i < m_physObjs.size(); i++)
	{
		delete m_physObjs[i];
	}
}
