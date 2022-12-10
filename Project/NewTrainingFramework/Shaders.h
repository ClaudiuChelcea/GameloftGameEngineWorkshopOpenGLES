#pragma once
#include "../Utilities/utilities.h"

class Shaders 
{
public:
	// Params
	GLuint program, vertexShader, fragmentShader;

	// Position
	GLint positionAttribute;

	// Color
	GLint colorAttribute;

	char fileVS[260];
	char fileFS[260];

	// Functions
	int Init(char * fileVertexShader, char * fileFragmentShader);
	~Shaders();
};