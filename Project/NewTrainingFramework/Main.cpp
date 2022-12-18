// Main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Vertex.h"
#include "Shaders.h"
#include <conio.h>
#include "Globals.h"
#include <iostream>

Globals allGlobals;

int Init ( ESContext *esContext )
{
	glClearColor ( 0.0f, 0.0f, 0.0f, 0.0f );

	/* DEBUG */ 
	if (allGlobals.DEBUGGER.DEBUG_BACKGROUND) {
		glClearColor(0.0f, 1.0f, 0.0f, 0.0f);
	}

/* ------------------------------------ TRIANGLE ------------------------------------ */
#if DRAW_TRIANGLE
	// Triangle data
	Vertex verticesDataTriangle[3];

	// Top vertex
	verticesDataTriangle[0].pos.x =  0.0f;  verticesDataTriangle[0].pos.y =  0.5f;  verticesDataTriangle[0].pos.z =  0.0f;
	verticesDataTriangle[0].color.x = 1.0f;  verticesDataTriangle[0].color.y = 0.0f;  verticesDataTriangle[0].color.z = 0.0f;

	// Left vertex
	verticesDataTriangle[1].pos.x = -0.5f;  verticesDataTriangle[1].pos.y = -0.5f;  verticesDataTriangle[1].pos.z =  0.0f;
	verticesDataTriangle[1].color.x = 0.0f;  verticesDataTriangle[1].color.y = 1.0f;  verticesDataTriangle[1].color.z = 0.0f;

	// Right vertex
	verticesDataTriangle[2].pos.x =  0.5f;  verticesDataTriangle[2].pos.y = -0.5f;  verticesDataTriangle[2].pos.z =  0.0f;
	verticesDataTriangle[2].color.x = 0.0f;  verticesDataTriangle[2].color.y = 0.0f;  verticesDataTriangle[2].color.z = 1.0f;

	// Buffer object
	glGenBuffers(1, &allGlobals.vboIdTriangle);
	glBindBuffer(GL_ARRAY_BUFFER, allGlobals.vboIdTriangle);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesDataTriangle), verticesDataTriangle, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Creation of shaders and program 
	int triangleStatus = allGlobals.myTriangleShader.Init("../Resources/Shaders/TriangleShaderVS.glsl", "../Resources/Shaders/TriangleShaderFS.glsl");
	if (triangleStatus != 0) {
		std::cerr << "Error creating triangle!\n";
	}

#endif
/* ------------------------------------ TRIANGLE ------------------------------------ */

