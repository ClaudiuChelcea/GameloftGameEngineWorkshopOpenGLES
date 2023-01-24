#pragma once

#include "XMLparser.hpp"

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
		printMe();
	}

	static SceneManager* Instance;
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
	// Print the whole data from the XML file
	void printMe() override;

	// Do nothing - for initialisation
	void doNothing() {};
};

