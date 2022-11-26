#include <stdafx.h>
#include "Shaders.h"

int Shaders::Init(char * fileVertexShader, char * fileFragmentShader)
{
	
	this->vertexShader = esLoadShader(GL_VERTEX_SHADER, fileVertexShader);

	if (this->vertexShader == 0 )
		return -1;

	this->fragmentShader = esLoadShader(GL_FRAGMENT_SHADER, fileFragmentShader);

	if (this->fragmentShader == 0 )
	{
		glDeleteShader(this->vertexShader );
		return -2;
	}

	this->program = esLoadProgram(this->vertexShader, this->fragmentShader);

	// Location
	this->positionAttribute = glGetAttribLocation(this->program, "a_posL");

	// Camera
	this->viewUniform = glGetUniformLocation(this->program, "u_view");
	this->perspectiveUniform = glGetUniformLocation(this->program, "u_persp");

	// Rotation
	this->matrixUniform = glGetUniformLocation(this->program, "u_rotZ");

	// Color
	this->colorAttribute = glGetAttribLocation(this->program, "a_color");

	return 0;
}

Shaders::~Shaders()
{
	glDeleteProgram(program);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}