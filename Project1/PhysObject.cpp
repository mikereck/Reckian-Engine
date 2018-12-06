#include "PhysObject.h"



PhysObject::PhysObject(Mesh* mesh, glm::vec3 position, float scale, glm::vec3 color) 
	 : m_scale(scale), m_mesh(mesh), m_position(position), m_color(color)
{
	
}

void PhysObject::draw()
{
	m_mesh->draw(m_color, m_position, glm::vec3(m_scale, m_scale, m_scale));
}


PhysObject::~PhysObject()
{
}
