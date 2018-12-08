#include "Mesh.h"

unsigned int sphSubdiv(glm::vec3 pointA, glm::vec3 pointB, glm::vec3 pointC, std::vector<float> &vertices, std::vector<float> &normals, int numSubDivs);
glm::vec3 lerp(glm::vec3 A, glm::vec3 B, float point);

Mesh::Mesh(Shader* shader) : m_shader(shader)
{
}

void Mesh::createPlane()
{
	//Unite square centered on (0,0,0) with the normal facing -z
	float vertices[] =
	{
		-0.5, -0.5, 0,
		-0.5,  0.5, 0,
		 0.5,  0.5, 0,
		 0.5, -0.5, 0
	};

	unsigned int indices[] =
	{
		0, 1, 2,
		2, 3, 0
	};

	float normals[] =
	{
		0, 0, 0,
		0, 0, 0,
		0, 0, 0,
		0, 0, 0
	};


	//calculate the normals
	for (int i = 0; i < 2; i++)
	{
		glm::vec3 a(vertices[3*indices[i * 3 + 1]] - vertices[3*indices[i * 3]], vertices[3*indices[i * 3 + 1] + 1] - vertices[3*indices[i * 3] + 1], vertices[3*indices[i * 3 + 1] + 2] - vertices[3*indices[i * 3] + 2]);
		glm::vec3 b(vertices[3*indices[i * 3 + 2]] - vertices[3*indices[i * 3]], vertices[3*indices[i * 3 + 2] + 1] - vertices[3*indices[i * 3] + 1], vertices[3*indices[i * 3 + 2] + 2] - vertices[3*indices[i * 3] + 2]);

		//std::cout << a.x << "," << a.y << "," << a.z << std::endl;
		//std::cout << b.x << "," << b.y << "," << b.z << std::endl;

		glm::vec3 c = glm::cross(a,b);

		for (int j = 0; j < 3; j++)
		{
			normals[3*indices[3 * i + j]] += c.x;
			normals[3*indices[3 * i + j] + 1] += c.y;
			normals[3*indices[3 * i + j] + 2] += c.z;
		}
		

		//std::cout << normals[3 * i] << "," << normals[3 * i + 1] << "," << normals[3 * i + 2] << std::endl;
	}


	//normalize the normals
	for (int i = 0; i < 4; i++)
	{
		float acc = 0;
		for (int j = 0; j < 3; j++)
		{
			acc += normals[3 * i + j] * normals[3 * i + j];
		}
		acc = glm::sqrt(acc);
		for (int j = 0; j < 3; j++)
		{
			normals[3 * i + j] = normals[3 * i + j] / acc;
		}

		std::cout << normals[3 * i] << "," << normals[3 * i + 1] << "," << normals[3 * i + 2] << std::endl;
		//std::cout << acc << std::endl;
	}

	

	//Create and assign values to the Vertex Buffer (VBO) and Element Buffer (EBO)
	VBO = new Buffer(vertices, 4, 3);
	NBO = new Buffer(normals, 4, 3);
	EBO = new IndexBuffer(indices, 6);

	//Attach the Vertex Buffer to the Vertex Array
	VAO.AttachBuffer(VBO, 0);
	VAO.AttachBuffer(NBO, 1);

	//set the loaded bool to true to allow for rendering
	m_loaded = true;
}

void Mesh::createSphere()
{
	unsigned int numT = 0;

	std::vector<float> vertices;
	std::vector<float> normals;
	std::vector<unsigned int> indices;
	glm::vec3 A(0.0, 0.0, -1.0);
	glm::vec3 B(0.0, 0.942809, 0.333333);
	glm::vec3 C(-0.816497, -0.471405, 0.333333);
	glm::vec3 D(0.816497, -0.471405, 0.333333);
	
	numT += sphSubdiv(A, B, C, vertices, normals, 6);
	numT += sphSubdiv(D, C, B, vertices, normals, 6);
	numT += sphSubdiv(A, D, B, vertices, normals, 6);
	numT += sphSubdiv(A, C, D, vertices, normals, 6);

	
	for (unsigned int a = 0; a < vertices.size()/3; a++)
	{
		indices.push_back(a);
	}

	VBO = new Buffer(vertices.data(), vertices.size() / 3, 3);
	NBO = new Buffer(normals.data(), normals.size() / 3, 3);
	EBO = new IndexBuffer(indices.data(), indices.size());

	VAO.AttachBuffer(VBO, 0);
	VAO.AttachBuffer(NBO, 1);

	m_loaded = true;
	
}

