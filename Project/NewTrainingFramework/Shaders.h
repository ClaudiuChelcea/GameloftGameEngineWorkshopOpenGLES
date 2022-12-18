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

	// Uv
	GLint uvAttribute;

	// Rotation
	GLint rotationUniform;

	// Camera
	GLint matrixUniform;
	GLint viewUniform;
	GLint perspectiveUniform;

	// Scalation
	GLint scalationUniform;

	// Texture
	GLint textureUniform;

	char fileVS[260];
	char fileFS[260];

	// Functions
	int Init(char * fileVertexShader, char * fileFragmentShader);
	~Shaders();
};