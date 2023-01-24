#pragma once

// Administreaza resursele ce pot fi folosite in cadrul scenei:
// modele, texturi, shadere, fisiere de sunet etc...

class ResourceManager
{
private:
	ResourceManager()
	{
		// PRIVATE CONSTRUCTOR FOR SINGLETON
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
};



