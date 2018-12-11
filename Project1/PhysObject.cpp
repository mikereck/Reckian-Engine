#include "PhysObject.h"



PhysObject::PhysObject(Mesh* mesh, glm::vec3 color, glm::vec3 position, float mass, float charge, float scale,  glm::vec3 velocity, glm::vec3 accel)
	 : m_scale(scale), m_mesh(mesh), m_position(position), m_color(color), m_velocity(velocity), m_accel(accel), m_mass(mass), m_charge(charge)
{
	//beginning force is assumed to already be applied via acceleration
	m_force = glm::vec3(0, 0, 0);
}

void PhysObject::draw(glm::mat4 viewMatrix, glm::mat4 perMatrix)
{
	
	//if the pointer to the mesh is not Null, call the mesh's inherent draw function providing, the color, position, and scale from private variables 
	if (m_mesh != NULL)
		m_mesh->draw(m_color, m_position, glm::vec3(m_scale, m_scale, m_scale), viewMatrix, perMatrix);
	else
		delete this;
}

void PhysObject::physUpdate(float timeInMS)
{
	m_force += m_charge * (m_efield + glm::cross(m_velocity,m_bfield));

	//Euler approximation of velocity and position
	m_position += (timeInMS / 1000) * m_velocity;
	m_velocity += (timeInMS / 1000) * m_accel;

	// a=F/m
	m_accel = m_force / m_mass;

	//Reset force to zero (assumes that all forces are applied instantaneously and then removed)
	m_force = glm::vec3(0, 0, 0);
	m_efield = glm::vec3(0, 0, 0);
	m_bfield = glm::vec3(0, 0, 0);
}

void PhysObject::applyForce(glm::vec3 Force)
{
	m_force += Force;
}

void PhysObject::applyEField(glm::vec3 EField)
{
	m_efield += EField;
}

void PhysObject::applyBField(glm::vec3 BField)
{
	m_bfield += BField;
}


void PhysObject::dumpStats()
{
	std::cout << "Position : (" << m_position.x << "," << m_position.y << "," << m_position.z << ")" << std::endl;
	std::cout << "Velocity : (" << m_velocity.x << "," << m_velocity.y << "," << m_velocity.z << ")" << std::endl;
	std::cout << "Acceleration : (" << m_accel.x << "," << m_accel.y << "," << m_accel.z << ")" << std::endl;
	std::cout << "Force : (" << m_force.x << "," << m_force.y << "," << m_force.z << ")" << std::endl;
	std::cout << "E-Field : (" << m_efield.x << "," << m_efield.y << "," << m_efield.z << ")" << std::endl;
	std::cout << "B-Field : (" << m_bfield.x << "," << m_bfield.y << "," << m_bfield.z << ")" << std::endl;
	std::cout << "Mass : " << m_mass << std::endl;
	std::cout << "Charge : " << m_charge << std::endl;
}

PhysObject::~PhysObject()
{
	//Meshes are handled by the class using the PhysObject
}
