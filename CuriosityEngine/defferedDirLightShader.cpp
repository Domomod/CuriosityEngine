#include "defferedDirLightShader.h"




DefferedDirLightShader::DefferedDirLightShader(const std::string& fileName)
{
	Construct(fileName, fileName);
}


DefferedDirLightShader::~DefferedDirLightShader()
{
}

void DefferedDirLightShader::LoadAttributes()
{
	glBindAttribLocation(m_program, 0, "position");
}

void DefferedDirLightShader::LoadUniforms()
{
	m_uniforms[MODEL_U] = glGetUniformLocation(m_program, "model");
	m_uniforms[CAMERA_POS_U] = glGetUniformLocation(m_program, "cameraPos");
}


void DefferedDirLightShader::Update(const Transform& transform, const Camera& camera)
{
	glm::mat4 model = camera.GetViewProjection() * transform.GetModel();
	glm::mat4 modelMatrix = transform.GetModel();
	glm::vec3 positionCamera = camera.getPos();

	glUniformMatrix4fv(m_uniforms[TRANSFORM_U], 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(m_uniforms[MODEL_U], 1, GL_FALSE, &modelMatrix[0][0]);
	glUniform3fv(m_uniforms[CAMERA_POS_U], 1, (float*)&positionCamera);
}

void DefferedDirLightShader::Bind()
{
	glUseProgram(m_program);

	GLuint t1Location = glGetUniformLocation(m_program, "gPositionMap");
	GLuint t2Location = glGetUniformLocation(m_program, "gColorMap");
	GLuint t3Location = glGetUniformLocation(m_program, "gNormalMap");

	glUniform1i(t1Location, 0);
	glUniform1i(t2Location, 1);
	glUniform1i(t3Location, 2);
}