/* ------------------------------------ RECTANGLE ------------------------------------ */
#if DRAW_RECTANGLE3D
#if VBO	== true
	Vertex verticesDataRectangle[12];

	/* DOWN */
	// Down - position
	verticesDataRectangle[0].pos.x = 0.0f;  verticesDataRectangle[0].pos.y = 0.0f;  verticesDataRectangle[0].pos.z = 0.0f;
	verticesDataRectangle[1].pos.x = -0.5f;  verticesDataRectangle[1].pos.y = -0.5f;  verticesDataRectangle[1].pos.z = 0.0f;
	verticesDataRectangle[2].pos.x = 0.5f;  verticesDataRectangle[2].pos.y = -0.5f;  verticesDataRectangle[2].pos.z = 0.0f;

	// Down - color
	verticesDataRectangle[0].color.x = 0.0f;  verticesDataRectangle[0].color.y = 0.0f;  verticesDataRectangle[0].color.z = 0.0f;
	verticesDataRectangle[1].color.x = 1.0f;  verticesDataRectangle[1].color.y = 1.0f;  verticesDataRectangle[1].color.z = 0.0f;
	verticesDataRectangle[2].color.x = 0.0f;  verticesDataRectangle[2].color.y = 1.0f;  verticesDataRectangle[2].color.z = 0.0f;

	/* UP */
	// Up - position
	verticesDataRectangle[3].pos.x = 0.0f;  verticesDataRectangle[3].pos.y = 0.0f;  verticesDataRectangle[3].pos.z = 0.0f;
	verticesDataRectangle[4].pos.x = -0.5f;  verticesDataRectangle[4].pos.y = 0.5f;  verticesDataRectangle[4].pos.z = 0.0f;
	verticesDataRectangle[5].pos.x = 0.5f;  verticesDataRectangle[5].pos.y = 0.5f;  verticesDataRectangle[5].pos.z = 0.0f;

	// Up - color
	verticesDataRectangle[3].color.x = 0.0f;  verticesDataRectangle[3].color.y = 0.0f;  verticesDataRectangle[3].color.z = 0.0f;
	verticesDataRectangle[4].color.x = 1.0f;  verticesDataRectangle[4].color.y = 0.0f;  verticesDataRectangle[4].color.z = 0.0f;
	verticesDataRectangle[5].color.x = 0.0f;  verticesDataRectangle[5].color.y = 0.0f;  verticesDataRectangle[5].color.z = 1.0f;

	/* LEFT */
	// Left - position
	verticesDataRectangle[6].pos.x = 0.0f;  verticesDataRectangle[6].pos.y = 0.0f;  verticesDataRectangle[6].pos.z = 0.0f;
	verticesDataRectangle[7].pos.x = 0.5f;  verticesDataRectangle[7].pos.y = 0.5f;  verticesDataRectangle[7].pos.z = 0.0f;
	verticesDataRectangle[8].pos.x = 0.5f;  verticesDataRectangle[8].pos.y = -0.5f;  verticesDataRectangle[8].pos.z = 0.0f;

	// Left - color
	verticesDataRectangle[6].color.x = 0.0f;  verticesDataRectangle[6].color.y = 0.0f;  verticesDataRectangle[6].color.z = 0.0f;
	verticesDataRectangle[7].color.x = 0.0f;  verticesDataRectangle[7].color.y = 0.0f;  verticesDataRectangle[7].color.z = 1.0f;
	verticesDataRectangle[8].color.x = 0.0f;  verticesDataRectangle[8].color.y = 1.0f;  verticesDataRectangle[8].color.z = 0.0f;

	/* RIGHT */
	// Right - position
	verticesDataRectangle[9].pos.x = 0.0f;  verticesDataRectangle[9].pos.y = 0.0f;  verticesDataRectangle[9].pos.z = 0.0f;
	verticesDataRectangle[10].pos.x = -0.5f;  verticesDataRectangle[10].pos.y = 0.5f;  verticesDataRectangle[10].pos.z = 0.0f;
	verticesDataRectangle[11].pos.x = -0.5f;  verticesDataRectangle[11].pos.y = -0.5f;  verticesDataRectangle[11].pos.z = 0.0f;

	// Right - color
	verticesDataRectangle[9].color.x = 0.0f;  verticesDataRectangle[9].color.y = 0.0f;  verticesDataRectangle[9].color.z = 0.0f;
	verticesDataRectangle[10].color.x = 1.0f;  verticesDataRectangle[10].color.y = 0.0f;  verticesDataRectangle[10].color.z = 0.0f;
	verticesDataRectangle[11].color.x = 1.0f;  verticesDataRectangle[11].color.y = 1.0f;  verticesDataRectangle[11].color.z = 0.0f;

	// Buffer object
	glGenBuffers(1, &allGlobals.vboIdRectangle3D);
	glBindBuffer(GL_ARRAY_BUFFER, allGlobals.vboIdRectangle3D);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesDataRectangle), verticesDataRectangle, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
