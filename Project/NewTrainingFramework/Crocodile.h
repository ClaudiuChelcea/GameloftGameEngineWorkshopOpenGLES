#pragma once
#include "ImportedObject.h"
#include <string>

class Crocodile : public ImportedObject
{
	private:
		const std::string modelPath = "../../Resources/Models/Croco.nfg";
	public:
		/* Getters */
		std::string getModelPath();
};

