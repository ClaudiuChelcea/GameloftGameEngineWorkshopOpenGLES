#pragma once

#include "XMLparser.hpp"
#include "Structs.h"
#include "Model.h"
#include "Texture.h"
#include "Shader.h"
#include "ImportedObject.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "ObjectComplete.h"
#include <vector>
#include <unordered_map>

using namespace std;
using namespace rapidxml;
struct ModelStruct;
struct ShaderStruct;
struct TextureStruct;
struct ResourceObject;

// Administreaza resursele ce pot fi folosite in cadrul scenei:
// modele, texturi, shadere, fisiere de sunet etc...

class ResourceManager : public XMLreader, public ImportedObject
{
private:
	ResourceManager()
	{
		// PRIVATE CONSTRUCTOR FOR SINGLETON
		setFileName("../../Resources/Test/resourceManager.xml");
		readMe();
		readData();
		// printData();
	}
	static ResourceManager* Instance;

	/* Just for reading */
	// Models
	std::unordered_map<int, ModelStruct*> modelsVector;

	// Shaders
	std::unordered_map<int, ShaderStruct*> shadersVector;
	
	// Textures
	std::unordered_map<int, TextureStruct*> texturesVector;
	
	/* For usage */
	// Models
	std::unordered_map<int, Model*> loadedModelsVector;

	// Shaders
	std::unordered_map<int, Shader*> loadedShadersVector;

	// Textures
	std::unordered_map<int, Texture*> loadedTexturesVector;

	// Array of existing objects
	std::unordered_map<int, ObjectComplete*> existingObjects;
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
	// Read the data into vectors
	void readData();

	// Do nothing - for initialisation
	void doNothing() {};

	// Print the whole data from the XML file
	void printData();

	// Load model
	Model* loadModel(int model_id);

	// Load texture
	Texture* loadTexture(int texture_id);

	// Load shader
	Shader* loadShader(int shader_id);
	
	// Fully create an object by it's model it
	void initExistingObjectByModelId(int model_id, int texture_id, int shader_id);

	/* Getters */
	std::unordered_map<int, ObjectComplete*>& getExistingObjects();
};



