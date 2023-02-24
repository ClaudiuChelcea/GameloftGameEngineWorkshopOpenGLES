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

ObjectComplete::ObjectComplete() {}

ObjectComplete::ObjectComplete(int _model_id, std::vector<int> _texture_id, int _shader_id)
{
	std::cerr << "Watch out! Multiple textures not implemented yet!" << std::endl;
	this->model_id = _model_id;
	this->texture_id = _texture_id.at(0);
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

int ObjectComplete::getModelId()
{
	return this->model_id;
}

int ObjectComplete::getShaderId()
{
	return this->shader_id;
}

int ObjectComplete::getTextureId()
{
	return this->texture_id;
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

void ObjectComplete::setModelId(int _model_id)
{
	this->model_id = _model_id;
}

void ObjectComplete::setShaderId(int _shader_id)
{
	this->shader_id = _shader_id;
}

void ObjectComplete::setTextureId(int _texture_id)
{
	this->texture_id = _texture_id;
}