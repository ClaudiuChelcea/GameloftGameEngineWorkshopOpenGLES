#pragma once

#include "XMLparser.hpp"
#include "CameraObject.h"
#include "SceneObject.h"

using namespace std;
using namespace rapidxml;

// Administreaza obiectele din cadrul scenei, luminile, camerele
// (eye) disponibile si setarile lor etc...

class SceneManager : public XMLreader
{
private:
	SceneManager()
	{
		// PRIVATE CONSTRUCTOR FOR SINGLETON
		setFileName("../../Resources/Test/sceneManager.xml");
		readMe();
		readData();
		// printMe();
	}

	static SceneManager* Instance;

	// Cameras
	std::vector<CameraObject*> cameras;

	// Objects
	std::vector<SceneObject*> objects;
public:
	
	// Get instance
	static SceneManager* getInstance()
	{
		if (!Instance) {
			Instance = new SceneManager();
		}

		return Instance;
	}

	// Destructor
	~SceneManager()
	{
		delete Instance;
	}

	/* Methods */
	// Read the data into vectors
	void readData();
	
	// Print the whole data from the XML file
	void printMe() override;

	// Do nothing - for initialisation
	void doNothing() {};
	
	/* Getters */
	std::vector<SceneObject*> getObjects();
};

