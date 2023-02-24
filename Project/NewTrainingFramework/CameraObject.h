#pragma once

#include <string>
#include "Camera.h"

class CameraObject : public Camera
{
private:
	int id;
	std::string comment;
	std::string type;
	Camera* cameraObjectCamera;
public:
	// Constructor
	CameraObject(Camera* _camera, int _id, std::string _comment, std::string _type);
};

