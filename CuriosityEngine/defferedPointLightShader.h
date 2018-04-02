#pragma once
#include "Shader.h"
class DefferedPointLightShader :
	public Shader
{
public:
	DefferedPointLightShader(const std::string& fileName);

	virtual void Bind();
	virtual void LoadUniforms();
	virtual void LoadAttributes();
	virtual void Update(const Transform & transform, const Camera & camera);

	~DefferedPointLightShader();
};

