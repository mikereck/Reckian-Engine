#version 330 core

in vec3 position;
in vec3 norm;
in vec3 lightPos;

uniform vec3 color;

out vec4 FragColor;

void main()
{
	vec3 normal = vec3(norm);
	vec3 lightToPos = normalize(lightPos - position);
	float diffuse = min(max(  300*dot(    normal.xyz,lightToPos.xyz    )/(length(lightPos.xyz - position.xyz)*length(lightPos.xyz-position.xyz)), 0.0    ),.75);
	//diffuse = 0.5;
	//lightToPos = reflect(lightToPos, fData.normal);
	//(length(lightPos.xyz - position.xyz)*length(lightPos.xyz-position.xyz))

	FragColor = vec4(vec3(1,1,1)*color*diffuse + color*0.1, 1.0);

	//FragColor = vec4(color, 1.0);
}