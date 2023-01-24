#pragma once

// Administreaza obiectele din cadrul scenei, luminile, camerele
// (eye) disponibile si setarile lor etc...

class SceneManager
{
private:
	SceneManager()
	{
		// PRIVATE CONSTRUCTOR FOR SINGLETON
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
};

