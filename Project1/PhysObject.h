#pragma once
#include "Mesh.h"
#include <glm/glm.hpp>

class PhysObject
{
public:
	//Create a PhysicsObject with the provided values, if no variables are provided, it will be placed at (0,0,0) with a mass of 1 unit and a velocity and acceleration of (0,0,0)
	PhysObject(Mesh* mesh, glm::vec3 color = glm::vec3(1, 0, 0), glm::vec3 position = glm::vec3(0, 0, 0), float scale = 1, float mass = 1, glm::vec3 velocity = glm::vec3(0, 0, 0), glm::vec3 accel = glm::vec3(0, 0, 0));

	//Draws the mesh to the screen using the position, color, and scale stored in the respective private variables
	void draw(glm::mat4 viewMatrix, glm::mat4 perMatrix);

	//update the phsyics variables using an Euler approximation
	void physUpdate(float timeInMS);

	//Set the force variable to the provide value
	void applyForce(glm::vec3 Force);

	float getMass() { return m_mass; };

	glm::vec3 getPosition() { return m_position; };

	~PhysObject();
private:
	//Mesh to be rendered for this physics object
	Mesh* m_mesh;

	//physics variables
	glm::vec3 m_position;
	glm::vec3 m_velocity;
	glm::vec3 m_accel;
	glm::vec3 m_force;
	float m_mass;

	//drawing variables
	float m_scale;
	glm::vec3 m_color;


};