#else
	Vertex verticesDataRectangle[5];

	/* DOWN */
	// Down - position
	verticesDataRectangle[0].pos.x = 0.0f;  verticesDataRectangle[0].pos.y = 0.0f;  verticesDataRectangle[0].pos.z = 0.0f; // A
	verticesDataRectangle[1].pos.x = -0.5f;  verticesDataRectangle[1].pos.y = -0.5f;  verticesDataRectangle[1].pos.z = 0.0f; // B
	verticesDataRectangle[2].pos.x = 0.5f;  verticesDataRectangle[2].pos.y = -0.5f;  verticesDataRectangle[2].pos.z = 0.0f; // C

	// Down - color
	verticesDataRectangle[0].color.x = 0.0f;  verticesDataRectangle[0].color.y = 0.0f;  verticesDataRectangle[0].color.z = 0.0f;
	verticesDataRectangle[1].color.x = 1.0f;  verticesDataRectangle[1].color.y = 1.0f;  verticesDataRectangle[1].color.z = 0.0f;
	verticesDataRectangle[2].color.x = 0.0f;  verticesDataRectangle[2].color.y = 1.0f;  verticesDataRectangle[2].color.z = 0.0f;

	/* UP */
	// Up - position
	verticesDataRectangle[3].pos.x = -0.5f;  verticesDataRectangle[3].pos.y = 0.5f;  verticesDataRectangle[3].pos.z = 0.0f; // D
	verticesDataRectangle[4].pos.x = 0.5f;  verticesDataRectangle[4].pos.y = 0.5f;  verticesDataRectangle[4].pos.z = 0.0f; // E

	// Up - color
	verticesDataRectangle[3].color.x = 1.0f;  verticesDataRectangle[3].color.y = 0.0f;  verticesDataRectangle[3].color.z = 0.0f;
	verticesDataRectangle[4].color.x = 0.0f;  verticesDataRectangle[4].color.y = 0.0f;  verticesDataRectangle[4].color.z = 1.0f;

	unsigned int indices[]
	{
		0,1,2,
		0,3,4,
		0,4,2,
		0,3,1
	};

	// Buffer object
	glGenBuffers(1, &allGlobals.vboIdRectangle3D);
	glBindBuffer(GL_ARRAY_BUFFER, allGlobals.vboIdRectangle3D);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesDataRectangle), verticesDataRectangle, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Buffer object
	glGenBuffers(1, &allGlobals.iboIdRectangle3D);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, allGlobals.iboIdRectangle3D);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
#endif
	// Creation of shaders and program 
	int rectangleStatus = allGlobals.myRectangle3DShader.Init("../Resources/Shaders/Rectangle3DShaderVS.glsl", "../Resources/Shaders/Rectangle3DShaderFS.glsl");
	if (rectangleStatus != 0) {
		std::cerr << "Error creating rectangle!\n";
	}
#endif
/* ------------------------------------ RECTANGLE ------------------------------------ */

/* ------------------------------------ SQUARE ------------------------------------ */
#if DRAW_SQUARE
	Vertex verticesDataSquare[6];

	/* DOWN */
	// Down - position
	verticesDataSquare[0].pos.x = 0.0f;  verticesDataSquare[0].pos.y = 0.0f;  verticesDataSquare[0].pos.z = 0.0f;
	verticesDataSquare[1].pos.x = 0.0f;  verticesDataSquare[1].pos.y = 1.0f;  verticesDataSquare[1].pos.z = 0.0f;
	verticesDataSquare[2].pos.x = 1.0f;  verticesDataSquare[2].pos.y = 0.0f;  verticesDataSquare[2].pos.z = 0.0f;

	// Down - color
	verticesDataSquare[0].color.x = 1.0f;  verticesDataSquare[0].color.y = 1.0f;  verticesDataSquare[0].color.z = 0.0f;
	verticesDataSquare[1].color.x = 1.0f;  verticesDataSquare[1].color.y = 1.0f;  verticesDataSquare[1].color.z = 0.0f;
	verticesDataSquare[2].color.x = 0.0f;  verticesDataSquare[2].color.y = 1.0f;  verticesDataSquare[2].color.z = 0.0f;

	/* UP */
	// Up - position
	verticesDataSquare[3].pos.x = 0.0f;  verticesDataSquare[3].pos.y = 1.0f;  verticesDataSquare[3].pos.z = 0.0f;
	verticesDataSquare[4].pos.x = 1.0f;  verticesDataSquare[4].pos.y = 0.0f;  verticesDataSquare[4].pos.z = 0.0f;
	verticesDataSquare[5].pos.x = 1.0f;  verticesDataSquare[5].pos.y = 1.0f;  verticesDataSquare[5].pos.z = 0.0f;

	// Up - color
	verticesDataSquare[3].color.x = 1.0f;  verticesDataSquare[3].color.y = 0.0f;  verticesDataSquare[3].color.z = 0.0f;
	verticesDataSquare[4].color.x = 1.0f;  verticesDataSquare[4].color.y = 1.0f;  verticesDataSquare[4].color.z = 1.0f;
	verticesDataSquare[5].color.x = 0.0f;  verticesDataSquare[5].color.y = 0.0f;  verticesDataSquare[5].color.z = 1.0f;

	// Buffer object
	glGenBuffers(1, &allGlobals.vboIdSquare);
	glBindBuffer(GL_ARRAY_BUFFER, allGlobals.vboIdSquare);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesDataSquare), verticesDataSquare, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Creation of shaders and program 
	int SquareStatus = allGlobals.mySquareShader.Init("../Resources/Shaders/SquareShaderVS.glsl", "../Resources/Shaders/SquareShaderFS.glsl");
	if (SquareStatus != 0) {
		std::cerr << "Error creating Square!\n";
	}
