#include "Scene.h"

Scene::Scene(Shader * shader, glm::vec3 gravity, float gravityConst) 
	: m_shader(shader), m_gravity(gravity), m_gravityConstant(gravityConst)
{
}

void Scene::addPhysObj(Mesh * mesh, glm::vec3 color, glm::vec3 position, float scale, float mass, glm::vec3 velocity, glm::vec3 accel)
{
	m_physObjs.push_back(new PhysObject(mesh, color, position, scale, mass, velocity, accel));
}

void Scene::physUpdate()
{
	for (int i = 0; i < m_physObjs.size(); i++)
	{
		
		for (int j = i+1; j < m_physObjs.size(); j++)
		{
			glm::vec3 relativePos = m_physObjs[i]->getPosition() - m_physObjs[j]->getPosition();
			if (glm::dot(relativePos, relativePos) > 1)
			{
				glm::vec3 forceIonJ = (m_gravityConstant * m_physObjs[i]->getMass()*m_physObjs[j]->getMass() / (glm::dot(relativePos, relativePos))) * relativePos;
				m_physObjs[i]->applyForce(-forceIonJ);
				m_physObjs[j]->applyForce(forceIonJ);
			}
		}
		m_physObjs[i]->applyForce(m_physObjs[i]->getMass()*m_gravity);
	}
}

glm::vec3 Scene::getCOM()
{
	float totalMass = 0;
	glm::vec3 COM(0,0,0);
	for (int i = 0; i < m_physObjs.size(); i++)
	{
		totalMass += m_physObjs[i]->getMass();
		COM += m_physObjs[i]->getPosition();
	}
	return COM/totalMass;
}

void Scene::renderUpdate(int width, int height)
{
	//temp code
	glm::mat4 VMatrix = glm::lookAt(glm::vec3(0, 0, 30), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glm::mat4 PMatrix = glm::perspective((float)glm::radians(45.0f), (float)width / height, (float).1, (float)100);

	for (int i = 0; i < m_physObjs.size(); i++)
	{
		m_physObjs[i]->physUpdate(17);
		m_physObjs[i]->draw(VMatrix, PMatrix);
	}
	glm::vec3 COM = getCOM();

	//std::cout << COM.x << "," << COM.y << "," << COM.z << std::endl;
}

Scene::~Scene()
{
	for (int i = 0; i < m_physObjs.size(); i++)
	{
		delete m_physObjs[i];
	}
}
