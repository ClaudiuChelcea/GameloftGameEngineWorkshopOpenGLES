#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string.h>
#include <stdio.h>
#include "XMLreader.h"

using namespace std;
using namespace rapidxml;

// Constructor
XMLreader::XMLreader(std::string file_name)
{
	// Open file
	std::ifstream f;
	f.open(file_name, std::ios::in);
	if (f.is_open() == false) {
		std::cerr << "File " << file_name << " is not open!";
		std::abort();
	}

	// Get data from file
	std::vector<char> _buffer((istreambuf_iterator<char>(f)), istreambuf_iterator<char>());
	_buffer.push_back('\0');
	this->buffer = _buffer;
}

// Destructor
XMLreader::~XMLreader()
{
	delete this->doc_text;
}

// Print the XML
void XMLreader::printMe()
{
	// Parse the buffer
	doc.parse<0>(&buffer[0]);

	// Find our root node
	root_node = doc.first_node("obiecte");
	if (root_node == NULL) {
		if (doc.value() == NULL) {
			std::cerr << "The doc was faulty!\n";
			return;
		} else {
			std::cerr << "Root node is faulty!\n";
			return;
		}
	}

	// Iterate over the objects
	for (xml_node<>* object = root_node->first_node("obiect"); object; object = object->next_sibling())
	{
		std::cout << "Id: " << object->first_attribute("id")->value() << " Name: " << object->first_attribute("nume")->value() << std::endl;

		// Interate over the object attributes - models
		// for (xml_node<>* object_attribute = object->first_node("model"); object_attribute; object_attribute = object_attribute->next_sibling())
		// {
		xml_node<>* object_model = object->first_node("model");
		std::cout << "Model info: " << object_model->first_attribute("info")->value() << std::endl;
		// }

		// Interate over the object attributes - textures
		// for (xml_node<>* object_attribute = object->first_node("textura"); object_attribute; object_attribute = object_attribute->next_sibling())
		// {
		xml_node<>* object_texture = object->first_node("textura");
		std::cout << "Textura folder: " << object_texture->first_attribute("folder")->value() << std::endl;
		// }

		cout << endl;
	}
}

// Modify the document
void XMLreader::modifyTree()
{
	/*xml_document<> doc;
	xml_node<>* node = doc.allocate_node(node_element, "a", "Google");
	doc.append_node(node);
	xml_attribute<>* attr = doc.allocate_attribute("href", "google.com");
	node->append_attribute(attr);*/
}