#endif
/* ------------------------------------ SQUARE ------------------------------------ */

/* ------------------------------------ MIDDLE LINE ------------------------------------ */
#if DRAW_MIDDLE_LINE
	Vertex verticesDataMiddleLine[2];

	/* DOWN */
	// Down - position
	verticesDataMiddleLine[0].pos.x = 0.0f;  verticesDataMiddleLine[0].pos.y = 1.0f;  verticesDataMiddleLine[0].pos.z = 0.0f;
	verticesDataMiddleLine[1].pos.x = 0.0f;  verticesDataMiddleLine[1].pos.y = -1.0f;  verticesDataMiddleLine[1].pos.z = 0.0f;

	// Down - color
	verticesDataMiddleLine[0].color.x = 1.0f;  verticesDataMiddleLine[0].color.y = 1.0f;  verticesDataMiddleLine[0].color.z = 1.0f;
	verticesDataMiddleLine[1].color.x = 1.0f;  verticesDataMiddleLine[1].color.y = 1.0f;  verticesDataMiddleLine[1].color.z = 1.0f;

	// Buffer object
	glGenBuffers(1, &allGlobals.vboIdMiddleLine);
	glBindBuffer(GL_ARRAY_BUFFER, allGlobals.vboIdMiddleLine);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesDataMiddleLine), verticesDataMiddleLine, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Creation of shaders and program 
	int MiddleLineStatus = allGlobals.myMiddleLineShader.Init("../Resources/Shaders/MiddleLineShaderVS.glsl", "../Resources/Shaders/MiddleLineShaderFS.glsl");
	if (MiddleLineStatus != 0) {
		std::cerr << "Error creating MiddleLine!\n";
	}
#endif
/* ------------------------------------ MIDDLE LINE ------------------------------------ */

/* ------------------------------------ CROCODILE ------------------------------------ */
#if DRAW_CROCODILE
	allGlobals.myCrocodile.InitNFG(allGlobals.myCrocodile.openFile(allGlobals.myCrocodile.getModelPath().c_str())); // NFT and scanning
	glGenTextures(1, &allGlobals.crocodileTextureID);

	// Creation of shaders and program 
	int CrocodileStatus = allGlobals.myCrocodileShader.Init("../Resources/Shaders/CrocodileShaderVS.glsl", "../Resources/Shaders/CrocodileShaderFS.glsl");
	if (CrocodileStatus != 0) {
		std::cerr << "Error creating Crocodile!\n";
	}

	glBindTexture(GL_TEXTURE_2D, allGlobals.crocodileTextureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	allGlobals.TGA_ANSWER = LoadTGA("../../Resources/Textures/Croco.tga", &allGlobals.width, &allGlobals.height, &allGlobals.bpp);
	if (allGlobals.TGA_ANSWER == NULL) {
		std::cerr << "Couldn't load Croco tga!\n";
		std::abort();
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (GLint)allGlobals.width, (GLint)allGlobals.height, 0, GL_RGBA,
	GL_UNSIGNED_BYTE, allGlobals.TGA_ANSWER);

	glActiveTexture(GL_TEXTURE0);

	glEnable(GL_DEPTH_TEST);
#endif
/* ------------------------------------ CROCODILE ------------------------------------ */

	// Check if anything is being drawn at all
	#if DRAW_TRIANGLE == false && DRAW_RECTANGLE3D == false && DRAW_SQUARE == false && DRAW_MIDDLE_LINE == false && DRAW_CROCODILE == false
		std::cerr << "Error! Nothing is being drawn on the screen!\n";
		return -1;
	#endif

#if ENABLE_XML
		allGlobals.myXMLreader.printMe();
#endif


	return 0;
}

