// Main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Vertex.h"
#include "Shaders.h"
#include <conio.h>
#include "Globals.h"
#include <iostream>

GLuint vboId;
Shaders myTriangleShader;
Globals allGlobals;

int Init ( ESContext *esContext )
{
	glClearColor ( 0.0f, 0.0f, 0.0f, 0.0f );

	/* DEBUG */ 
	if (allGlobals.DEBUGGER.DEBUG_BACKGROUND) {
		glClearColor(0.0f, 1.0f, 0.0f, 0.0f);
	}

	// Triangle data
	Vertex verticesData[3];

	// Top vertex
	verticesData[0].pos.x =  0.0f;  verticesData[0].pos.y =  0.5f;  verticesData[0].pos.z =  0.0f;
	verticesData[0].color.x = 1.0f;  verticesData[0].color.y = 0.0f;  verticesData[0].color.z = 0.0f;

	// Left vertex
	verticesData[1].pos.x = -0.5f;  verticesData[1].pos.y = -0.5f;  verticesData[1].pos.z =  0.0f;
	verticesData[1].color.x = 0.0f;  verticesData[1].color.y = 1.0f;  verticesData[1].color.z = 0.0f;

	// Right vertex
	verticesData[2].pos.x =  0.5f;  verticesData[2].pos.y = -0.5f;  verticesData[2].pos.z =  0.0f;
	verticesData[2].color.x = 0.0f;  verticesData[2].color.y = 0.0f;  verticesData[2].color.z = 1.0f;

	// Buffer object
	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesData), verticesData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Creation of shaders and program 
	int triangleStatus = myTriangleShader.Init("../Resources/Shaders/TriangleShaderVS.glsl", "../Resources/Shaders/TriangleShaderFS.glsl");
	if (triangleStatus != 0) {
		std::cerr << "Error creating triangle!\n";
	}

	return triangleStatus;
}

void Draw ( ESContext *esContext )
{ 
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(myTriangleShader.program);

	glBindBuffer(GL_ARRAY_BUFFER, vboId);

	size_t memory_used = 0;

	// Send position
	if(myTriangleShader.positionAttribute != -1)
	{
		glEnableVertexAttribArray(myTriangleShader.positionAttribute);
		glVertexAttribPointer(myTriangleShader.positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*) memory_used);
		memory_used += sizeof(Vector3);
	}

	// Send color
	if (myTriangleShader.colorAttribute != -1)
	{
		glEnableVertexAttribArray(myTriangleShader.colorAttribute);
		glVertexAttribPointer(myTriangleShader.colorAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*) memory_used);
		memory_used += sizeof(Vector3);
	}

	// Camera rotation (matrix uniform)
	Matrix m;
	m.SetRotationZ(0);
	if (myTriangleShader.matrixUniform != -1)
	{
		glUniformMatrix4fv(myTriangleShader.matrixUniform, 1, GL_FALSE, (GLfloat*)m.m);
	}

	// Camera perspective
	Matrix cameraPerspective = allGlobals.myCamera.getPerspectiveMatrix();
	if (myTriangleShader.perspectiveUniform != -1)
	{
		glUniformMatrix4fv(myTriangleShader.perspectiveUniform, 1, GL_FALSE, (GLfloat*)cameraPerspective.m);
	}

	// Camera view
	Matrix cameraView = allGlobals.myCamera.getViewMatrix();
	if (myTriangleShader.viewUniform != -1)
	{
		glUniformMatrix4fv(myTriangleShader.viewUniform, 1, GL_FALSE, (GLfloat*) cameraView.m);
	}

	// Add rotation to the triangle
	Matrix rotationOfTriangle;
	rotationOfTriangle.SetRotationZ(allGlobals.rotationAngle += allGlobals.rotationAngleIncreaseSpeed);

	if (myTriangleShader.rotationUniform != -1)
	{
		glUniformMatrix4fv(myTriangleShader.rotationUniform, 1, GL_FALSE, (GLfloat*) rotationOfTriangle.m);
	}

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	eglSwapBuffers ( esContext->eglDisplay, esContext->eglSurface );
}

