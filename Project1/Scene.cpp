#include "Scene.h"

Scene::Scene(Shader * shader, glm::vec3 gravity, float gravityConst, float permittivity, float permeability) 
	: m_shader(shader), m_gravity(gravity), m_gravityConstant(gravityConst), m_permittivity(permittivity), m_permeability(permeability)
{
}

void Scene::addPhysObj(Mesh * mesh, glm::vec3 color, glm::vec3 position, float mass, float charge, float scale, glm::vec3 velocity, glm::vec3 accel)
{
	m_physObjs.push_back(new PhysObject(mesh, color, position, mass, charge, scale, velocity, accel));
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
				glm::vec3 efieldBase = (relativePos/(4 * glm::pi<float>() * m_permittivity * glm::pow( glm::length(relativePos),3 )));

				//                   mu/4pi                             Q/len^2
				m_physObjs[i]->applyBField((m_permeability/(4*glm::pi<float>())) * m_physObjs[j]->getCharge()/(glm::dot(relativePos,relativePos)) * glm::cross(m_physObjs[j]->getVelocity(),-relativePos));
				m_physObjs[j]->applyBField((m_permeability / (4 * glm::pi<float>())) * m_physObjs[i]->getCharge() / (glm::dot(relativePos, relativePos)) * glm::cross(m_physObjs[i]->getVelocity(), relativePos));

				m_physObjs[i]->applyEField(efieldBase * m_physObjs[j]->getCharge());
				m_physObjs[j]->applyEField(-efieldBase * m_physObjs[i]->getCharge());

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

void Scene::dumpStats()
{

	std::cout << "Scene Stats" << std::endl;
	std::cout << "Gravity Accel : (" << m_gravity.x << "," << m_gravity.y << "," << m_gravity.z << ")" << std::endl;
	std::cout << "Gravity Constant : " << m_gravityConstant << std::endl;
	std::cout << "Permittivity : " << m_permittivity << std::endl;
	std::cout << "Permeability : " << m_permeability << std::endl;

	std::cout << std::endl;
	for (int i = 0; i < m_physObjs.size(); i++)
	{
		std::cout << "Object #" << i << std::endl;
		m_physObjs[i]->dumpStats();
		std::cout << std::endl;
	}
}

Scene::~Scene()
{
	for (int i = 0; i < m_physObjs.size(); i++)
	{
		delete m_physObjs[i];
	}
}
