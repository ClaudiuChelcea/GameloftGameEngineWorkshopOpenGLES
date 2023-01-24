#ifndef XMLreader_H
#define XMLreader_H

#include "XMLparser.hpp"
#include <vector>
#include <sstream>

using namespace std;
using namespace rapidxml;

class XMLreader
{
	protected:
		rapidxml::xml_document<> doc;    // character type defaults to char
		rapidxml::xml_node<>* root_node;
		vector<char> input;
		char* doc_text; // the text extracted from the document
		std::string file_name = "";
	public:
		// Constructor and destructor
		XMLreader(std::string file_name = "NO FILE PATH RECEIVED"); // read the XML
		~XMLreader();
		
		// Methods
		void readMe(); // read the file
		virtual void printMe(); // print the XML
		void modifyTree(); // modify the XML document
		
		// Setters and getters
		// Change the name of the file
		void setFileName(std::string _file_name = "NO NEW FILE PATH RECEIVED");
};

#endif // XMLreader_H