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

// Print the whole data from the XML file
// Print the XML
void ResourceManager::printMe()
{
	// Parse the buffer
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
	std::cout << models_folder->first_attribute("path")->value() << "\n";
	for (xml_node<>* model = models_folder->first_node("model"); model; model = model->next_sibling())
	{
		// Show model id
		std::cout << model->first_attribute("id")->value() << "\n";

		// Get file name
		xml_node<>* file = model->first_node("file");
		std::cout << file->value() << "\n\n";
	}

	// Iterate over the models


	// - shaders
	xml_node<>* shaders = root_node->first_node("shaders");
	xml_node<>* shaders_folder = shaders->first_node("folder");
	std::cout << shaders_folder->first_attribute("path")->value() << "\n";
	for (xml_node<>* shader = shaders_folder->first_node("shader"); shader; shader = shader->next_sibling())
	{
		// Show shader id
		std::cout << shader->first_attribute("id")->value() << "\n";

		// Get vs name
		xml_node<>* vs = shader->first_node("vs");
		std::cout << vs->value() << "\n";

		// Get fs name
		xml_node<>* fs = shader->first_node("fs");
		std::cout << fs->value() << "\n\n";
	}

	// - textures
	xml_node<>* textures = root_node->first_node("textures");
	xml_node<>* textures_folder = textures->first_node("folder");
	std::cout << textures_folder->first_attribute("path")->value() << "\n";
	for (xml_node<>* texture = textures_folder->first_node("texture"); texture; texture = texture->next_sibling())
	{
		// Show texture id
		std::cout << texture->first_attribute("id")->value() << "\n";

		// Show texture type
		std::cout << texture->first_attribute("type")->value() << "\n";

		// Get file name
		xml_node<>* file = texture->first_node("file");
		std::cout << file->value() << "\n";

		// Get min_filter name
		xml_node<>* min_filter = texture->first_node("min_filter");
		std::cout << min_filter->value() << "\n";

		// Get mag_filter name
		xml_node<>* mag_filter = texture->first_node("mag_filter");
		std::cout << mag_filter->value() << "\n";

		// Get wrap_s name
		xml_node<>* wrap_s = texture->first_node("wrap_s");
		std::cout << wrap_s->value() << "\n";

		// Get wrap_t name
		xml_node<>* wrap_t = texture->first_node("wrap_t");
		std::cout << wrap_t->value() << "\n\n";
	}
}