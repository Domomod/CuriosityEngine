#ifndef TERRAINSHADER_H
#define TERRAINSHADER_H

#include <string>
#include <vector>
#include <Gl/glew.h>

#include "Shader.h"
#include "transform.h"
#include "camera.h"
#include "mesh.h"
#include "light.h"

class TerrainShader :
	public Shader
{
public:
    TerrainShader() {}
    TerrainShader(const std::string& fileName);

    virtual void Bind();
	virtual void UpdateMaterial(Material* material) {};
	virtual void LoadLight(Light light) {};

    TerrainShader(const TerrainShader& other);

    virtual ~TerrainShader();
protected:

private:
};

#endif // TERRAINSHADER_H
