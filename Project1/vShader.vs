#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNor;

uniform mat4 MVMatrix;
uniform mat3 NMatrix;

out vec3 position;
out vec3 norm;

void main()
{
	gl_Position = MVMatrix * vec4(aPos, 1.0);
	position = (MVMatrix * vec4(aPos, 1.0)).xyz;
	norm = NMatrix* aNor;
}

