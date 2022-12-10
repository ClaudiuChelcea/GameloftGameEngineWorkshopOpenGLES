#pragma once
#include <string>
#include "Camera.h"

static class Globals
{
	private:
		/* Camera variables */
		Vector3 position = Vector3(0.0f, 0.0f, -5.0f);
		Vector3 target = Vector3(0.0f, 0.0f, 1.0f);
		Vector3 up = Vector3(0.0f, 1.0f, 0.0f);
		GLfloat moveSpeed = { 1.0f };
		GLfloat rotateSpeed = 0.5f;
		GLfloat nearC = 0.1f;
		GLfloat farC = 10000.0f;
		GLfloat fov = 5.0f;
	public:
		/* View screen */
		// Size
		struct screen_size {
			static const int screenWidth = 960;
			static const int screenHeight = 720;
		} screen_size;

		// Title
		std::string screenTitle = "MyGameEngine";

		/* DEBUG */
		struct DEBUG {
			int DEBUG_BACKGROUND = false;
		} DEBUGGER;

		// Triangle
		float rotationAngle = 0.0f;
		float rotationAngleIncreaseSpeed = 0.01f;

		/* Camera */
		Camera myCamera = Camera(position, target, up, moveSpeed, rotateSpeed, nearC, farC, fov);

		// Prevent update from happening too fast
		#define LOCK_UPDATE false
		GLfloat currentTime = 0;
		GLfloat maxTime = 0.05f;
};
