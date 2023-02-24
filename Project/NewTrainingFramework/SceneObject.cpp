#include "stdafx.h"
#include "SceneObject.h"

// Constructor
SceneObject::SceneObject
(
	int _object_id,
	int _model,
	int _shader,
	std::string _type,
	std::string _name,
	std::vector<int> _textures,
	Vector3 _position,
	Vector3 _rotation,
	Vector3 _scale,
	Vector3 _color
)
{
	this->SO_object_id = _object_id;
	this->SO_model = _model;
	this->SO_shader = _shader;
	this->SO_type = _type;
	this->SO_name = _name;
	this->SO_textures = _textures;
	this->SO_position = _position;
	this->SO_rotation = _rotation;
	this->SO_scale = _scale;
	this->SO_color = _color;
}

/* Getters and setters */
void SceneObject::setObjectComplete(ObjectComplete& _newObject)
{
	this->thisObject = _newObject;
}

void SceneObject::setObjectCompleteIDS(int model_id, std::vector<int> texture_id, int shader_id)
{
	this->thisObject.setModelId(model_id);
	if(texture_id.size() > 1)
		std::cerr << "Watch out! Multiple textures not supported yet!" << std::endl;
	this->thisObject.setTextureId(texture_id.at(0));
	this->thisObject.setShaderId(shader_id);
}


int SceneObject::getSceneObjectModelId()
{
	return this->SO_model;
}

std::vector<int> SceneObject::getSceneObjectTextureId()
{
	return this->SO_textures;
}

int SceneObject::getSceneObjectShaderId()
{
	return this->SO_shader;
}

/* Debugger */
void SceneObject::printMe()
{
	std::cout << this->getModelClass()->getId() << std::endl;
	std::cout << this->getModelId() << std::endl;
}