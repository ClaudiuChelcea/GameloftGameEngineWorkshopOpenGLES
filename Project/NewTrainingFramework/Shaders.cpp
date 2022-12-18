#include <stdafx.h>
#include "Shaders.h"

int Shaders::Init(char * fileVertexShader, char * fileFragmentShader)
{
	// Load shaders
	this->vertexShader = esLoadShader(GL_VERTEX_SHADER, fileVertexShader);

	if (this->vertexShader == 0 )
		return -1;

	this->fragmentShader = esLoadShader(GL_FRAGMENT_SHADER, fileFragmentShader);

	if (this->fragmentShader == 0 )
	{
		glDeleteShader(this->vertexShader );
		return -2;
	}

	// Load program
	this->program = esLoadProgram(this->vertexShader, this->fragmentShader);

	// Finding location of uniforms / attributes
	this->positionAttribute = glGetAttribLocation(program, "a_posL");

	// Color
	this->colorAttribute = glGetAttribLocation(this->program, "a_color");

	// Rotation of object
	this->rotationUniform = glGetUniformLocation(this->program, "u_rotation");

	// Camera
	this->matrixUniform = glGetUniformLocation(this->program, "u_rotZ");
	this->viewUniform = glGetUniformLocation(this->program, "u_view");
	this->perspectiveUniform = glGetUniformLocation(this->program, "u_persp");

	// Uv
	this->uvAttribute = glGetAttribLocation(this->program, "a_uv");

	// Scalation
	this->scalationUniform = glGetUniformLocation(this->program, "u_scalation");

	// Texture
	this->textureUniform = glGetUniformLocation(this->program, "u_texture");

	return 0;
}

Shaders::~Shaders()
{
	glDeleteProgram(program);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}