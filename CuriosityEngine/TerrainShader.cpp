#include <iostream>
#include <fstream>
#include <string>

#include "TerrainShader.h"
#include "material.h"

TerrainShader::TerrainShader(const std::string& fileName)
{
    m_program = glCreateProgram();
    m_shaders[0] = CreateShader(LoadShader(fileName + ".vs"), GL_VERTEX_SHADER);
    m_shaders[1] = CreateShader(LoadShader(fileName + ".fs"), GL_FRAGMENT_SHADER);

    for(unsigned int i = 0; i < NUM_SHADERS; i++)
        glAttachShader(m_program, m_shaders[i]);

    glBindAttribLocation(m_program, 0, "position");
    glBindAttribLocation(m_program, 1, "texCoord");
    glBindAttribLocation(m_program, 2, "normal");
    glBindAttribLocation(m_program, 3, "tangent");

    glLinkProgram(m_program);
    CheckShaderError(m_program, GL_LINK_STATUS, true, "Error: Program linking failed: ");

    glValidateProgram(m_program);
    CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Error: Program in invalid: ");

    m_uniforms[TRANSFORM_U] = glGetUniformLocation(m_program, "transform");
    m_uniforms[MODEL_U] = glGetUniformLocation(m_program, "model");
    m_uniforms[CAMERA_POS_U] = glGetUniformLocation(m_program, "cameraPos");
    m_uniforms[VIEW_MATRIX_U] = glGetUniformLocation(m_program, "viewMatrix");
}

TerrainShader::~TerrainShader()
{
    for(unsigned int i = 0; i < NUM_SHADERS; i++)
    {
        glDetachShader(m_program, m_shaders[i]);
        glDeleteShader(m_shaders[i]);
    }

    glDeleteProgram(m_program);
}

void TerrainShader::Bind()
{
    glUseProgram(m_program);

    GLuint t1Location = glGetUniformLocation(m_program, "backgroundTexture");
    GLuint t2Location = glGetUniformLocation(m_program, "normalMap");
    GLuint t3Location = glGetUniformLocation(m_program, "dispMap");

    GLuint t4Location = glGetUniformLocation(m_program, "rTexture");
    GLuint t5Location = glGetUniformLocation(m_program, "rNormalMap");
    GLuint t6Location = glGetUniformLocation(m_program, "rDispMap");

    GLuint t7Location = glGetUniformLocation(m_program, "gTexture");
    GLuint t8Location = glGetUniformLocation(m_program, "gNormalMap");
    GLuint t9Location = glGetUniformLocation(m_program, "gDispMap");

    GLuint t10Location = glGetUniformLocation(m_program, "bTexture");
    GLuint t11Location = glGetUniformLocation(m_program, "bNormalMap");
    GLuint t12Location = glGetUniformLocation(m_program, "bDispMap");

    GLuint t13Location = glGetUniformLocation(m_program, "blendMap");

    glUniform1i(t1Location, 0);
    glUniform1i(t2Location, 1);
    glUniform1i(t3Location, 2);
    glUniform1i(t4Location, 3);
    glUniform1i(t5Location, 4);
    glUniform1i(t6Location, 5);
    glUniform1i(t7Location, 6);
    glUniform1i(t8Location, 7);
    glUniform1i(t9Location, 8);
    glUniform1i(t10Location, 9);
    glUniform1i(t11Location, 10);
    glUniform1i(t12Location, 11);
    glUniform1i(t13Location, 12);
}