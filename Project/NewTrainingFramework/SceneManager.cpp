#include "stdafx.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string.h>
#include <stdio.h>
#include "XMLreader.h"
#include "SceneManager.h"

using namespace std;
using namespace rapidxml;

// Administreaza obiectele din cadrul scenei, luminile, camerele
// (eye) disponibile si setarile lor etc...

SceneManager* SceneManager::Instance = NULL;

// Print the whole data from the XML file
// Print the XML
void SceneManager::printMe()
{
	// Parse the buffer
	doc.clear();
	doc.parse<0>(&input[0]);

	std::cout << doc.value() << std::endl;
}

// Read the data into vectors
void SceneManager::readData()
{
	// Parse the input file
	doc.parse<0>(&input[0]);

	// Find our root node
	root_node = doc.first_node("sceneManager");
	if (root_node == NULL) {
		if (doc.value() == NULL) {
			std::cerr << "The doc was faulty!\n";
			return;
		}
		else {
			std::cerr << "Root node is faulty!\n";
			return;
		}
	}

	// scene manager

	// game name
	xml_node<>* game_name = root_node->first_node("gameName");
	//std::cout << game_name->value() << std::endl;

	// screen size
	xml_node<>* screen_size = root_node->first_node("defaultScreenSize");
	//std::cout << screen_size->first_node("width")->value() << std::endl;
	//std::cout << screen_size->first_node("height")->value() << std::endl;

	// bg color
	xml_node<>* screen_color = root_node->first_node("backgroundColor");
	//std::cout << screen_color->first_node("r")->value() << std::endl;
	//std::cout << screen_color->first_node("g")->value() << std::endl;
	//std::cout << screen_color->first_node("b")->value() << std::endl;

	// controls
	xml_node<>* controls = root_node->first_node("controls");
	for (xml_node<>* control = controls->first_node("control"); control; control = control->next_sibling())
	{
		// Create control

		// KEY
		//std::cout << control->first_node("key")->value() << std::endl;

		// ACTION
		//std::cout << control->first_node("action")->value() << std::endl;
	}

	/* Camera */
	xml_node<>* cameras = root_node->first_node("cameras");
	for (xml_node<>* camera = cameras->first_node("camera"); camera; camera = camera->next_sibling())
	{
		// Create camera
		Camera* my_camera = new Camera(
			Vector3(
				atof(camera->first_node("position")->first_node("x")->value()),
				atof(camera->first_node("position")->first_node("y")->value()),
				atof(camera->first_node("position")->first_node("z")->value())),
			Vector3(
				atof(camera->first_node("target")->first_node("x")->value()),
				atof(camera->first_node("target")->first_node("y")->value()),
				atof(camera->first_node("target")->first_node("z")->value())),
			Vector3(
				(GLfloat)atof(camera->first_node("up")->first_node("x")->value()),
				(GLfloat)atof(camera->first_node("up")->first_node("y")->value()),
				(GLfloat)atof(camera->first_node("up")->first_node("z")->value())),
			(GLfloat)atof(camera->first_node("translationSpeed")->value()),
			(GLfloat)atof(camera->first_node("rotationSpeed")->value()),
			(GLfloat)atof(camera->first_node("near")->value()),
			(GLfloat)atof(camera->first_node("far")->value()),
			(GLfloat)atof(camera->first_node("fov")->value())
		);

		CameraObject* my_cameraObject = new CameraObject(
			my_camera,
			atoi(camera->first_attribute("id")->value()),
			camera->first_node("comment")->value(),
			camera->first_node("type")->value());

		this->cameras.push_back(my_cameraObject);
	}

	// Active cameras
	xml_node<>* camerasActive = root_node->first_node("activeCamera");
	std::cout << camerasActive->value() << std::endl;

	/* Objects */
	xml_node<>* objects = root_node->first_node("objects");
	xml_node<>* objects_comment = objects->first_node("comment");
	// std::cout << objects_comment->value() << std::endl;

	for (xml_node<>* object = objects->first_node("object"); object; object = object->next_sibling())
	{
		// Texture
		bool texture = false;
		Vector3 color = { -1, -1, -1 };
		std::vector <int> textures_ids;

		xml_node<>* textures = object->first_node("textures");
		if (textures != nullptr) {
			texture = true;
			for (xml_node<>* texture = textures->first_node("texture"); texture; texture = texture->next_sibling())
			{
				textures_ids.push_back(atoi(texture->first_attribute("id")->value()));
			}
		} else if (object->first_node("color") != nullptr) { // Color
			color.x = atoi(object->first_node("color")->first_node("r")->value());
			color.y = atoi(object->first_node("color")->first_node("g")->value());
			color.z = atoi(object->first_node("color")->first_node("b")->value());
		}

		if (texture == true) {
			// Create object
			SceneObject* myObject = new SceneObject(
				atoi(object->first_attribute("id")->value()),
				atoi(object->first_node("model")->value()),
				atoi(object->first_node("shader")->value()),
				object->first_node("type")->value(),
				object->first_node("name")->value(),
				textures_ids,
				Vector3(
					atof(object->first_node("position")->first_node("x")->value()),
					atof(object->first_node("position")->first_node("y")->value()),
					atof(object->first_node("position")->first_node("z")->value())),
				Vector3(
					atof(object->first_node("rotation")->first_node("x")->value()),
					atof(object->first_node("rotation")->first_node("y")->value()),
					atof(object->first_node("rotation")->first_node("z")->value())),
				Vector3(
					atof(object->first_node("scale")->first_node("x")->value()),
					atof(object->first_node("scale")->first_node("y")->value()),
					atof(object->first_node("scale")->first_node("z")->value())));

			if (textures_ids.size() > 1) {
				std::cerr << "Watch out! Multiple textures not implemented yet!" << std::endl;
			}

			this->objects.push_back(myObject);
		} else {
			// Create object
			SceneObject* myObject = new SceneObject(
				atoi(object->first_attribute("id")->value()),
				atoi(object->first_node("model")->value()),
				atoi(object->first_node("shader")->value()),
				object->first_node("type")->value(),
				object->first_node("name")->value(),
				textures_ids,
				Vector3(
					atof(object->first_node("position")->first_node("x")->value()),
					atof(object->first_node("position")->first_node("y")->value()),
					atof(object->first_node("position")->first_node("z")->value())),
				Vector3(
					atof(object->first_node("rotation")->first_node("x")->value()),
					atof(object->first_node("rotation")->first_node("y")->value()),
					atof(object->first_node("rotation")->first_node("z")->value())),
				Vector3(
					atof(object->first_node("scale")->first_node("x")->value()),
					atof(object->first_node("scale")->first_node("y")->value()),
					atof(object->first_node("scale")->first_node("z")->value())),
				color);

			this->objects.push_back(myObject);
		}
	}

	// Debug settings
	xml_node<>* debugSettings = root_node->first_node("debugSettings");
	xml_node<>* objectAxes = debugSettings->first_node("objectAxes");
	//std::cout << objectAxes->first_node("OXColor")->first_node("r")->value() << std::endl;
	//std::cout << objectAxes->first_node("OXColor")->first_node("g")->value() << std::endl;
	//std::cout << objectAxes->first_node("OXColor")->first_node("b")->value() << std::endl;
	//std::cout << objectAxes->first_node("OYColor")->first_node("r")->value() << std::endl;
	//std::cout << objectAxes->first_node("OYColor")->first_node("g")->value() << std::endl;
	//std::cout << objectAxes->first_node("OYColor")->first_node("b")->value() << std::endl;
	//std::cout << objectAxes->first_node("OZColor")->first_node("r")->value() << std::endl;
	//std::cout << objectAxes->first_node("OZColor")->first_node("g")->value() << std::endl;
	//std::cout << objectAxes->first_node("OZColor")->first_node("b")->value() << std::endl;

	xml_node<>* camAxes = debugSettings->first_node("camAxes");
	//std::cout << camAxes->first_node("OXColor")->first_node("r")->value() << std::endl;
	//std::cout << camAxes->first_node("OXColor")->first_node("g")->value() << std::endl;
	//std::cout << camAxes->first_node("OXColor")->first_node("b")->value() << std::endl;
	//std::cout << camAxes->first_node("OYColor")->first_node("r")->value() << std::endl;
	//std::cout << camAxes->first_node("OYColor")->first_node("g")->value() << std::endl;
	//std::cout << camAxes->first_node("OYColor")->first_node("b")->value() << std::endl;
	//std::cout << camAxes->first_node("OZColor")->first_node("r")->value() << std::endl;
	//std::cout << camAxes->first_node("OZColor")->first_node("g")->value() << std::endl;
	//std::cout << camAxes->first_node("OZColor")->first_node("b")->value() << std::endl;
}

/* Getters */
std::vector<SceneObject*> SceneManager::getObjects()
{
	return this->objects;
}