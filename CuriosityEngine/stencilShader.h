#pragma once
#include "Shader.h"
class StencilShader :
	public Shader
{
public:
	StencilShader(const std::string& fileName);
	~StencilShader();

	virtual void LoadLightUniforms() {};
	virtual void LoadMaterialUniforms() {};

	virtual void UpdateMaterial(Material* material) {};
	virtual void LoadLight(Light light) {};

	virtual void Bind();
	virtual void LoadUniforms();
	virtual void LoadAttributes();
	virtual void Update(const Transform & transform, const Camera & camera);
};

