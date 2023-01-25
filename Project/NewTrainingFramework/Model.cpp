#include "stdafx.h"
#include "Model.h"

// Constructor
Model::Model(ModelStruct* mr)
{
	this->mr = mr;
}

// Destructor
Model::~Model()
{
	delete mr;
}

/* Methods */

/* Getters */
std::string Model::getModelPath()
{
	std::string full_path = mr->model_path + mr->model_name;
	return full_path;
}

GLuint Model::getId()
{
	return this->mr->model_id;
}

/* Setters */
void Model::setWiredId(int _wiredId)
{
	this->wiredboId = _wiredId;
}

void Model::setNrIndexesWired(int _nrindexeswired)
{
	this->nrIndiciWired = _nrindexeswired;
}