void Update ( ESContext *esContext, float deltaTime )
{
	/* Send info to allGlobals.myCamera */
	// Limit update
	#if LOCK_UPDATE
	allGlobals.currentTime += deltaTime;
	if (allGlobals.currentTime > allGlobals.maxTime) {
		allGlobals.currentTime = 0.0f;
		return;
	}
	#endif
	allGlobals.myCamera.setDeltaTime(deltaTime);
}

void Key ( ESContext *esContext, unsigned char key, bool bIsPressed)
{
	/* Update allGlobals.myCamera */
	// WASD movement
	if (key == "W"[0] || key == "w"[0]) {
		allGlobals.myCamera.moveOy(allGlobals.myCamera.getMoveSpeed());
		allGlobals.myCamera.updateWorldView();
	}

	if (key == "S"[0] || key == "s"[0]) {
		allGlobals.myCamera.moveOy(-allGlobals.myCamera.getMoveSpeed());
		allGlobals.myCamera.updateWorldView();
	}

	if (key == "A"[0] || key == "a"[0]) {
		allGlobals.myCamera.moveOx(-allGlobals.myCamera.getMoveSpeed());
		allGlobals.myCamera.updateWorldView();
	}

	if (key == "D"[0] || key == "d"[0]) {
		allGlobals.myCamera.moveOx(allGlobals.myCamera.getMoveSpeed());
		allGlobals.myCamera.updateWorldView();
	}

	// ZOOM IN AND OUT
	if (key == "Z"[0] || key == "z"[0]) {
		allGlobals.myCamera.moveOz(allGlobals.myCamera.getMoveSpeed());
		allGlobals.myCamera.updateWorldView();
	}

	if (key == "X"[0] || key == "x"[0]) {
		allGlobals.myCamera.moveOz(-allGlobals.myCamera.getMoveSpeed());
		allGlobals.myCamera.updateWorldView();
	}

	// ROTATE CAMERA
	if (key == "F"[0] || key == "f"[0]) {
		allGlobals.myCamera.rotateOy(allGlobals.myCamera.getMoveSpeed());
		allGlobals.myCamera.updateWorldView();
	}

	if (key == "G"[0] || key == "g"[0]) {
		allGlobals.myCamera.rotateOy(-allGlobals.myCamera.getMoveSpeed());
		allGlobals.myCamera.updateWorldView();
	}

	if (key == "H"[0] || key == "h"[0]) {
		allGlobals.myCamera.rotateOx(allGlobals.myCamera.getMoveSpeed());
		allGlobals.myCamera.updateWorldView();
	}

	if (key == "J"[0] || key == "j"[0]) {
		allGlobals.myCamera.rotateOx(-allGlobals.myCamera.getMoveSpeed());
		allGlobals.myCamera.updateWorldView();
	}

	if (key == "K"[0] || key == "k"[0]) {
		allGlobals.myCamera.rotateOz(allGlobals.myCamera.getMoveSpeed());
		allGlobals.myCamera.updateWorldView();
	}

	if (key == "L"[0] || key == "l"[0]) {
		allGlobals.myCamera.rotateOz(-allGlobals.myCamera.getMoveSpeed());
		allGlobals.myCamera.updateWorldView();
	}
}

void CleanUp()
{
	glDeleteBuffers(1, &vboId);
}

int _tmain(int argc, _TCHAR* argv[])
{
	//identifying memory leaks
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF ); 

	ESContext esContext;

    esInitContext ( &esContext );

	esCreateWindow ( &esContext, allGlobals.screenTitle.c_str(), allGlobals.screen_size.screenWidth, allGlobals.screen_size.screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);

	if ( Init ( &esContext ) != 0 )
		return 0;

	esRegisterDrawFunc ( &esContext, Draw );
	esRegisterUpdateFunc ( &esContext, Update );
	esRegisterKeyFunc ( &esContext, Key);

	esMainLoop ( &esContext );

	//releasing OpenGL resources
	CleanUp();

	printf("Press any key...\n");
	_getch();

	return 0;
}

