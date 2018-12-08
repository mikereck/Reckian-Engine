#version 330 core

in vec3 position;
in vec3 norm;

uniform vec3 color;

out vec4 FragColor;

void main()
{
	vec3 normal = vec3(norm);
	vec3 lightPos = vec3(-1, 1,-1);
	vec3 lightToPos = normalize(lightPos.xyz - position.xyz);
	float diffuse = 2.5*max(  dot(    normal.xyz,lightToPos.xyz    ), 0.0    )/(length(lightPos.xyz - position.xyz)*length(lightPos.xyz - position.xyz));
	//diffuse = 0.5;
	//lightToPos = reflect(lightToPos, fData.normal);

	FragColor = vec4(vec3(1,1,1)*color*diffuse + color*0.1, 1.0);

	//FragColor = vec4(color, 1.0);
}