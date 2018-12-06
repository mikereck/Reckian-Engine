#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
	//The OpenGL ID for this shader
	unsigned int ID;

	Shader(const char * vertexPath, const char * fragmentPath);
	void use();
	~Shader();
private:
	void checkCompileErrors(GLuint shader, std::string type);
};