void Draw ( ESContext *esContext )
{ 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Variables
	size_t memory_used = 0;
	Matrix cameraPerspective;
	Matrix m;
	Matrix cameraView;
/* ------------------------------------ TRIANGLE ------------------------------------ */
#if DRAW_TRIANGLE
	glUseProgram(allGlobals.myTriangleShader.program);

	glBindBuffer(GL_ARRAY_BUFFER, allGlobals.vboIdTriangle);

	memory_used = 0;

	// Send position
	if(allGlobals.myTriangleShader.positionAttribute != -1)
	{
		glEnableVertexAttribArray(allGlobals.myTriangleShader.positionAttribute);
		glVertexAttribPointer(allGlobals.myTriangleShader.positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*) memory_used);
		memory_used += sizeof(Vector3);
	}

	// Send color
	if (allGlobals.myTriangleShader.colorAttribute != -1)
	{
		glEnableVertexAttribArray(allGlobals.myTriangleShader.colorAttribute);
		glVertexAttribPointer(allGlobals.myTriangleShader.colorAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*) memory_used);
		memory_used += sizeof(Vector3);
	}

	// Camera rotation (matrix uniform)
	m.SetRotationZ(0);
	if (allGlobals.myTriangleShader.matrixUniform != -1)
	{
		glUniformMatrix4fv(allGlobals.myTriangleShader.matrixUniform, 1, GL_FALSE, (GLfloat*)m.m);
	}

	// Camera perspective
	cameraPerspective = allGlobals.myCamera.getPerspectiveMatrix();
	if (allGlobals.myTriangleShader.perspectiveUniform != -1)
	{
		glUniformMatrix4fv(allGlobals.myTriangleShader.perspectiveUniform, 1, GL_FALSE, (GLfloat*)cameraPerspective.m);
	}

	// Camera view
	cameraView = allGlobals.myCamera.getViewMatrix();
	if (allGlobals.myTriangleShader.viewUniform != -1)
	{
		glUniformMatrix4fv(allGlobals.myTriangleShader.viewUniform, 1, GL_FALSE, (GLfloat*) cameraView.m);
	}

	// Add rotation to the triangle
	Matrix rotationOfTriangle;
#if ENFORCE_ROTATION == false
	rotationOfTriangle.SetRotationZ(allGlobals.rotationAngle += allGlobals.rotationAngleIncreaseSpeed);
#else 
	rotationOfTriangle.SetRotationZ(allGlobals.enforcedRotation);
#endif

	if (allGlobals.myTriangleShader.rotationUniform != -1)
	{
		glUniformMatrix4fv(allGlobals.myTriangleShader.rotationUniform, 1, GL_FALSE, (GLfloat*) rotationOfTriangle.m);
	}

	glDrawArrays(GL_TRIANGLES, 0, 3);

#endif
/* ------------------------------------ TRIANGLE ------------------------------------ */

/* ------------------------------------ RECTANGLE ------------------------------------ */
#if DRAW_RECTANGLE3D
#if VBO == true
	glUseProgram(allGlobals.myRectangle3DShader.program);

	glBindBuffer(GL_ARRAY_BUFFER, allGlobals.vboIdRectangle3D);

	memory_used = 0;

	// Send position
	if (allGlobals.myRectangle3DShader.positionAttribute != -1)
	{
		glEnableVertexAttribArray(allGlobals.myRectangle3DShader.positionAttribute);
		glVertexAttribPointer(allGlobals.myRectangle3DShader.positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)memory_used);
		memory_used += sizeof(Vector3);
	}

	// Send color
	if (allGlobals.myRectangle3DShader.colorAttribute != -1)
	{
		glEnableVertexAttribArray(allGlobals.myRectangle3DShader.colorAttribute);
		glVertexAttribPointer(allGlobals.myRectangle3DShader.colorAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)memory_used);
		memory_used += sizeof(Vector3);
	}

	// Camera rotation (matrix uniform)
	m.SetRotationZ(0);
	if (allGlobals.myRectangle3DShader.matrixUniform != -1)
	{
		glUniformMatrix4fv(allGlobals.myRectangle3DShader.matrixUniform, 1, GL_FALSE, (GLfloat*)m.m);
	}

	// Camera perspective
	cameraPerspective = allGlobals.myCamera.getPerspectiveMatrix();
	if (allGlobals.myRectangle3DShader.perspectiveUniform != -1)
	{
		glUniformMatrix4fv(allGlobals.myRectangle3DShader.perspectiveUniform, 1, GL_FALSE, (GLfloat*)cameraPerspective.m);
	}

	// Camera view
	cameraView = allGlobals.myCamera.getViewMatrix();
	if (allGlobals.myRectangle3DShader.viewUniform != -1)
	{
		glUniformMatrix4fv(allGlobals.myRectangle3DShader.viewUniform, 1, GL_FALSE, (GLfloat*)cameraView.m);
	}

	// Add rotation to the rectangle
	Matrix rotationOfRectangle3D;
