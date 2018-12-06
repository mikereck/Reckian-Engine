#include "PhysObject.h"



PhysObject::PhysObject(Mesh* mesh, glm::vec3 position, float scale, glm::vec3 color, float mass, glm::vec3 velocity, glm::vec3 accel)
	 : m_scale(scale), m_mesh(mesh), m_position(position), m_color(color), m_velocity(velocity), m_accel(accel), m_mass(mass)
{
	//beginning force is assumed to already be applied via acceleration
	m_force = glm::vec3(0, 0, 0);
}

void PhysObject::draw()
{
	
	//if the pointer to the mesh is not Null, call the mesh's inherent draw function providing, the color, position, and scale from private variables 
	if (m_mesh != NULL)
		m_mesh->draw(m_color, m_position, glm::vec3(m_scale, m_scale, m_scale));
	else
		delete this;
}

void PhysObject::physUpdate(float timeInMS)
{
	//Euler approximation of velocity and position
	m_position += (timeInMS / 1000) * m_velocity;
	m_velocity += (timeInMS / 1000) * m_accel;

	// a=F/m
	m_accel = m_force / m_mass;

	//Reset force to zero (assumes that all forces are applied instantaneously and the removed)
	m_force = glm::vec3(0,0,0);
}

void PhysObject::applyForce(glm::vec3 Force)
{
	m_force = Force;
}


PhysObject::~PhysObject()
{
	//Meshes are handled by the class using the PhysObject
}
