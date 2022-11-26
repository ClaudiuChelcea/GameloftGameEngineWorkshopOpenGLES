#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Vertex.h"
#include "Shaders.h"
#include "Globals.h"
#include "Camera.h" // Camera class

#include <fstream>
#include <string>
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <vector>

#define DEBUG_BACKGROUND true

// Vertex & shaders
GLuint vboId[4];
Shaders myShaders[4];

// Prevent update from happening too fast
#define LOCK_UPDATE false
GLfloat currentTime = 0;
GLfloat maxTime = 0.05f;

// Camera
Vector3 position = Vector3(0.0f, 0.0f, -5.0f);
Vector3 target = Vector3(0.0f, 0.0f, 1.0f);
Vector3 up = Vector3(0.0f, 1.0f, 0.0f);
GLfloat moveSpeed = { 1.0f };
GLfloat rotateSpeed = 0.5f;
GLfloat nearC = 0.1f;
GLfloat farC = 1000.0f;
GLfloat fov = 5.0f;
Camera camera = Camera(position, target, up, moveSpeed, rotateSpeed, nearC, farC, fov);

// Delta time
float globalDeltaTime;

// Rotate based on click
bool rotateLeft = false;
bool rotateRight = false;
float rotationAngle = 0.0f;

// Model
int numberOfVertices;
int numberOfIndices;

