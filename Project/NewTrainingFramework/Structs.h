#pragma once

#include <iostream>
#include <string>
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include

using namespace std;

struct ModelStruct
{
	GLuint model_id;
	string model_path;
	string model_name;
};

struct ShaderStruct
{
	GLuint shader_id;
	string shader_path;
	string shader_vs;
	string shader_fs;
};

struct TextureStruct
{
	GLuint* texture_id;
	string texture_path;
	string texture_type;
	string texture_file;
	string texture_min_filter;
	string texture_mag_filter;
	string texture_wrap_s;
	string texture_wrap_t;
};