#if ENFORCE_ROTATION == false
	rotationOfRectangle3D.SetRotationZ(allGlobals.rotationAngleRectangle3D += allGlobals.rotationAngleIncreaseSpeedRectangle3D);
#else 
	rotationOfRectangle3D.SetRotationZ(allGlobals.enforcedRotation);
#endif

	if (allGlobals.myRectangle3DShader.rotationUniform != -1)
	{
		glUniformMatrix4fv(allGlobals.myRectangle3DShader.rotationUniform, 1, GL_FALSE, (GLfloat*)rotationOfRectangle3D.m);
	}

	glDrawArrays(GL_TRIANGLES, 0, 12);
#else 
	glUseProgram(allGlobals.myRectangle3DShader.program);
	glBindBuffer(GL_ARRAY_BUFFER, allGlobals.vboIdRectangle3D);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, allGlobals.iboIdRectangle3D);

	memory_used = 0;

	// Send position
	if (allGlobals.myRectangle3DShader.positionAttribute != -1)
	{
		glEnableVertexAttribArray(allGlobals.myRectangle3DShader.positionAttribute);
		glVertexAttribPointer(allGlobals.myRectangle3DShader.positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)memory_used);
		memory_used += sizeof(Vector3);
	}

	// Send color
	if (allGlobals.myRectangle3DShader.colorAttribute != -1)
	{
		glEnableVertexAttribArray(allGlobals.myRectangle3DShader.colorAttribute);
		glVertexAttribPointer(allGlobals.myRectangle3DShader.colorAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)memory_used);
		memory_used += sizeof(Vector3);
	}

	// Camera rotation (matrix uniform)
	m.SetRotationZ(0);
	if (allGlobals.myRectangle3DShader.matrixUniform != -1)
	{
		glUniformMatrix4fv(allGlobals.myRectangle3DShader.matrixUniform, 1, GL_FALSE, (GLfloat*)m.m);
	}

	// Camera perspective
	cameraPerspective = allGlobals.myCamera.getPerspectiveMatrix();
	if (allGlobals.myRectangle3DShader.perspectiveUniform != -1)
	{
		glUniformMatrix4fv(allGlobals.myRectangle3DShader.perspectiveUniform, 1, GL_FALSE, (GLfloat*)cameraPerspective.m);
	}

	// Camera view
	cameraView = allGlobals.myCamera.getViewMatrix();
	if (allGlobals.myRectangle3DShader.viewUniform != -1)
	{
		glUniformMatrix4fv(allGlobals.myRectangle3DShader.viewUniform, 1, GL_FALSE, (GLfloat*)cameraView.m);
	}

	// Add rotation to the rectangle
	Matrix rotationOfRectangle3D;
#if ENFORCE_ROTATION == false
	rotationOfRectangle3D.SetRotationZ(allGlobals.rotationAngleRectangle3D += allGlobals.rotationAngleIncreaseSpeedRectangle3D);
#else 
	rotationOfRectangle3D.SetRotationZ(allGlobals.enforcedRotation);
#endif

	if (allGlobals.myRectangle3DShader.rotationUniform != -1)
	{
		glUniformMatrix4fv(allGlobals.myRectangle3DShader.rotationUniform, 1, GL_FALSE, (GLfloat*)rotationOfRectangle3D.m);
	}

	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, nullptr);
#endif
#endif

/* ------------------------------------ RECTANGLE ------------------------------------ */

