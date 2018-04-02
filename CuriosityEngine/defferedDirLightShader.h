#pragma once
#include "Shader.h"
class DefferedDirLightShader :
	public Shader
{
public:
	DefferedDirLightShader(const std::string& fileName);

	virtual void Bind();
	virtual void LoadUniforms();
	virtual void LoadAttributes();
	virtual void Update(const Transform & transform, const Camera & camera);

	~DefferedDirLightShader();
};

