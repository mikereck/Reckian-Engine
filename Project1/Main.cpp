#include "Shader.h"
#include "Mesh.h"
#include "PhysObject.h"
#include "Scene.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int w, int h);
void ProcessInput(GLFWwindow* window);

int width;
int height;

bool Progress;


int main()
{	
	//Initialize GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Create Window
	GLFWwindow* window = glfwCreateWindow(800, 800, "Testing 123", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window";
		glfwTerminate();
		return -1;
	}
	//Make the new window the current OpenGL Context
	width = 800;
	height = 800;
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//Initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD";
		return -1;
	}

	glEnable(GL_DEPTH_TEST);

	//Create and compile shader
	Shader ourShader("vShader.vs", "fShader.fs");

	//Create plane mesh to be used for rendering
	Mesh Plane(&ourShader);
	Plane.createSphere();

	//Create all physics objects for the current scene
	//PhysObject PhysPlane(&Plane, glm::vec3(1, 0.6, 1),glm::vec3(-10,0,0));

	//1,0.6,1

	Scene myScene(&ourShader, glm::vec3(0,0,0), 0.01f, /*MAXDWORD32*/ 1.0f, 0.0f);


	/*Magnetic force test
	myScene.addPhysObj(&Plane, glm::vec3(1, 1, 1), glm::vec3(-10, 0, 0), MAXDWORD32, 1,1,glm::vec3(0.01,0,0));
	myScene.addPhysObj(&Plane, glm::vec3(1, 0, 0), glm::vec3(-10, 10, 0), 1, -1, 1, glm::vec3(0.0, 0.0, 0.01));
	*/
	/**/
	myScene.addPhysObj(&Plane, glm::vec3(0.75, 0, 0), glm::vec3(10, 0, 0), 1, 1);
	myScene.addPhysObj(&Plane, glm::vec3(0.5, 0.5, 0.5), glm::vec3(-10, 0, 0), 1, 1);
	myScene.addPhysObj(&Plane, glm::vec3(0, 0.75, 0), glm::vec3(10, 10, 0), 1, 1);
	myScene.addPhysObj(&Plane, glm::vec3(0, 0, 0.75), glm::vec3(-10, -10, 0), 1, 1);
	myScene.addPhysObj(&Plane, glm::vec3(0, 0.75, 0.75), glm::vec3(-10, 10, 0), 1, 1);
	myScene.addPhysObj(&Plane, glm::vec3(0.75, 0, 0.75), glm::vec3(10, -10, 0), 1, 1);
	myScene.addPhysObj(&Plane, glm::vec3(1, 0.6, 1), glm::vec3(0, 0, -10), 1, 1);
	myScene.addPhysObj(&Plane, glm::vec3(1, 0.6, 0.6), glm::vec3(0, 0, 10), 1, 1);
	myScene.addPhysObj(&Plane, glm::vec3(1, 0.6, 0.25), glm::vec3(10, 10, -10), 1, 1);
	myScene.addPhysObj(&Plane, glm::vec3(0.6, 1, 1), glm::vec3(-10, -10, 10), 1, 1);
	

	/* COOL LAYOUT!
	myScene.addPhysObj(&Plane, glm::vec3(.75, 0, 0), glm::vec3(-10, 0, 0),1,0,1,glm::vec3(0,1.75*.1125,0));
	myScene.addPhysObj(&Plane, glm::vec3(0.5, 0.5, 0.5), glm::vec3(10, 0, 0), 1, 0, 1, glm::vec3(0, 1.75*-.1125, 0));
	myScene.addPhysObj(&Plane, glm::vec3(0, 0.75, 0), glm::vec3(0, -10, 0),1,0, 1,glm::vec3(1.75*-.1125,0,0));
	myScene.addPhysObj(&Plane, glm::vec3(0, 0, .75), glm::vec3(0, 10, 0),1,0,1, glm::vec3(1.75*.1125,0,0));
	myScene.addPhysObj(&Plane, glm::vec3(1, 0.6, 1), glm::vec3(0, 0, -10), 1, 0);
	*/
	//Render Loop
	while (!glfwWindowShouldClose(window))
	{
		ProcessInput(window);
		Progress = false;
		//Clear the screen
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//PhysPlane.applyForce(glm::vec3(.0001, 0, 0));
		//PhysPlane.physUpdate(17);
		//Draw all of the Physics objects
		//PhysPlane.draw(VMatrix, PMatrix);
		myScene.physUpdate();
		/*
		myScene.dumpStats();
		while (!Progress)
		{
			glfwPollEvents();
			ProcessInput(window);
		}
		while (Progress)
		{
			glfwPollEvents();
			ProcessInput(window);
		}*/
		myScene.renderUpdate(width, height);

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
	if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
		Progress = true;
	if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_RELEASE)
		Progress = false;
}

void framebuffer_size_callback(GLFWwindow* window, int w, int h)
{
	//Update the size of the context being drawn to if the size of the window changes
	glViewport(0, 0, w, h);
	width = w;
	height = h;
}