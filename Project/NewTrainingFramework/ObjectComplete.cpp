#include "stdafx.h"
#include "ObjectComplete.h"

// Constructor
ObjectComplete::ObjectComplete(Model* _model, Texture* _texture, Shader* _shader)
{
	this->model = _model;
	this->texture = _texture;
	this->shader = _shader;
}

ObjectComplete::ObjectComplete(int _model_id, int _texture_id, int _shader_id)
{
	this->model_id = _model_id;
	this->texture_id = _texture_id;
	this->shader_id = _shader_id;
}

/* Getters */
Model* ObjectComplete::getModelClass()
{
	return this->model;
}

Texture* ObjectComplete::getTextureClass()
{
	return this->texture;
}

Shader* ObjectComplete::getShaderClass()
{
	return this->shader;
}

/* Setters */
void ObjectComplete::setModelClass(Model* _model)
{
	try {
		this->model = _model;
	}
	catch (std::exception e)
	{
		std::cerr << e.what();
		std::abort();
	}
}

void ObjectComplete::setTextureClass(Texture* _texture)
{
	try {
		this->texture = _texture;
	}
	catch (std::exception e)
	{
		std::cerr << e.what();
		std::abort();
	}
}

void ObjectComplete::setShaderClass(Shader* _shader)
{
	try {
		this->shader = _shader;
	}
	catch (std::exception e)
	{
		std::cerr << e.what();
		std::abort();
	}
}