/* ------------------------------------ SQUARE ------------------------------------ */
#if DRAW_SQUARE
	glUseProgram(allGlobals.mySquareShader.program);

	glBindBuffer(GL_ARRAY_BUFFER, allGlobals.vboIdSquare);

	memory_used = 0;

	// Send position
	if (allGlobals.mySquareShader.positionAttribute != -1)
	{
		glEnableVertexAttribArray(allGlobals.mySquareShader.positionAttribute);
		glVertexAttribPointer(allGlobals.mySquareShader.positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)memory_used);
		memory_used += sizeof(Vector3);
	}

	// Send color
	if (allGlobals.mySquareShader.colorAttribute != -1)
	{
		glEnableVertexAttribArray(allGlobals.mySquareShader.colorAttribute);
		glVertexAttribPointer(allGlobals.mySquareShader.colorAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)memory_used);
		memory_used += sizeof(Vector3);
	}

	// Camera rotation (matrix uniform)
	m.SetRotationZ(0);
	if (allGlobals.mySquareShader.matrixUniform != -1)
	{
		glUniformMatrix4fv(allGlobals.mySquareShader.matrixUniform, 1, GL_FALSE, (GLfloat*)m.m);
	}

	// Camera perspective
	cameraPerspective = allGlobals.myCamera.getPerspectiveMatrix();
	if (allGlobals.mySquareShader.perspectiveUniform != -1)
	{
		glUniformMatrix4fv(allGlobals.mySquareShader.perspectiveUniform, 1, GL_FALSE, (GLfloat*)cameraPerspective.m);
	}

	// Camera view
	cameraView = allGlobals.myCamera.getViewMatrix();
	if (allGlobals.mySquareShader.viewUniform != -1)
	{
		glUniformMatrix4fv(allGlobals.mySquareShader.viewUniform, 1, GL_FALSE, (GLfloat*)cameraView.m);
	}

	// Add rotation to the rectangle
	Matrix rotationOfSquare;
#if ENFORCE_ROTATION == false
	rotationOfSquare.SetRotationZ(allGlobals.rotationAngleSquare += allGlobals.rotationAngleIncreaseSpeedSquare);
#else 
	rotationOfSquare.SetRotationZ(allGlobals.enforcedRotation);
#endif
	
	if (allGlobals.mySquareShader.rotationUniform != -1)
	{
		glUniformMatrix4fv(allGlobals.mySquareShader.rotationUniform, 1, GL_FALSE, (GLfloat*)rotationOfSquare.m);
	}

	glDrawArrays(GL_TRIANGLES, 0, 6);

#endif
/* ------------------------------------ SQUARE ------------------------------------ */

/* ------------------------------------ MIDDLE LINE ------------------------------------ */
#if DRAW_MIDDLE_LINE
	glUseProgram(allGlobals.myMiddleLineShader.program);

	glBindBuffer(GL_ARRAY_BUFFER, allGlobals.vboIdMiddleLine);

	memory_used = 0;

	// Send position
	if (allGlobals.myMiddleLineShader.positionAttribute != -1)
	{
		glEnableVertexAttribArray(allGlobals.myMiddleLineShader.positionAttribute);
		glVertexAttribPointer(allGlobals.myMiddleLineShader.positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)memory_used);
		memory_used += sizeof(Vector3);
	}

	// Send color
	if (allGlobals.myMiddleLineShader.colorAttribute != -1)
	{
		glEnableVertexAttribArray(allGlobals.myMiddleLineShader.colorAttribute);
		glVertexAttribPointer(allGlobals.myMiddleLineShader.colorAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)memory_used);
		memory_used += sizeof(Vector3);
	}

	glDrawArrays(GL_LINES, 0, 2);

#endif
/* ------------------------------------ MIDDLE LINE ------------------------------------ */

