#include "stencilShader.h"



StencilShader::StencilShader(const std::string& fileName)
{
	Construct(fileName, fileName);
}


StencilShader::~StencilShader()
{
}

void StencilShader::LoadAttributes()
{
	glBindAttribLocation(m_program, 0, "position");
}

void StencilShader::LoadUniforms()
{
	m_uniforms[MODEL_U] = glGetUniformLocation(m_program, "model");
}


void StencilShader::Update(const Transform& transform, const Camera& camera)
{
	glm::mat4 modelMatrix = transform.GetModel();

	glUniformMatrix4fv(m_uniforms[MODEL_U], 1, GL_FALSE, &modelMatrix[0][0]);
}

void StencilShader::Bind()
{
}