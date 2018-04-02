#include "Shader.h"

void Shader::Construct(const std::string& fileName1, const std::string& fileName2)
{
	LoadShadersCode(fileName1, fileName2);
	LoadAttributes();
	LinkProgram();
	LoadUniforms();
	LoadLightUniforms();
	LoadMaterialUniforms();
}


void Shader::LoadShadersCode(const std::string& fileName1,const std::string& fileName2)
{
	m_program = glCreateProgram();
	m_shaders[0] = CreateShader(LoadShader(fileName1 + ".vs"), GL_VERTEX_SHADER);
	m_shaders[1] = CreateShader(LoadShader(fileName2 + ".fs"), GL_FRAGMENT_SHADER);


	for (unsigned int i = 0; i < NUM_SHADERS; i++)
		glAttachShader(m_program, m_shaders[i]);
}


void Shader::LoadAttributes()
{
	glBindAttribLocation(m_program, 0, "position");
	glBindAttribLocation(m_program, 1, "texCoord");
	glBindAttribLocation(m_program, 2, "normal");
	glBindAttribLocation(m_program, 3, "tangent");
}


void Shader::LinkProgram()
{
	glLinkProgram(m_program);
	CheckShaderError(m_program, GL_LINK_STATUS, true, "Error: Program linking failed: ");

	glValidateProgram(m_program);
	CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Error: Program in invalid: ");
}


void Shader::LoadUniforms()
{
	m_uniforms[TRANSFORM_U] = glGetUniformLocation(m_program, "transform");
	m_uniforms[MODEL_U] = glGetUniformLocation(m_program, "model");
	m_uniforms[CAMERA_POS_U] = glGetUniformLocation(m_program, "cameraPos");
	m_uniforms[VIEW_MATRIX_U] = glGetUniformLocation(m_program, "viewMatrix");
}


void Shader::LoadLightUniforms()
{
	m_LightSourceUniforms[POS_DIR_U] = glGetUniformLocation(m_program, "light.PosDir");
	m_LightSourceUniforms[ATTENUATION_U] = glGetUniformLocation(m_program, "light.Attenuation");
	m_LightSourceUniforms[COLOR_U] = glGetUniformLocation(m_program, "light.Color");
	m_LightSourceUniforms[AMBIENT_U] = glGetUniformLocation(m_program, "light.AmbientCoefficient");

	m_NumLights = glGetUniformLocation(m_program, "NUM_LIGHTS");
}


void Shader::LoadMaterialUniforms()
{
	m_MaterialUniforms[MAT_EMMISION_U] = glGetUniformLocation(m_program, "material.Emmision");
	m_MaterialUniforms[MAT_AMBIENT_U] = glGetUniformLocation(m_program, "material.Ambient");
	m_MaterialUniforms[MAT_DIFFUSE_U] = glGetUniformLocation(m_program, "material.Diffuse");
	m_MaterialUniforms[MAT_SPECULAR_U] = glGetUniformLocation(m_program, "material.Specular");
	m_MaterialUniforms[MAT_SHININESS_U] = glGetUniformLocation(m_program, "material.Shininess");
	m_MaterialUniforms[MAT_DISP_SCALE_U] = glGetUniformLocation(m_program, "material.DispMapScale");
	m_MaterialUniforms[MAT_DISP_BIAS_U] = glGetUniformLocation(m_program, "material.DispMapBias");
}


GLuint Shader::CreateShader(const std::string& text, GLenum shaderType)
{
	GLuint shader = glCreateShader(shaderType);

	if (shader == 0)
		std::cerr << "Error: Shader creation failed!" << std::endl;

	const GLchar* shaderSourceStrings[1];
	GLint shaderSourceStringLengths[1];

	shaderSourceStrings[0] = text.c_str();
	shaderSourceStringLengths[0] = text.length();

	glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLengths);
	glCompileShader(shader);

	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error: Shader compilation failed: ");

	return shader;
}

std::string Shader::LoadShader(const std::string& fileName)
{
	std::ifstream file;
	file.open((fileName).c_str());

	std::string output;
	std::string line;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		std::cerr << "Unable to load shader: " << fileName << std::endl;
	}

	return output;
}

void Shader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE)
	{
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		std::cerr << errorMessage << ": '" << error << "'" << std::endl;
	}
}


void Shader::Bind()
{
	glUseProgram(m_program);

	GLuint t1Location = glGetUniformLocation(m_program, "diffuse");
	GLuint t2Location = glGetUniformLocation(m_program, "normalMap");
	GLuint t3Location = glGetUniformLocation(m_program, "dispMap");

	glUniform1i(t1Location, 0);
	glUniform1i(t2Location, 1);
	glUniform1i(t3Location, 2);
}


void Shader::Detach()
{
	glUseProgram(0);
}


void Shader::UpdateMaterial(Material* material)
{
	glUniform3fv(m_MaterialUniforms[MAT_SPECULAR_U], 1, (float*)&material->m_specular);
	glUniform1fv(m_MaterialUniforms[MAT_SHININESS_U], 1, (float*)&material->m_shininess);

}

void Shader::LoadLight(Light light)
{
	glUniform3fv(m_LightSourceUniforms[POS_DIR_U], 1, (float*)&light.m_posdir);
	glUniform3fv(m_LightSourceUniforms[ATTENUATION_U], 1, (float*)&light.m_attunation);
	glUniform3fv(m_LightSourceUniforms[COLOR_U], 1, (float*)&light.m_color);
	glUniform1fv(m_LightSourceUniforms[AMBIENT_U], 1, (float*)&light.m_ambientCoefficient);
}

void Shader::Update(const Transform& transform, const Camera& camera)
{
	glm::mat4 model = camera.GetViewProjection() * transform.GetModel();
	glm::mat4 modelMatrix = transform.GetModel();
	glm::mat4 viewprojection = camera.GetViewProjection();

	glm::vec3 positionCamera = camera.getPos();

	glUniformMatrix4fv(m_uniforms[TRANSFORM_U], 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(m_uniforms[MODEL_U], 1, GL_FALSE, &modelMatrix[0][0]);
	glUniform3fv(m_uniforms[CAMERA_POS_U], 1, (float*)&positionCamera);
	glUniformMatrix4fv(m_uniforms[VIEW_MATRIX_U], 1, GL_FALSE, &viewprojection[0][0]);
	//glUniform1fv(m_uniforms[MAT_SHININESS_U], 1, (float*)&glLight[1].quadraticAtt);
}