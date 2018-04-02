#ifndef ENTITY_SHADER_H
#define ENTITY_SHADER_H

#include <string>
#include <vector>
#include <Gl/glew.h>

#include "Shader.h"
#include "transform.h"
#include "camera.h"
#include "mesh.h"
#include "light.h"

class EntityShader :
	public Shader
{
public:
	EntityShader(){}
	EntityShader(const std::string& fileName);

	virtual void LoadLightUniforms() {};
	virtual void LoadMaterialUniforms() {};

	virtual void UpdateMaterial(Material* material) {};
	virtual void LoadLight(Light light) {};

	EntityShader(const EntityShader& other);

protected:

private:
    static const unsigned int NUM_SHADERS = 2;
};

#endif // SHADER_H
