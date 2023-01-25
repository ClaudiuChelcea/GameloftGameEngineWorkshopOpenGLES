#pragma once

#include "ImportedObject.h"
#include "Structs.h"

class Texture : public ImportedObject
{
private:
	TextureStruct* tr;
public:
	// Constructor
	Texture(TextureStruct* tr);
	Texture() = default;

	// Destructor
	~Texture();

	/* Methods */

	/* Getters */
	std::string getTexturePath();
	GLuint* getId();
	TextureStruct* getData();
};
