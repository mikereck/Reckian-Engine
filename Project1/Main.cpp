#include "Shader.h"
#include "Mesh.h"
#include "PhysObject.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int w, int h);
void ProcessInput(GLFWwindow* window);


int main()
{	
	//Initialize GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Create Window
	GLFWwindow* window = glfwCreateWindow(800, 600, "Testing 123", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window";
		glfwTerminate();
		return -1;
	}
	//Make the new window the current OpenGL Context
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//Initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD";
		return -1;
	}

	//Create and compile shader
	Shader ourShader("vShader.vs", "fShader.fs");

	//Create plane mesh to be used for rendering
	Mesh Plane(&ourShader);
	Plane.createPlane();

	//Create all physics objects for the current scene
	PhysObject PhysPlane(&Plane,glm::vec3(-0.5,0,0));
	
	//Render Loop
	while (!glfwWindowShouldClose(window))
	{
		ProcessInput(window);

		//Clear the screen
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		PhysPlane.applyForce(glm::vec3(.00001,0,0));
		PhysPlane.physUpdate(17);
		//Draw all of the Physics objects
		PhysPlane.draw();

		//Switch which buffer is being drawn to the screen
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	
	//Terminate glfw on close
	glfwTerminate();
	return 0;
}

void ProcessInput(GLFWwindow* window)
{
	//Check if the user has pressed the escape key, if so, tell the window that it should close
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int w, int h)
{
	//Update the size of the context being drawn to if the size of the window changes
	glViewport(0, 0, w, h);
}