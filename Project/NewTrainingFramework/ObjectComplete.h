#pragma once

#include "Model.h"
#include "Texture.h"
#include "Shader.h"
#include <vector>

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
	ObjectComplete(int _model_id, std::vector<int> _texture_id, int _shader_id);

	ObjectComplete();
	
	/* Getters */
	Model* getModelClass();
	Texture* getTextureClass();
	Shader* getShaderClass();
	int getModelId();
	int getShaderId();
	int getTextureId();

	/* Setters */
	void setModelClass(Model* _model);
	void setTextureClass(Texture* _texture);
	void setShaderClass(Shader* _shader);
	void setModelId(int _model_id);
	void setShaderId(int _shader_id);
	void setTextureId(int _texture_id);
};

