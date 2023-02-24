#pragma once
#include <string>
#include "Camera.h"
#include "Shaders.h"
#include "XMLreader.h"
#include "ResourceManager.h"
#include "SceneManager.h"

static class Globals
{
	private:
		/* Camera variables */
		Vector3 position = Vector3(0.0f, 0.0f, -5.0f);
		Vector3 target = Vector3(0.0f, 0.0f, 1.0f);
		Vector3 up = Vector3(0.0f, 1.0f, 0.0f);
		GLfloat moveSpeed = { 1.0f };
		GLfloat rotateSpeed = 0.5f;
		GLfloat nearC = 0.0001f;
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
		#define DRAW_TRIANGLE true
		GLuint vboIdTriangle;
		Shaders myTriangleShader;
		GLuint vboIdTriangle2;
		float rotationAngle = 0.0f;
		float rotationAngleIncreaseSpeed = 0.01f;

		// Rectangle
		#define DRAW_RECTANGLE3D false
		#define VBO true
		#if VBO == true
				GLuint vboIdRectangle3D;
		#else 
				GLuint vboIdRectangle3D;
				GLuint iboIdRectangle3D;
		#endif
		Shaders myRectangle3DShader;
		float rotationAngleRectangle3D = 0.0f;
		float rotationAngleIncreaseSpeedRectangle3D = 0.01f;

		// Rectangle
		#define DRAW_SQUARE false
		GLuint vboIdSquare;
		Shaders mySquareShader;
		float rotationAngleSquare = 0.0f;
		float rotationAngleIncreaseSpeedSquare = 0.01f;

		// Middle Line
		#define DRAW_MIDDLE_LINE false
		GLuint vboIdMiddleLine;
		Shaders myMiddleLineShader;

		/* Camera */
		Camera myCamera = Camera(position, target, up, moveSpeed, rotateSpeed, nearC, farC, fov);

		// Prevent update from happening too fast
		#define LOCK_UPDATE false
		GLfloat currentTime = 0;
		GLfloat maxTime = 0.05f;

		// Enforced rotation on mouse click
		#define ENFORCE_ROTATION false
		GLfloat enforcedRotation = 0;
		GLfloat enforcedRotationStep = 90;

		// XML TEST
		#define ENABLE_XML_TEST_PRINT false
		#define PRINT_XML_TEST false

		// FLAGS
		#define QUIT_IF_NOTHING_TO_DRAW false
};
