#pragma once
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include

// Camera
class Camera
{
	private:
		Vector3 position;
		Vector3 target;
		Vector3 up;
		GLfloat moveSpeed;
		GLfloat rotateSpeed;
		GLfloat farC;
		GLfloat nearC;
		GLfloat fov;
		GLfloat deltaTime;
		Vector3 xAxis;
		Vector3 yAxis;
		Vector3 zAxis;
		Matrix viewMatrix;
		Matrix worldMatrix;
		Matrix perspectiveMatrix;

		// For any object, we'll multiply it with MVP
		// Matrix model; // Scaling, rotation, translation (in this order)
		// Matrix view; // allows us to walk in the scene using an abstract point called camera
		// Matrix projection; // projection - for close and far seeing

		#define CAMERA_DELTATIME_ACTIVE false
		GLfloat cameraPrivateSpeed = 0.03f;

	public:
		/* Camera movement */
		void moveOx(GLint distance);
		void moveOy(GLint distance);
		void moveOz(GLint distance);

		/* Camera rotation */
		void rotateOx(GLint directie);
		void rotateOy(GLint directie);
		void rotateOz(GLint directie);

		/* World view */
		void updateWorldView();
		void updateAxis();
		void setPerspectiveMatrix();

		/* Getters */
		GLfloat getMoveSpeed();
		Matrix getWorldMatrix();
		Matrix getViewMatrix();
		Matrix getPerspectiveMatrix();

		/* Setters */
		void setDeltaTime(float _deltaTime);

		/* Constructors */
		Camera(Vector3 position = Vector3(0.0f, 0.0f, -5.0f), Vector3 target = Vector3(0.0f, 0.0f, 1.0f),
			Vector3 up = Vector3(0.0f, 1.0f, 0.0f), GLfloat moveSpeed = { 1.0f }, GLfloat rotateSpeed = 0.5f,
			GLfloat nearC = 0.0f, GLfloat farC = 0.0f, GLfloat fov = 0.0f);
};

