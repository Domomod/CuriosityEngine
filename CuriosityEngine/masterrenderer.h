#ifndef MASTERRENDERER_H
#define MASTERRENDERER_H

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#include <vector>

#include "light.h"
#include "entity.h"
#include "texturepack.h"
#include "defines/texturedmodels.h"
#include "mesh.h"

#include "entityShader.h"
#include "TerrainShader.h"
#include "stencilShader.h"
#include "defferedPointLightShader.h"
#include "defferedDirLightShader.h"

#include "transform.h"
#include "terrain.h"
#include "Gbuffer.h"


class MasterRenderer
{
public:
//    private static final float FOV = 70;
//    private static final float NEAR_PLANE = 0.1f;
//    private static final float FAR_PLANE = 1000;
//    private Matrix4f projectionMatrix;
	MasterRenderer(Entity *rectanglePointer,  Entity *spherePointer);

	void PrepareAndRender(Mesh *mesh, Texture *texture, Material *material, glm::vec3 pos, glm::vec3 rot, float scale, Camera camera);
	void PrepareAndRender(Mesh *mesh, TexturePack *texture, Material *material, glm::vec3 pos, glm::vec3 rot, float scale, Camera camera);
	void PrepareAndRender(Mesh *mesh, Material *material, glm::vec3 pos, glm::vec3 rot, float scale, Camera camera);
	void Transformation(glm::vec3 pos, glm::vec3 rot, float scale, Camera camera);
	void Prepare(Mesh *model, Camera camera);
	void Render(TexturedModel model);
	void UseTexture(Texture *texture);
	void UseTexture(TexturePack *texture);
	void UnbindTexturedModel();

	void DSgeometryPass(std::vector<Entity> entities, std::vector<Terrain> terrains, std::vector<Light> lights, Camera camera);
	void DSStencilPass(Light light, Camera camera);
	void DSdebugLightningPass();
	void PrepareLightPass();
	void DSPointLightPass(Light lights, Camera camera);
	void DSFinalPass();
	void DSDirectionalLightPass(Light lights, Camera camera);
    void Render(std::vector<Entity> entities, std::vector<Terrain> terrains, std::vector<Light> lights, Camera camera);
    void Prepare();

	void UseShader(Shader* shader) { currentShader = shader; }
	//Shader *dirLightShader;

	Gbuffer m_gbuffer;

	Entity *m_sphere;
	Entity *m_rectangle;

	EntityShader  entityShader;
	TerrainShader terrainShader;
	StencilShader stencilShader;
	DefferedPointLightShader pointShader;
	DefferedDirLightShader dirShader;

	Shader *currentShader;
//
//    std::vector<Entity> *entities;
//    std::vector<Terrain> *terrains;
};

#endif // MASTERRENDERER_H