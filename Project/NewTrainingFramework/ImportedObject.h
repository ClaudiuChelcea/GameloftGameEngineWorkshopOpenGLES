#pragma once

#include <string>

class ImportedObject
{
	private:
		// VBO & IBO
		unsigned int mVBO;
		unsigned int mIBO;
		unsigned int mNumberOfIndices;
	public:
		/* Methods */
		// Open file safely
		FILE* openFile(const char* file_name);

		// Create object from NFG file
		bool InitNFG(FILE* file);

		// Create object from NFG file
		bool InitNFG(std::string file_name);

		/* Getters */
		unsigned int getVBO();
		unsigned int getIBO();
		unsigned int getNumberOfIndices();
};

