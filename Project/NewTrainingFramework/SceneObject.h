#pragma once

#include <string>
#include <vector>
#include "../Utilities/utilities.h"
#include "ObjectComplete.h"

class SceneObject : public ObjectComplete
{
private:
	ObjectComplete thisObject;
	int SO_object_id;
	int SO_model;
	int SO_shader;
	std::string SO_type;
	std::string SO_name;
	std::vector<int> SO_textures;
	Vector3 SO_position;
	Vector3 SO_rotation;
	Vector3 SO_scale;
	Vector3 SO_color;
	bool SO_wired = false;
public:
	// Constructor
	SceneObject(
		int _object_id,
		int _model,
		int _shader,
		std::string _type,
		std::string _name,
		std::vector<int> _textures,
		Vector3 _position,
		Vector3 _rotation,
		Vector3 _scale,
		Vector3 _color = { -1, -1, -1 });

	/* Getters and setters */
	void setObjectComplete(ObjectComplete& _newObject);
	void setObjectCompleteIDS(int model_id, std::vector<int> texture_id, int shader_id);
	int getSceneObjectModelId();
	std::vector<int> getSceneObjectTextureId();
	int getSceneObjectShaderId();

	/* Debugger */
	void printMe();
};