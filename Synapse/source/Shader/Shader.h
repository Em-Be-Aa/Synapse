#pragma once

#include <string>


class Shader
{

public:

	// Constructor, reads and builds shader
	Shader(const char* vertexPath, const char* fragmentPath);

	// Use, Activate the shader
	void use();

	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;

	// The program ID
	unsigned int ID;
};

