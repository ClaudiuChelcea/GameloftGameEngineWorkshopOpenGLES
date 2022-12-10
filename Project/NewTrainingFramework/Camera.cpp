#include "stdafx.h"
#include "Camera.h"
#include "Globals.h"

extern Globals allGlobals; // receive global variables

/* Getters */
GLfloat Camera::getMoveSpeed()
{
	return this->moveSpeed;
}

Matrix Camera::getWorldMatrix() {
	return this->worldMatrix;
}

Matrix Camera::getViewMatrix() {
	return this->viewMatrix;
}

Matrix Camera::getPerspectiveMatrix() {
	return this->perspectiveMatrix;
}

/* Setters */
void Camera::setDeltaTime(float _deltaTime)
{
	this->deltaTime = _deltaTime;
}

/* Constructors */
Camera::Camera(Vector3 position, Vector3 target, Vector3 up, GLfloat moveSpeed, GLfloat rotateSpeed, GLfloat nearC, GLfloat farC, GLfloat fov) {
	this->zAxis = -(target - position).Normalize();
	this->yAxis = up.Normalize();
	this->xAxis = zAxis.Cross(yAxis).Normalize();
	this->position = position;
	this->target = target;
	this->up = up;
	this->zAxis = -(this->target - this->position).Normalize();
	this->yAxis = this->up.Normalize();
	this->xAxis = this->zAxis.Cross(this->yAxis).Normalize();
	this->moveSpeed = moveSpeed;
	this->rotateSpeed = rotateSpeed;
	this->nearC = nearC;
	this->farC = farC;
	this->fov = fov;
	updateAxis();
	updateWorldView();
	setPerspectiveMatrix();
};

/* Camera movement */
void Camera::moveOx(GLint distance)
{
	Vector3 forward = xAxis * distance;
	Vector3 vectorDeplasare = forward * this->moveSpeed * cameraPrivateSpeed;
#if CAMERA_DELTATIME_ACTIVE
	vectorDeplasare = forward * this->moveSpeed *deltaTime;
#endif
	
	this->position += vectorDeplasare;
	this->target += vectorDeplasare;
}

void Camera::moveOy(GLint distance)
{
	Vector3 forward = yAxis * distance;
	Vector3 vectorDeplasare = forward * this->moveSpeed * cameraPrivateSpeed;
#if CAMERA_DELTATIME_ACTIVE
	vectorDeplasare = forward * this->moveSpeed * deltaTime;
#endif
	
	this->position += vectorDeplasare;
	this->target += vectorDeplasare;
}

void Camera::moveOz(GLint distance)
{
	Vector3 forward = zAxis * distance;
	Vector3 vectorDeplasare = forward * this->moveSpeed * cameraPrivateSpeed;
#if CAMERA_DELTATIME_ACTIVE
	vectorDeplasare = forward * this->moveSpeed * deltaTime;
#endif
	this->position += vectorDeplasare;
	this->target += vectorDeplasare;
}

/* Camera rotation */
void Camera::rotateOx(GLint directie) {
	// Rotation matrix
	Matrix mRotateOX;
	mRotateOX.SetRotationX(rotateSpeed * directie * cameraPrivateSpeed);
#if CAMERA_DELTATIME_ACTIVE
	mRotateOX.SetRotationX(rotateSpeed * directie * deltaTime);
#endif
	Vector4 rotatedLocalUp = Vector4(0.0f, 1.0f, 0.0f, 0.0f) * mRotateOX;
	Vector4 up4 = rotatedLocalUp * worldMatrix;
	up = Vector3(up4.x, up4.y, up4.z).Normalize();
	Vector4 localTarget = Vector4(0.0f, 0.0f, -(target - position).Length(), 1.0f);
	Vector4 rotatedTarget = localTarget * mRotateOX;
	Vector4 target4 = rotatedTarget * worldMatrix;
	this->target = Vector3(target4.x, target4.y, target4.z);
	updateAxis();
}
void Camera::rotateOy(GLint directie) {
	Vector4 localTarget = Vector4(0.0f, 0.0f, -(target - position).Length(), 1.0f);
	Matrix mRotateOY;
	mRotateOY.SetRotationY(rotateSpeed * directie * cameraPrivateSpeed);
#if CAMERA_DELTATIME_ACTIVE
	mRotateOY.SetRotationY(rotateSpeed * directie * deltaTime);
#endif
	Vector4 rotatedTarget = localTarget * mRotateOY;
	Vector4 target4 = rotatedTarget * worldMatrix;
	this->target = Vector3(target4.x, target4.y, target4.z).Normalize();
	updateAxis();
}

void Camera::rotateOz(GLint directie) {
	Matrix mRotateOZ;
	mRotateOZ.SetRotationZ(rotateSpeed * directie * cameraPrivateSpeed);
#if CAMERA_DELTATIME_ACTIVE
	mRotateOZ.SetRotationZ(rotateSpeed * directie * deltaTime);
#endif
	Vector4 rotatedLocalUp = Vector4(0.0f, 1.0f, 0.0f, 0.0f) * mRotateOZ;
	Vector4 up4 = rotatedLocalUp * worldMatrix;
	up = Vector3(up4.x, up4.y, up4.z).Normalize();
	updateAxis();
}

/* World view */
void Camera::updateWorldView() {
	Matrix translatePosition;
	translatePosition.SetTranslation(position);
	Matrix mRot = Matrix(xAxis.x, xAxis.y, xAxis.z, 0, yAxis.x, yAxis.y, yAxis.z, 0, zAxis.x, zAxis.y, zAxis.z, 0, 0, 0, 0, 1);
	Matrix translatePositionInverse;
	translatePositionInverse.SetTranslation(Vector3(-position.x, -position.y, -position.z));
	this->worldMatrix = mRot * translatePosition;
	this->viewMatrix = translatePositionInverse * mRot.Transpose();
}
void Camera::updateAxis() {
	this->zAxis = -(this->target - this->position).Normalize();
	this->yAxis = this->up.Normalize();
	this->xAxis = this->zAxis.Cross(this->yAxis).Normalize();
}

void Camera::setPerspectiveMatrix()
{
	GLint screenWidth = allGlobals.screen_size.screenWidth;
	GLint screenHeight = allGlobals.screen_size.screenHeight;
	GLfloat aspect_ratio = (float)(screenWidth / screenHeight);
	this->perspectiveMatrix.SetPerspective(fov, aspect_ratio, nearC, farC);
}