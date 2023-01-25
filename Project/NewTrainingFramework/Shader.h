#pragma once

#include "ImportedObject.h"
#include "Structs.h"
#include "Shaders.h"

class Shader : public ImportedObject, public Shaders
{
private:
	ShaderStruct* sd;
public:
	// Constructor
	Shader(ShaderStruct* sd);
	Shader() = default;

	// Destructor
	~Shader();

	/* Methods */

	/* Getters */
	std::string getShaderPath();
	ShaderStruct* getData();
	GLuint getProgram();
	GLuint getId();
};