// Read NFG file
bool ReadNFG(FILE* file)
{
	fscanf(file, "NrVertices: %d\n", &numberOfVertices);
	if (numberOfVertices <= 0)
		return false;
	Vertex* vertices = new Vertex[numberOfVertices];
	for (int i = 0; i < numberOfVertices; ++i)
	{
		fscanf(file, "   %*d. pos:[%f, %f, %f]; norm:[%f, %f, %f]; binorm:[%*f, %*f, %*f]; tgt:[%*f, %*f, %*f]; uv:[%f, %f];\n",
			&vertices[i].pos.x, &vertices[i].pos.y, &vertices[i].pos.z,
			&vertices[i].normal.x, &vertices[i].normal.y, &vertices[i].normal.z,
			&vertices[i].uv.x, &vertices[i].uv.y);
	}
	glGenBuffers(1, &vboId[2]);
	glBindBuffer(GL_ARRAY_BUFFER, vboId[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * numberOfVertices, vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	delete vertices;

	fscanf(file, "NrIndices: %d\n", &numberOfIndices);
	if (numberOfIndices <= 0)
	{
		glDeleteBuffers(1, &vboId[2]);
		return 0;
	}

	int* indices = new int[numberOfIndices];
	for (int i = 0; i < numberOfIndices; i += 3)
	{
		fscanf(file, "   %*d.    %d,    %d,    %d\n", &indices[i], &indices[i + 1], &indices[i + 2]);
	}
	glGenBuffers(1, &vboId[3]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboId[3]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * numberOfIndices, indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	delete indices;
}

int Init ( ESContext *esContext )
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	#if DEBUG_BACKGROUND
	glClearColor ( 0.0f, 1.0f, 0.0f, 0.0f );
	#endif

	// Load model
	FILE* file = fopen("../../NewResourcesPacket/Models/Croco.nfg", "r");
	if (file == NULL) {
		printf("Impossible to open the file !\n");
		return false;
	}
	if(ReadNFG(file) == false) {
		printf("Impossible to read the file !\n");
		return false;
	}

	Vertex verticesData[12];

	/* DOWN */
	// Down - position
	verticesData[0].pos.x =  0.0f;  verticesData[0].pos.y =  0.0f;  verticesData[0].pos.z =  0.0f;
	verticesData[1].pos.x = -0.5f;  verticesData[1].pos.y = -0.5f;  verticesData[1].pos.z =  0.0f;
	verticesData[2].pos.x =  0.5f;  verticesData[2].pos.y = -0.5f;  verticesData[2].pos.z =  0.0f;

	// Down - color
	verticesData[0].color.x = 1.0f;  verticesData[0].color.y = 1.0f;  verticesData[0].color.z = 1.0f;
	verticesData[1].color.x = 1.0f;  verticesData[1].color.y = 1.0f;  verticesData[1].color.z = 0.0f;
	verticesData[2].color.x = 0.0f;  verticesData[2].color.y = 1.0f;  verticesData[2].color.z = 0.0f;

	/* UP */
	// Up - position
	verticesData[3].pos.x = 0.0f;  verticesData[3].pos.y = 0.0f;  verticesData[3].pos.z = 0.0f;
	verticesData[4].pos.x = -0.5f;  verticesData[4].pos.y = 0.5f;  verticesData[4].pos.z = 0.0f;
	verticesData[5].pos.x = 0.5f;  verticesData[5].pos.y = 0.5f;  verticesData[5].pos.z = 0.0f;

	// Up - color
	verticesData[3].color.x = 1.0f;  verticesData[3].color.y = 1.0f;  verticesData[3].color.z = 1.0f;
	verticesData[4].color.x = 1.0f;  verticesData[4].color.y = 0.0f;  verticesData[4].color.z = 0.0f;
	verticesData[5].color.x = 0.0f;  verticesData[5].color.y = 0.0f;  verticesData[5].color.z = 1.0f;

	/* LEFT */
	// Left - position
	verticesData[6].pos.x = 0.0f;  verticesData[6].pos.y = 0.0f;  verticesData[6].pos.z = 0.0f;
	verticesData[7].pos.x = 0.5f;  verticesData[7].pos.y = 0.5f;  verticesData[7].pos.z = 0.0f;
	verticesData[8].pos.x = 0.5f;  verticesData[8].pos.y = -0.5f;  verticesData[8].pos.z = 0.0f;

	// Left - color
	verticesData[9].color.x = 1.0f;  verticesData[9].color.y = 1.0f;  verticesData[9].color.z = 1.0f;
	verticesData[10].color.x = 1.0f;  verticesData[10].color.y = 0.0f;  verticesData[10].color.z = 0.0f;
	verticesData[11].color.x = 1.0f;  verticesData[11].color.y = 1.0f;  verticesData[11].color.z = 0.0f;

	/* RIGHT */
	// Right - position
	verticesData[9].pos.x = 0.0f;  verticesData[9].pos.y = 0.0f;  verticesData[9].pos.z = 0.0f;
	verticesData[10].pos.x = -0.5f;  verticesData[10].pos.y = 0.5f;  verticesData[10].pos.z = 0.0f;
	verticesData[11].pos.x = -0.5f;  verticesData[11].pos.y = -0.5f;  verticesData[11].pos.z = 0.0f;

	// Right - color
	verticesData[6].color.x = 1.0f;  verticesData[6].color.y = 1.0f;  verticesData[6].color.z = 1.0f;
	verticesData[7].color.x = 0.0f;  verticesData[7].color.y = 0.0f;  verticesData[7].color.z = 1.0f;
	verticesData[8].color.x = 0.0f;  verticesData[8].color.y = 1.0f;  verticesData[8].color.z = 0.0f;

	// Separating line
	Vertex verticesDataLine[2];

	verticesDataLine[0].pos.x = 0.0f;  verticesDataLine[0].pos.y = -1.0f;  verticesDataLine[0].pos.z = 0.0f;
	verticesDataLine[1].pos.x = 0.0f;  verticesDataLine[1].pos.y = 1.0f;  verticesDataLine[1].pos.z = 0.0f;

	// Buffer object
	glGenBuffers(1, &vboId[0]); // Generate buffer ID 
	glBindBuffer(GL_ARRAY_BUFFER, vboId[0]); // ADD TYPE
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesData), verticesData, GL_STATIC_DRAW); // Allocate size

	glGenBuffers(1, &vboId[1]); // Generate buffer ID 
	glBindBuffer(GL_ARRAY_BUFFER, vboId[1]); // ADD TYPE
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesDataLine), verticesDataLine, GL_STATIC_DRAW); // Allocate size
	glBindBuffer(GL_ARRAY_BUFFER, 0); // Close buffer

	// Shaders
	int status_1 = myShaders[0].Init("../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs");
	int status_2 = myShaders[1].Init("../Resources/Shaders/TriangleShaderVS_whiteLine.vs", "../Resources/Shaders/TriangleShaderFS_whiteLine.fs");
	int status_3 = myShaders[2].Init("../Resources/Shaders/TriangleShaderVS_MODEL.vs", "../Resources/Shaders/TriangleShaderFS_MODEL.fs");
	int status_4 = myShaders[3].Init("../Resources/Shaders/TriangleShaderVS_MODEL.vs", "../Resources/Shaders/TriangleShaderFS_MODEL.fs");
	return status_1 || status_2 || status_3 || status_4;
}

