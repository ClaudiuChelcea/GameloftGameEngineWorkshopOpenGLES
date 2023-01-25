#pragma once

#include "ImportedObject.h"
#include "Structs.h"

class Model : public ImportedObject
{
private:
	ModelStruct* mr;
	int wiredboId; // (id-ul bufferului care contine indicii pentru afisarea wired)
	int nrIndiciWired;
public:
	// Constructor
	Model(ModelStruct* mr);
	Model() = default;

	// Destructor
	~Model();

	/* Methods */

	/* Getters */
	std::string getModelPath();
	GLuint getId();

	/* Setters */
	void Model::setWiredId(int _wiredId);
	void Model::setNrIndexesWired(int _nrindexeswired);
};

