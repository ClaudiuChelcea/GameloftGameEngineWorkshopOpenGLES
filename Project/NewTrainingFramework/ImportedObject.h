#pragma once

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

		// Getters
		unsigned int getVBO();
		unsigned int getIBO();
		unsigned int getNumberOfIndices();
};