void Draw ( ESContext *esContext )
{
	glClear(GL_COLOR_BUFFER_BIT);

	// --------------------------------- MODEL ---------------------------------------
	glUseProgram(myShaders[2].program);

	glBindBuffer(GL_ARRAY_BUFFER, vboId[2]);

	// Position
	if (myShaders[2].positionAttribute != -1)
	{
		glEnableVertexAttribArray(myShaders[2].positionAttribute);
		glVertexAttribPointer(myShaders[2].positionAttribute, numberOfVertices, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}

	// Color
	if (myShaders[2].colorAttribute != -1)
	{
		glEnableVertexAttribArray(myShaders[2].colorAttribute);
		glVertexAttribPointer(myShaders[2].colorAttribute, numberOfVertices, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(sizeof(Vector3)));
	}

	// Draw the model
	glDrawElements(GL_TRIANGLES, numberOfVertices, GL_UNSIGNED_SHORT, 0);

	glUseProgram(myShaders[2].program);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboId[3]);

	// Position
	if (myShaders[3].positionAttribute != -1)
	{
		glEnableVertexAttribArray(myShaders[3].positionAttribute);
		glVertexAttribPointer(myShaders[3].positionAttribute, numberOfIndices, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}

	// Color
	if (myShaders[3].colorAttribute != -1)
	{
		glEnableVertexAttribArray(myShaders[3].colorAttribute);
		glVertexAttribPointer(myShaders[3].colorAttribute, numberOfIndices, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(sizeof(Vector3)));
	}

	// Draw the model
	glDrawElements(GL_TRIANGLES, numberOfIndices, GL_UNSIGNED_SHORT, 0);
	// --------------------------------- MODEL ---------------------------------------

	// --------------------------------- CUBE ---------------------------------------
	glUseProgram(myShaders[0].program);

	glBindBuffer(GL_ARRAY_BUFFER, vboId[0]);
	
	// Position
	if (myShaders[0].positionAttribute != -1)
	{
		glEnableVertexAttribArray(myShaders[0].positionAttribute);
		glVertexAttribPointer(myShaders[0].positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}
		
	// Color
	if (myShaders[0].colorAttribute != -1)
	{
		glEnableVertexAttribArray(myShaders[0].colorAttribute);
		glVertexAttribPointer(myShaders[0].colorAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(sizeof(Vector3)));
	}

	// Camera view
	Matrix cameraView = camera.getViewMatrix();
	if (myShaders[0].viewUniform != -1)
	{
		glUniformMatrix4fv(myShaders[0].viewUniform, 1, GL_FALSE, (GLfloat*)cameraView.m);
	}

	// Camera perspective
	Matrix cameraPerspective = camera.getPerspectiveMatrix();
	if (myShaders[0].perspectiveUniform != -1)
	{
		glUniformMatrix4fv(myShaders[0].perspectiveUniform, 1, GL_FALSE, (GLfloat*)cameraPerspective.m);
	}

	// Rotate
	Matrix m;
	m.SetRotationZ(rotationAngle);
	if (myShaders[0].matrixUniform != -1)
	{
		glUniformMatrix4fv(myShaders[0].matrixUniform, 1, GL_FALSE, (GLfloat*)m.m);
	}

	// Draw the square
	glDrawArrays(GL_TRIANGLES, 0, 12);
	// --------------------------------- CUBE ---------------------------------------

	// --------------------------------- LINE ---------------------------------------
	// Now add separating line
	glUseProgram(myShaders[1].program);

	glBindBuffer(GL_ARRAY_BUFFER, vboId[1]);

	// Position
	if (myShaders[1].positionAttribute != -1)
	{
		glEnableVertexAttribArray(myShaders[1].positionAttribute);
		glVertexAttribPointer(myShaders[1].positionAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}

	// Color
	if (myShaders[1].colorAttribute != -1)
	{
		glEnableVertexAttribArray(myShaders[1].colorAttribute);
		glVertexAttribPointer(myShaders[1].colorAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(sizeof(Vector3)));
	}

	// Draw the line
	glDrawArrays(GL_LINES, 0, 2);
	// --------------------------------- LINE ---------------------------------------

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	eglSwapBuffers ( esContext->eglDisplay, esContext->eglSurface );
}

void Update(ESContext* esContext, float deltaTime)
{
	// Limit update
	#if LOCK_UPDATE
	currentTime += deltaTime;
	if (currentTime > maxTime) {
		currentTime = 0;
		return;
	}
	#endif

	// Update deltaTime
	globalDeltaTime += deltaTime;
	if (globalDeltaTime > 0.016) { // 60fps
		camera.setDeltaTime(globalDeltaTime);
		globalDeltaTime = 0.0f;
	}
}

void Key ( ESContext *esContext, unsigned char key, bool bIsPressed)
{
	/* Update camera */
	// WASD movement
	if (key == "W"[0] || key == "w"[0]) {
		camera.moveOy(camera.getMoveSpeed());
		camera.updateWorldView();
	}

	if (key == "S"[0] || key == "s"[0]) {
		camera.moveOy(-camera.getMoveSpeed());
		camera.updateWorldView();
	}

	if (key == "A"[0] || key == "a"[0]) {
		camera.moveOx(-camera.getMoveSpeed());
		camera.updateWorldView();
	}

	if (key == "D"[0] || key == "d"[0]) {
		camera.moveOx(camera.getMoveSpeed());
		camera.updateWorldView();
	}
	
	// ZOOM IN AND OUT
	if (key == "Z"[0] || key == "z"[0]) {
		camera.moveOz(camera.getMoveSpeed());
		camera.updateWorldView();
	}

	if (key == "X"[0] || key == "x"[0]) {
		camera.moveOz(-camera.getMoveSpeed());
		camera.updateWorldView();
	}

	// ROTATE CAMERA
	if (key == "F"[0] || key == "f"[0]) {
		camera.rotateOy(camera.getMoveSpeed());
		camera.updateWorldView();
	}

	if (key == "G"[0] || key == "g"[0]) {
		camera.rotateOy(-camera.getMoveSpeed());
		camera.updateWorldView();
	}

	if (key == "H"[0] || key == "h"[0]) {
		camera.rotateOx(camera.getMoveSpeed());
		camera.updateWorldView();
	}

	if (key == "J"[0] || key == "j"[0]) {
		camera.rotateOx(-camera.getMoveSpeed());
		camera.updateWorldView();
	}

	if (key == "K"[0] || key == "k"[0]) {
		camera.rotateOz(camera.getMoveSpeed());
		camera.updateWorldView();
	}

	if (key == "L"[0] || key == "l"[0]) {
		camera.rotateOz(-camera.getMoveSpeed());
		camera.updateWorldView();
	}
}

void Mouse(ESContext* esContext, float mouseX, float mouseY)
{
	if (mouseX <= Globals::screenWidth / 2) {
		// std::cout << "Left\n";
		rotationAngle -= 90;
	}
	else {
		// std::cout << "Right\n";
		rotationAngle += 90;
	}
}

void CleanUp()
{
	glDeleteBuffers(1, &vboId[0]);
	glDeleteBuffers(1, &vboId[1]);
}

int _tmain(int argc, _TCHAR* argv[])
{
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF ); 

	ESContext esContext;

    esInitContext ( &esContext );

	esCreateWindow ( &esContext, "Game Engine", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);

	if ( Init ( &esContext ) != 0 )
		return 0;

	esRegisterDrawFunc ( &esContext, Draw );
	esRegisterUpdateFunc ( &esContext, Update );
	esRegisterKeyFunc ( &esContext, Key);
	esRegisterMouseFunc( &esContext, Mouse);

	esMainLoop ( &esContext );

	CleanUp();

	printf("Press any key...\n");
	_getch();

	
	return 0;
}

