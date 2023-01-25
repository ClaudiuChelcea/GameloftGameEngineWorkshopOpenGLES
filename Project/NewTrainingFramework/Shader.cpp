#include "stdafx.h"
#include "Shader.h"

// Constructor
Shader::Shader(ShaderStruct* sd)
{
	this->sd = sd;
}

// Destructor
Shader::~Shader()
{
	delete sd;
}

/* Methods */

/* Getters */
std::string Shader::getShaderPath()
{
	std::string full_path = sd->shader_path;
	return full_path;
}

ShaderStruct* Shader::getData()
{
	return this->sd;
}

GLuint Shader::getProgram()
{
	return this->program;
}

GLuint Shader::getId()
{
	return this->sd->shader_id;
}