void Mesh::draw(glm::vec3 color, glm::vec3 position, glm::vec3 scale)
{
	//Check to see if a mesh has been loaded before rendering
	if (m_loaded)
	{
		//enable the shader for this mesh
		m_shader->use();
		//bind the vertex array and the element buffer
		VAO.Bind();
		EBO->Bind();

		//Create  the transform matrix described by the provided position and scale
		glm::mat4 MVMatrix;
		glm::mat3 NMatrix;
		MVMatrix = glm::translate(MVMatrix, position);
		MVMatrix = glm::scale(MVMatrix,scale);
		NMatrix = glm::mat3(MVMatrix);
		NMatrix = glm::transpose(NMatrix);



		//Send the transform matrix and the color to the shader as uniforms
		glUniform3f(glGetUniformLocation(m_shader->ID, "color"), color.x, color.y, color.z);
		glUniformMatrix4fv(glGetUniformLocation(m_shader->ID, "MVMatrix"), 1, GL_FALSE, glm::value_ptr(MVMatrix));
		glUniformMatrix3fv(glGetUniformLocation(m_shader->ID, "NMatrix"), 1, GL_FALSE, glm::value_ptr(NMatrix));

		//Drawthe shape to the screen
		glDrawElements(GL_TRIANGLES, EBO->getCount(), GL_UNSIGNED_INT, 0);

		//Unbind the vertex array and the element buffer
		EBO->Unbind();
		VAO.Unbind();
	}
}



Mesh::~Mesh()
{
	//Since the element buffer is stored as a pointer, we need to delete it when the Mesh object is deleted
	delete EBO;
}

unsigned int sphSubdiv(glm::vec3 pointA, glm::vec3 pointB, glm::vec3 pointC, std::vector<float> &vertices, std::vector<float> &normals, int numSubDivs)
{
	if (numSubDivs > 0)
	{
		unsigned int numT = 0;
		glm::vec3 AB = glm::normalize(lerp(pointA, pointB, 0.5));
		glm::vec3 AC = glm::normalize(lerp(pointA, pointC, 0.5));
		glm::vec3 BC = glm::normalize(lerp(pointB, pointC, 0.5));

		numT += sphSubdiv(pointA, AB, AC, vertices, normals, numSubDivs - 1);
		numT += sphSubdiv(AB, pointB, BC, vertices, normals, numSubDivs - 1);
		numT += sphSubdiv(BC, pointC, AC, vertices, normals, numSubDivs - 1);
		numT += sphSubdiv(AB, BC, AC, vertices, normals, numSubDivs - 1);

		return numT;
	}
	else
	{
		vertices.push_back(pointA.x);
		vertices.push_back(pointA.y);
		vertices.push_back(pointA.z);
		vertices.push_back(pointB.x);
		vertices.push_back(pointB.y);
		vertices.push_back(pointB.z);
		vertices.push_back(pointC.x);
		vertices.push_back(pointC.y);
		vertices.push_back(pointC.z);

		normals.push_back(pointA.x);
		normals.push_back(pointA.y);
		normals.push_back(pointA.z);
		normals.push_back(pointB.x);
		normals.push_back(pointB.y);
		normals.push_back(pointB.z);
		normals.push_back(pointC.x);
		normals.push_back(pointC.y);
		normals.push_back(pointC.z);

		return 1;
	}
	
}

glm::vec3 lerp(glm::vec3 A, glm::vec3 B, float point)
{
	return (B - A)*point + A;
}
