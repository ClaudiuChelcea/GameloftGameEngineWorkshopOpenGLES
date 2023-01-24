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
	return;
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
}