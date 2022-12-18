#ifndef XMLreader_H
#define XMLreader_H

#include "XMLparser.hpp"
#include <vector>

using namespace std;
using namespace rapidxml;

class XMLreader
{
	private:
		rapidxml::xml_document<> doc;    // character type defaults to char
		rapidxml::xml_node<>* root_node;
		std::vector<char> buffer;
		char* doc_text; // the text extracted from the document
	public:
		// Constructor and destructor
		XMLreader(std::string file_name = ""); // read the XML
		~XMLreader();
		
		// Methods
		void printMe(); // print the XML
		void modifyTree(); // modify the XML document
};

#endif // XMLreader_H