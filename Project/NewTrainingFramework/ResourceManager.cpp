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
#include "ResourceManager.h"

using namespace std;
using namespace rapidxml;

// Administreaza resursele ce pot fi folosite in cadrul scenei:
// modele, texturi, shadere, fisiere de sunet etc...

ResourceManager* ResourceManager::Instance = NULL;

// Read the data into vectors
void ResourceManager::readData()
{
	// Parse the input file
	doc.parse<0>(&input[0]);

	// Find our root node
	root_node = doc.first_node("resourceManager");
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

	// resource manager
	
	// - models
	xml_node<>* models = root_node->first_node("models");
	xml_node<>* models_folder = models->first_node("folder");
	//std::cout << models_folder->first_attribute("path")->value() << "\n";
	for (xml_node<>* model = models_folder->first_node("model"); model; model = model->next_sibling())
	{
		// Create model
		ModelStruct* default_model = new ModelStruct();
		default_model->model_path = models_folder->first_attribute("path")->value();
		
		// Show model id
		// std::cout << model->first_attribute("id")->value() << "\n";
		default_model->model_id = atoi(model->first_attribute("id")->value());

		// Get file name
		xml_node<>* file = model->first_node("file");
		// std::cout << file->value() << "\n\n";
		default_model->model_name = file->value();

		// Add the model in the model vector
		modelsVector[default_model->model_id] = default_model;
	}


	// - shaders
	xml_node<>* shaders = root_node->first_node("shaders");
	xml_node<>* shaders_folder = shaders->first_node("folder");
	// std::cout << shaders_folder->first_attribute("path")->value() << "\n";
	for (xml_node<>* shader = shaders_folder->first_node("shader"); shader; shader = shader->next_sibling())
	{
		// Create shader
		ShaderStruct* default_shader = new ShaderStruct();
		default_shader->shader_path = shaders_folder->first_attribute("path")->value();
		
		// Show shader id
		// std::cout << shader->first_attribute("id")->value() << "\n";
		default_shader->shader_id = atoi(shader->first_attribute("id")->value());

		// Get vs name
		xml_node<>* vs = shader->first_node("vs");
		// std::cout << vs->value() << "\n";
		default_shader->shader_vs = vs->value();

		// Get fs name
		xml_node<>* fs = shader->first_node("fs");
		// std::cout << fs->value() << "\n\n";
		default_shader->shader_fs = fs->value();

		// Add shader to shader vector
		shadersVector[default_shader->shader_id] = default_shader;
	}

	// - textures
	xml_node<>* textures = root_node->first_node("textures");
	xml_node<>* textures_folder = textures->first_node("folder");
	// std::cout << textures_folder->first_attribute("path")->value() << "\n";
	for (xml_node<>* texture = textures_folder->first_node("texture"); texture; texture = texture->next_sibling())
	{
		// Create texture
		TextureStruct* default_texture = new TextureStruct();
		default_texture->texture_path = textures_folder->first_attribute("path")->value();

		// Show texture id
		// std::cout << texture->first_attribute("id")->value() << "\n";
		default_texture->texture_id = new GLuint((unsigned int) atoi(texture->first_attribute("id")->value()));

		// Show texture type
		// std::cout << texture->first_attribute("type")->value() << "\n";
		default_texture->texture_type = texture->first_attribute("type")->value();

		// Get file name
		xml_node<>* file = texture->first_node("file");
		// std::cout << file->value() << "\n";
		default_texture->texture_file = file->value();

		// Get min_filter name
		xml_node<>* min_filter = texture->first_node("min_filter");
		// std::cout << min_filter->value() << "\n";
		default_texture->texture_min_filter = min_filter->value();

		// Get mag_filter name
		xml_node<>* mag_filter = texture->first_node("mag_filter");
		// std::cout << mag_filter->value() << "\n";
		default_texture->texture_mag_filter = mag_filter->value();

		// Get wrap_s name
		xml_node<>* wrap_s = texture->first_node("wrap_s");
		// std::cout << wrap_s->value() << "\n";
		default_texture->texture_wrap_s = wrap_s->value();

		// Get wrap_t name
		xml_node<>* wrap_t = texture->first_node("wrap_t");
		// std::cout << wrap_t->value() << "\n\n";
		default_texture->texture_wrap_t = wrap_t->value();
		
		// Add texture to texture vector
		texturesVector[*(default_texture->texture_id)] = default_texture;
	}
}

// Print the whole data from the XML file
void ResourceManager::printData()
{
	// Models
	std::cout << "Models!\n";
	for (auto model : this->modelsVector)
	{
		std::cout << "Model " <<  model.second->model_id << " within file " << model.second->model_name << " in folder " << model.second->model_path << std::endl;;
	}

	std::cout << "\n\n";

	// Shaders
	std::cout << "Shaders!\n";
	for (auto shader : this->shadersVector)
	{
		std::cout << "Shader " << shader.second->shader_id << " within file " << shader.second->shader_fs << " and " << shader.second->shader_vs << " in folder " << shader.second->shader_path << std::endl;;
	}

	std::cout << "\n\n";

	// Textures
	std::cout << "Textures!\n";
	for (auto texture : this->texturesVector)
	{
		std::cout << "Texture " << *(texture.second->texture_id) << " within file " << texture.second->texture_file << " in folder " << texture.second->texture_path << " of type " << texture.second->texture_type
			<< " with min_filter " << texture.second->texture_min_filter << " and mag_filter " << texture.second->texture_mag_filter << " and wrap_s " << texture.second->texture_wrap_s << " and wrap_t " << texture.second->texture_wrap_t << std::endl;
	}
}

