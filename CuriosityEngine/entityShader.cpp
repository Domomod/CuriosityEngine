#include <iostream>
#include <fstream>
#include <string>

#include "entityShader.h"
#include "material.h"

EntityShader::EntityShader(const std::string& fileName)
{
	Shader::Construct(fileName, fileName);
}