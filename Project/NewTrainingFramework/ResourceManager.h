#pragma once

#include "XMLparser.hpp"

using namespace std;
using namespace rapidxml;

// Administreaza resursele ce pot fi folosite in cadrul scenei:
// modele, texturi, shadere, fisiere de sunet etc...

class ResourceManager : public XMLreader
{
private:
	ResourceManager()
	{
		// PRIVATE CONSTRUCTOR FOR SINGLETON
		setFileName("../../Resources/Test/resourceManager.xml");
		readMe();
		printMe();
	}
	static ResourceManager* Instance;
public:

	// Get instance
	static ResourceManager* getInstance()
	{
		if (!Instance) {
			Instance = new ResourceManager();
		}

		return Instance;
	}

	// Destructor
	~ResourceManager()
	{
		delete Instance;
	}
	
	/* Methods */
	// Print the whole data from the XML file
	void printMe() override;

	// Do nothing - for initialisation
	void doNothing() {};
};