// Load model
Model* ResourceManager::loadModel(int model_id)
{
	// Check if the model exists in the input XML file
	if (this->modelsVector[model_id] == nullptr) {
		// The model id doesn't exist
		std::cerr << "Model id " << model_id << " doesn't exist in the input file!";
		std::abort();
		return NULL;
	}
	
	// Check if the object is already loaded
	if (this->loadedModelsVector[model_id] == nullptr) {
		// Doesn't exist. Create it!
		Model* modelToLoad = new Model(this->modelsVector[model_id]);
		modelToLoad->InitNFG(this->modelsVector[model_id]->model_path + this->modelsVector[model_id]->model_name);
		
		// Values not used yet
		modelToLoad->setNrIndexesWired(-1);
		modelToLoad->setWiredId(-1);

		// Add to model array
		this->loadedModelsVector[model_id] = modelToLoad;
	
		return modelToLoad;
	}
	else {
		// Already exists
		std::cerr << "Model id " << model_id << " already loaded!";
		return this->loadedModelsVector[model_id];
	}
}

// Load texture
Texture* ResourceManager::loadTexture(int texture_id)
{
	// Load texture
	Texture* textureToLoad = new Texture(this->texturesVector[texture_id]);
	glGenTextures(1, textureToLoad->getId());

	// Check if the texture is 2D or 3D
	if (strcmp(textureToLoad->getData()->texture_type.c_str(), "2d") == 0) {
		glBindTexture(GL_TEXTURE_2D, *(textureToLoad->getId()));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		char* TGA_ANSWER = NULL;
		int width = 0;
		int height = 0;
		int bpp = 0;
		std::string texture_file = textureToLoad->getData()->texture_path + textureToLoad->getData()->texture_file;
		TGA_ANSWER = LoadTGA(texture_file.c_str(), &width, &height, &bpp);
		if (TGA_ANSWER == NULL) {
			std::cerr << "Couldn't load Texture tga!\n";
			std::abort();
		}

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (GLint) width, (GLint) height, 0, GL_RGBA,
			GL_UNSIGNED_BYTE, TGA_ANSWER);

		glActiveTexture(GL_TEXTURE0);

		glEnable(GL_DEPTH_TEST);

	} else if (strcmp(textureToLoad->getData()->texture_type.c_str(), "3d") == 0) {
		std::cerr << "Texture type 3D not implemented yet: " << textureToLoad->getData()->texture_type.c_str() << "\n\n";
		std::abort();
	}
	else {
		std::cerr << "Texture type not understood: " << textureToLoad->getData()->texture_type.c_str() << "\n\n";
		std::abort();
	}
	
	// Put texture in texture array
	this->loadedTexturesVector[texture_id] = textureToLoad;
	return textureToLoad;
}

// Load shader
Shader* ResourceManager::loadShader(int shader_id)
{
	// Create shader
	Shader * shaderToLoad = new Shader(this->shadersVector[shader_id]);

	// Init the shader
	char* vs = new char[shaderToLoad->getData()->shader_path.size() + shaderToLoad->getData()->shader_vs.size() + 1];
	std::string vs_s = shaderToLoad->getData()->shader_path + shaderToLoad->getData()->shader_vs;
	strcpy(vs, vs_s.c_str());

	char* fs = new char[shaderToLoad->getData()->shader_path.size() + shaderToLoad->getData()->shader_fs.size() + 1];
	std::string fs_s = shaderToLoad->getData()->shader_path + shaderToLoad->getData()->shader_fs;
	strcpy(fs, fs_s.c_str());

	if (shaderToLoad->Init(vs, fs) != 0) {
		std::cout << vs << "|" << fs << "|\n";
		std::cerr << "Couldn't init shader for shader " << shaderToLoad->getData()->shader_id << std::endl;
		std::abort();
	}
	
	// Add shader to shader array
	this->loadedShadersVector[shader_id] = shaderToLoad;
	return shaderToLoad;
}

// Fully create an object by it's model it
void ResourceManager::initExistingObjectByModelId(int model_id, int texture_id, int shader_id)
{
	// Create the object
    this->existingObjects[model_id]->setModelClass(loadModel(model_id));
    this->existingObjects[model_id]->setTextureClass(loadTexture(texture_id));
    this->existingObjects[model_id]->setShaderClass(loadShader(shader_id));

	// Print the indexes received
  //  std::cout << this->existingObjects[model_id]->getModelClass()->getId() << " " <<
	///	*((int*)this->existingObjects[model_id]->getTextureClass()->getId()) << " " <<
	//	this->existingObjects[model_id]->getShaderClass()->getId() << "\n";
}

/* Getters */
std::unordered_map<int, ObjectComplete*>& ResourceManager::getExistingObjects()
{
	return this->existingObjects;
}