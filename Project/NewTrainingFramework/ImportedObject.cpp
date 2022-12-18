#include "stdafx.h"
#include "ImportedObject.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Vertex.h"
#include "Shaders.h"
#include <iostream>

#define DEBUG_READING false

// Open file safely
FILE* ImportedObject::openFile(const char* file_name)
{
	FILE* f = NULL;
	f = fopen(file_name, "r");
	if (f == NULL) {
		std::cerr << "NFG file could not be opened!\n";
		std::exit(-1);
	}
	return f;
}

// Create object from NFG file
bool ImportedObject::InitNFG(FILE* file)
{
	// Scan number of vertices
	int numberOfVertices;
	fscanf(file, "NrVertices: %d\n", &numberOfVertices);
	if (numberOfVertices <= 0)
		return false;

	// Scan vertices
	Vertex* vertices = new Vertex[numberOfVertices];
	for (int i = 0; i < numberOfVertices; ++i)
	{
		fscanf(file, "   %*d. pos:[%f, %f, %f]; norm:[%f, %f, %f]; binorm:[%f, %f, %f]; tgt:[%f, %f, %f]; uv:[%f, %f];\n",
			&vertices[i].pos.x, &vertices[i].pos.y, &vertices[i].pos.z,
			&vertices[i].normal.x, &vertices[i].normal.y, &vertices[i].normal.z,
			&vertices[i].binorm.x, &vertices[i].binorm.y, &vertices[i].binorm.z,
			&vertices[i].tgt.x, &vertices[i].tgt.y, &vertices[i].tgt.z,
			&vertices[i].uv.x, &vertices[i].uv.y);
	}

#if DEBUG_READING == true
	for (int i = 0; i < numberOfVertices; ++i)
	{
		//printf("Vertices[%d]: pos.x = %f pos.y = %f pos.z = %f\n", i, vertices[i].pos.x, vertices[i].pos.y, vertices[i].pos.z);
		printf("Vertices[%d]: uv.x = %f uv.y = %f\n", i, vertices[i].uv.x, vertices[i].uv.y);
	}
#endif

	// Bind VBO
	glGenBuffers(1, &this->mVBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->mVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * numberOfVertices, vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// delete[] vertices;

	// Get indices
	unsigned int numberOfIndices;
	fscanf(file, "NrIndices: %u\n", &numberOfIndices);
	if (numberOfIndices <= 0)
	{
		glDeleteBuffers(1, &mVBO);
		return 0;
	}

	// Read
	unsigned short* indices = new unsigned short[numberOfIndices];
	for (int i = 0; i < numberOfIndices; i += 3)
	{
		fscanf(file, "   %*d.    %u,    %u,    %u\n", &indices[i], &indices[i + 1], &indices[i + 2]);
	}

#if DEBUG_READING == true
	for (int i = 0; i < numberOfIndices; i += 3)
	{
		if (i == 0) {
			printf("Indices[%d] = %u %u %u\n", i, indices[i], indices[i + 1], indices[i + 2]);
		}
		else {
			printf("Indices[%d] = %u %u %u\n", i / 3, indices[i], indices[i + 1], indices[i + 2]);
		}
	}
#endif

	// Bind VBO
	glGenBuffers(1, &this->mIBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->mIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * numberOfIndices, indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	mNumberOfIndices = numberOfIndices;
}

// Getters
unsigned int ImportedObject::getVBO()
{
	return this->mVBO;
}

unsigned int ImportedObject::getIBO()
{
	return this->mIBO;
}

unsigned int ImportedObject::getNumberOfIndices()
{
	return this->mNumberOfIndices;
}
