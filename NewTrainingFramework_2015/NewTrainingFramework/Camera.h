#pragma once
#include "Math.h"
#include "../Utilities/utilities.h"

class Camera
{
private:
	Vector3 position, target;
	Vector3 up;
	GLfloat moveSpeed = 0.0001f, rotateSpeed = 0.5f;
	GLfloat nearC = 0.02f, farC = 10.0f ,fov = 0.25f;
	GLfloat deltaTime = 0.05f;
	Vector3 zAxis;
	Vector3 yAxis;
	Vector3 xAxis;
	Matrix viewMatrix, worldMatrix, perspectiveMatrix;
public:
	// Constructors 
	Camera() = default;
	Camera(Vector3 position = Vector3(0.0f, 0.0f, -5.0f), Vector3 target = Vector3(0.0f, 0.0f, 1.0f),
		   Vector3 up = Vector3(0.0f, 1.0f, 0.0f), GLfloat moveSpeed = { 1.0f }, GLfloat rotateSpeed = 0.5f,
		   GLfloat nearC = 0.0f, GLfloat farC = 0.0f, GLfloat fov = 0.0f);

	// Getters and setters
	Vector3 getPosition();
	void setPosition(Vector3 position);

	Vector3 getTarget();
	void setTarget();

	Vector3 getUp();
	void setUp();

	GLfloat getMoveSpeed();
	void setMoveSpeed(GLfloat moveSpeed);

	GLfloat getRotateSpeed();
	void setRotateSpeed(GLfloat rotateSpeed);

	GLfloat getNear();
	void setNear(GLfloat nearC);

	GLfloat getFar();
	void setFar(GLfloat farC);

	GLfloat getFov();
	void setFov(GLfloat fov);

	Matrix getWorldMatrix();

	Matrix getViewMatrix();

	Matrix getPerspectiveMatrix();
	void setPerspectiveMatrix();

	void setDeltaTime(float _deltaTime);

	// Methods
	void moveOx(GLint directie);
	void moveOy(GLint directie);
	void moveOz(GLint directie);
	void rotateOx(GLint directie);
	void rotateOy(GLint directie);
	void rotateOz(GLint directie);
	void updateWorldView();
	void updateAxis();
};