/* ------------------------------------ CROCODILE ------------------------------------ */
#if DRAW_CROCODILE
	glUseProgram(allGlobals.myCrocodileShader.program);

	glBindBuffer(GL_ARRAY_BUFFER, allGlobals.myCrocodile.getVBO());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, allGlobals.myCrocodile.getIBO());
	
	memory_used = 0;

	// Send position
	if (allGlobals.myCrocodileShader.positionAttribute != -1)
	{
		glEnableVertexAttribArray(allGlobals.myCrocodileShader.positionAttribute);
		glVertexAttribPointer(allGlobals.myCrocodileShader.positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)memory_used);
		memory_used += sizeof(Vector3);
	}

	// Camera perspective
	cameraPerspective = allGlobals.myCamera.getPerspectiveMatrix();
	if (allGlobals.myCrocodileShader.perspectiveUniform != -1)
	{
		glUniformMatrix4fv(allGlobals.myCrocodileShader.perspectiveUniform, 1, GL_FALSE, (GLfloat*)cameraPerspective.m);
	}

	// Camera view
	cameraView = allGlobals.myCamera.getViewMatrix();
	if (allGlobals.myCrocodileShader.viewUniform != -1)
	{
		glUniformMatrix4fv(allGlobals.myCrocodileShader.viewUniform, 1, GL_FALSE, (GLfloat*)cameraView.m);
	}

	if (allGlobals.myCrocodileShader.uvAttribute != -1)
	{
		glEnableVertexAttribArray(allGlobals.myCrocodileShader.uvAttribute);
		glVertexAttribPointer(allGlobals.myCrocodileShader.uvAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*) (5 * sizeof(Vector3)));
	}

	// Scalation matrix
	Matrix scalationMatrix;
	scalationMatrix.SetScale(0.01f);
	if (allGlobals.myCrocodileShader.scalationUniform != -1)
	{
		glUniformMatrix4fv(allGlobals.myCrocodileShader.scalationUniform, 1, GL_FALSE, (GLfloat*) scalationMatrix.m);
	}

	// Rotation of object
	Matrix rotationOfCrocodile;

#if ENFORCE_ROTATION == false
	//rotationOfCrocodile.SetRotationX(allGlobals.rotationAngleSquare -= allGlobals.rotationAngleIncreaseSpeedSquare);
	rotationOfCrocodile.SetRotationZ(-3.15);
#else 
	rotationOfCrocodile.SetRotationY(allGlobals.enforcedRotation);
	rotationOfCrocodile.SetRotationX(-0.5);
#endif

	if (allGlobals.myCrocodileShader.rotationUniform != -1)
	{
		glUniformMatrix4fv(allGlobals.myCrocodileShader.rotationUniform, 1, GL_FALSE, (GLfloat*) rotationOfCrocodile.m);
	}

	// Texture
	if (allGlobals.myCrocodileShader.textureUniform != -1)
	{
		glUniform1i(allGlobals.myCrocodileShader.textureUniform, 0);
	}
	else {
		std::cerr << "Error sending texture!";
	}

	glDrawElements(GL_TRIANGLES, allGlobals.myCrocodile.getNumberOfIndices(), GL_UNSIGNED_SHORT, nullptr);

#endif

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

void Mouse(ESContext* esContext, float mouseX, float mouseY)
{
	if (mouseX <= allGlobals.screen_size.screenWidth / 2) {
		allGlobals.enforcedRotation += allGlobals.enforcedRotationStep;
		// std::cout << "Left" << std::endl;
	}
	else {
		allGlobals.enforcedRotation -= allGlobals.enforcedRotationStep;
		// std::cout << "Right" << std::endl;
	}
}

void CleanUp()
{
#if DRAW_TRIANGLE
	glDeleteBuffers(1, &allGlobals.vboIdTriangle);
#endif

#if DRAW_RECTANGLE3D
	#if VBO == true
		glDeleteBuffers(1, &allGlobals.vboIdRectangle3D);
	#else 
		glDeleteBuffers(1, &allGlobals.iboIdRectangle3D);
	#endif
#endif

#if DRAW_SQUARE
	glDeleteBuffers(1, &allGlobals.vboIdSquare);
#endif

#if DRAW_MIDDLE_LINE
	glDeleteBuffers(1, &allGlobals.vboIdMiddleLine);
#endif

#if DRAW_CROCODILE
	delete allGlobals.TGA_ANSWER;
#endif

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
	esRegisterMouseFunc(&esContext, Mouse);

	esMainLoop ( &esContext );

	//releasing OpenGL resources
	CleanUp();

	printf("Press any key...\n");
	_getch();

	return 0;
}

