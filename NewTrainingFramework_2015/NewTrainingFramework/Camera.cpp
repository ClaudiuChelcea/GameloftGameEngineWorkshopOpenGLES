#include <stdafx.h>
#include "Camera.h"
#include "Math.h"
#include "Globals.h"

// Constructor
Camera :: Camera(Vector3 position, Vector3 target, Vector3 up, GLfloat moveSpeed, GLfloat rotateSpeed, GLfloat nearC, GLfloat farC, GLfloat fov) {
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

Vector3 Camera :: getPosition() {
	return this->position;
}
void Camera :: setPosition(Vector3 position) {
	this->position = position;
}

Vector3 Camera :: getTarget() {
	return this->target;
}
void Camera :: setTarget() {
	this->target = target;
}

Vector3 Camera :: getUp() {
	return this->up;
}
void Camera :: setUp() {
	this->up = up;
}

GLfloat Camera :: getMoveSpeed() {
	return this->moveSpeed;
}
void Camera :: setMoveSpeed(GLfloat moveSpeed) {
	this->moveSpeed = moveSpeed;
}

GLfloat Camera :: getRotateSpeed() {
	return this->rotateSpeed;
}
void Camera :: setRotateSpeed(GLfloat rotateSpeed) {
	this->rotateSpeed = rotateSpeed;
}

GLfloat Camera :: getNear() {
	return this->nearC;
}
void Camera :: setNear(GLfloat nearC) {
	this->nearC = nearC;
}

GLfloat Camera :: getFar() {
	return this->farC;
}
void Camera :: setFar(GLfloat farC) {
	this->farC = farC;
}

GLfloat Camera :: getFov() {
	return this->fov;
}
void Camera :: setFov(GLfloat fov) {
	this->fov = fov;
}

Matrix Camera :: getWorldMatrix() {
	return this->worldMatrix;
}

Matrix Camera :: getViewMatrix() {
	return this->viewMatrix;
}

Matrix Camera::getPerspectiveMatrix() {
	return this->perspectiveMatrix;
}

void Camera::setPerspectiveMatrix() {
	GLint screenWidth = Globals :: screenWidth;
	GLint screenHeight = Globals :: screenHeight;
	GLfloat ar = (float) (screenWidth / screenHeight); 
	this->perspectiveMatrix.SetPerspective(fov, ar, nearC, farC);
}

void Camera::setDeltaTime(float _deltaTime)
{
	this->deltaTime = _deltaTime;
}

void Camera :: moveOx(GLint directie) {
	Vector3 forward = xAxis * directie;
	Vector3 vectorDeplasare = forward * this->moveSpeed * deltaTime;
	this->position += vectorDeplasare;
	this->target += vectorDeplasare;
}
void Camera :: moveOy(GLint directie) {
	Vector3 forward = yAxis * directie;
	Vector3 vectorDeplasare = forward * this->moveSpeed * deltaTime;
	this->position += vectorDeplasare;
	this->target += vectorDeplasare;
}
void Camera :: moveOz(GLint directie) {
	Vector3 forward = zAxis * directie;
	Vector3 vectorDeplasare = forward * this->moveSpeed * deltaTime;
	this->position += vectorDeplasare;
	this->target += vectorDeplasare;
}
void Camera :: rotateOx(GLint directie) {
	Matrix mRotateOX;
	mRotateOX.SetRotationX(rotateSpeed * directie * deltaTime);
	Vector4 rotatedLocalUp = Vector4(0.0f, 1.0f, 0.0f, 0.0f) * mRotateOX;
	Vector4 up4 = rotatedLocalUp * worldMatrix;
	up = Vector3(up4.x, up4.y, up4.z).Normalize();
	Vector4 localTarget = Vector4(0.0f, 0.0f, -(target - position).Length(), 1.0f);
	Vector4 rotatedTarget = localTarget * mRotateOX;
	Vector4 target4 = rotatedTarget * worldMatrix;
	this->target = Vector3(target4.x, target4.y, target4.z);
	updateAxis();
}
void Camera :: rotateOy(GLint directie) {
	Vector4 localTarget = Vector4(0.0f, 0.0f, -(target - position).Length(), 1.0f);
	Matrix mRotateOY;
	mRotateOY.SetRotationY(rotateSpeed * directie * deltaTime);
	Vector4 rotatedTarget = localTarget * mRotateOY;
	Vector4 target4 = rotatedTarget * worldMatrix;
	this->target = Vector3(target4.x, target4.y, target4.z).Normalize();
	updateAxis();
}
void Camera :: rotateOz(GLint directie) {
	Matrix mRotateOZ;
	mRotateOZ.SetRotationZ(rotateSpeed * directie * deltaTime);
	Vector4 rotatedLocalUp = Vector4(0.0f, 1.0f, 0.0f, 0.0f) * mRotateOZ;
	Vector4 up4 = rotatedLocalUp * worldMatrix;
	up = Vector3(up4.x, up4.y, up4.z).Normalize();
	updateAxis();
	
}
void Camera :: updateWorldView() {
	Matrix translatePosition;
	translatePosition.SetTranslation(position);
	Matrix mRot = Matrix(xAxis.x, xAxis.y, xAxis.z, 0, yAxis.x, yAxis.y, yAxis.z, 0, zAxis.x, zAxis.y, zAxis.z, 0, 0, 0, 0, 1);
	Matrix translatePositionInverse;
	translatePositionInverse.SetTranslation(Vector3(-position.x, -position.y, -position.z));
	this->worldMatrix = mRot * translatePosition;
	this->viewMatrix = translatePositionInverse * mRot.Transpose();
}
void Camera :: updateAxis() {
	this->zAxis = -(this->target - this->position).Normalize();
	this->yAxis = this->up.Normalize();
	this->xAxis = this->zAxis.Cross(this->yAxis).Normalize();
}