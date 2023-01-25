#include "stdafx.h"
#include "Texture.h"

// Constructor
Texture::Texture(TextureStruct* tr)
{
	this->tr = tr;
}

// Destructor
Texture::~Texture()
{
	delete tr;
}

/* Methods */

/* Getters */
std::string Texture::getTexturePath()
{
	std::string full_path = tr->texture_path + tr->texture_file;
	return full_path;
}

GLuint* Texture::getId()
{
	return this->tr->texture_id;
}

TextureStruct* Texture::getData()
{
	return this->tr;
}