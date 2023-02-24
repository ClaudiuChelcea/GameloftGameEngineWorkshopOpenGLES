#include "stdafx.h"
#include "CameraObject.h"

// Constructor
CameraObject::CameraObject(Camera* _camera, int _id, std::string _comment, std::string _type)
{
	this->cameraObjectCamera = _camera;
	this->id = _id;
	this->comment = _comment;
	this->type = type;
}