#pragma once
#include <iostream>
#include <fstream>
#include <string>

#include "camera.h"
#include "light.h"
#include "material.h"
#include "transform.h"

//Factory Method // metoda fabrykuj¹ca
template< class C >
C* factoryNew()
{
	C* pObject = new C();
	pObject->afterConstruction();

	return pObject;
}

class Shader
{
public:
	Shader() {};
	virtual ~Shader() {};

	virtual void Construct(const std::string& fileName1, const std::string& fileName2);
	virtual void LoadShadersCode(const std::string& fileName1, const std::string& fileName2);
	virtual void LoadAttributes();
	virtual void LinkProgram();
	virtual void LoadUniforms();
	virtual void LoadLightUniforms();
	virtual void LoadMaterialUniforms();

	virtual void Bind();
	virtual void Detach();
	virtual void Update(const Transform& transform, const Camera& camera);
	virtual void UpdateMaterial(Material* material);
	virtual void LoadLight(Light light);

	GLuint CreateShader(const std::string& text, GLenum shaderType);
	static std::string LoadShader(const std::string& fileName);
	void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);

	static const unsigned int NUM_SHADERS = 2;

	enum UNI_LIGHT_PARAMS
	{
		POS_DIR_U,
		ATTENUATION_U,
		COLOR_U,
		AMBIENT_U,

		NUM_PARAMS_LIGHT
	};

	enum UNI_MAT_PARAMS
	{
		MAT_EMMISION_U,
		MAT_AMBIENT_U,
		MAT_DIFFUSE_U,
		MAT_SPECULAR_U,
		MAT_SHININESS_U,
		MAT_DISP_SCALE_U,
		MAT_DISP_BIAS_U,

		NUM_PARAMS_MAT
	};

	enum UNIFORMS
	{
		TRANSFORM_U,
		MODEL_U,
		CAMERA_POS_U,
		VIEW_MATRIX_U,

		NUM_UNIFORMS
	};

protected:
	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];
	GLuint m_uniforms[NUM_UNIFORMS];
	GLuint m_NumLights;
	GLuint m_LightSourceUniforms[NUM_PARAMS_LIGHT];
	GLuint m_MaterialUniforms[NUM_PARAMS_MAT];
};

