#pragma once

#include "Model.h"
#include "Texture.h"
#include "Shader.h"

class ObjectComplete
{
private:
	Model* model;
	Texture* texture;
	Shader* shader;

	int model_id;
	int texture_id;
	int shader_id;
public:
	// Constructor
	ObjectComplete(Model* _model, Texture* _texture, Shader* _shader);
	ObjectComplete(int _model_id, int _texture_id, int _shader_id);
	
	/* Getters */
	Model* getModelClass();
	Texture* getTextureClass();
	Shader* getShaderClass();

	/* Setters */
	void setModelClass(Model* _model);
	void setTextureClass(Texture* _texture);
	void setShaderClass(Shader* _shader);
};

