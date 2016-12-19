#include "mesh.h"

#include <vector>

#include <iostream>

Mesh::Mesh(const std::string& fileName)
{
	IndexedModel model = OBJModel(fileName).ToIndexedModel();
	InitMesh(model);
}

Mesh::Mesh(Vertex* verticies, unsigned int numVerticies, unsigned int* indices, unsigned int numIndicies)
{
	IndexedModel model;

	for (unsigned int i = 0; i < numVerticies; i++)
	{
		model.positions.push_back(*verticies[i].getPos());
		model.texCoords.push_back(*verticies[i].getTexCoord());
		model.normals.push_back(*verticies[i].getNormal());
	}

	for (unsigned int i = 0; i < numIndicies; i++)
		model.indices.push_back(indices[i]);

	InitMesh(model);
}

Mesh::~Mesh()
{
	glDeleteBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
	glDeleteVertexArrays(1, &m_vertexArrayObject);
}

void Mesh::InitMesh(const IndexedModel& model)
{
	m_drawCount = model.indices.size();

	/*
	for (unsigned int i = 0; i < model.normals.size(); i++)
	{
		std::cout << model.normals[i].z << std::endl;
	}	
	*/
	glGenVertexArrays(1, &m_vertexArrayObject);
	glBindVertexArray(m_vertexArrayObject);

	glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, model.texCoords.size() * sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[NORMAL_VB]);
	glBufferData(GL_ARRAY_BUFFER, model.normals.size() * sizeof(model.normals[0]), &model.normals[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffers[INDEX_VB]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
}

void Mesh::Draw()
{
	glBindVertexArray(m_vertexArrayObject);

	glDrawElementsBaseVertex(GL_TRIANGLES, m_drawCount, GL_UNSIGNED_INT, 0, 0);

	glBindVertexArray(0);
}