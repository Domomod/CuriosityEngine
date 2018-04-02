#include "masterrenderer.h"
#include "defines/materials.h"



MasterRenderer::MasterRenderer(Entity *rectanglePointer, Entity *spherePointer) :
	/*here we specify the constructors of our shader objects, then we set 
	the currentShader pointer to avoid using a pointer that is not associated
	with any of member shaders. Then we initiate the m_gbuffer and set the 
	entity pointers.
	*/
	terrainShader("./res/TerrainShader"),
	entityShader("./res/BasicShader"),
	pointShader("./res/defferedPointLightShader"),
	dirShader("./res/defferedDirLightShader"),
	stencilShader("./res/stencilShader")
{
	currentShader = &entityShader;

	m_gbuffer.Init(WINDOW_WIDTH, WINDOW_HEIGHT);

	m_rectangle = rectanglePointer;
	m_sphere = spherePointer;
}

void MasterRenderer::PrepareAndRender(Mesh *mesh, Texture *texture, Material *material, glm::vec3 pos, glm::vec3 rot, float scale, Camera camera)
/*this is the simpliest render methode, it render*/
{
	//if (texture->getTransparency() == true) glDisable(GL_CULL_FACE);
	Transformation(pos, rot, scale, camera);
	Prepare(mesh, camera);
	currentShader->UpdateMaterial(material);
	UseTexture(texture);
	glDrawElements(GL_TRIANGLES, mesh->GetDrawCount(), GL_UNSIGNED_INT, 0);
	UnbindTexturedModel();
}

void MasterRenderer::PrepareAndRender(Mesh *mesh, TexturePack *texture, Material *material, glm::vec3 pos, glm::vec3 rot, float scale, Camera camera)
/*this methode is used for objects with multiple blended textures eg. terrain.*/
{
	Transformation(pos, rot, scale, camera);
	Prepare(mesh, camera);
	currentShader->UpdateMaterial(material);
	UseTexture(texture);
	glDrawElements(GL_TRIANGLES, mesh->GetDrawCount(), GL_UNSIGNED_INT, 0);
	UnbindTexturedModel();
}

void MasterRenderer::PrepareAndRender(Mesh *mesh, Material *material, glm::vec3 pos, glm::vec3 rot, float scale, Camera camera)
/*this methode is used if we are setting our textures in a diffrent methodes and we don't want to create a TexturePack object 
eg. we need to bind diffrent textures for point lights in deffered lightning pass, otherwise we would render just some gray spheres*/
{
	Transformation(pos, rot, scale, camera);
	Prepare(mesh, camera);
	currentShader->UpdateMaterial(material);
	glDrawElements(GL_TRIANGLES, mesh->GetDrawCount(), GL_UNSIGNED_INT, 0);
	UnbindTexturedModel();
}

void MasterRenderer::Transformation(glm::vec3 pos, glm::vec3 rot, float scale, Camera camera)
{
	Transform transform;
	transform.SetPos(pos);
	transform.SetRot(rot);
	transform.SetScale(glm::vec3(scale));
	currentShader->Update(transform, camera);
}


void MasterRenderer::Prepare(Mesh *rawModel, Camera camera)
{
	glBindVertexArray(rawModel->GetVertexArrayObj());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
}


void MasterRenderer::Render(TexturedModel model)
{
	glDrawElements(GL_TRIANGLES, model.GetRawModel()->GetDrawCount(), GL_UNSIGNED_INT, 0);
	UnbindTexturedModel();
}


void MasterRenderer::UseTexture(Texture *texture)
{
	texture->Bind(0);
}

void MasterRenderer::UseTexture(TexturePack *texture)
{
	texture->Bind();
}


void MasterRenderer::UnbindTexturedModel()
{
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
	glBindVertexArray(0);
}


void MasterRenderer::PrepareLightPass()
{
	glEnable(GL_BLEND);
	glBlendEquation(GL_FUNC_ADD);
	glBlendFunc(GL_ONE, GL_ONE);

	m_gbuffer.BindForReading();
	glClear(GL_COLOR_BUFFER_BIT);
}

void MasterRenderer::DSgeometryPass(std::vector<Entity> entities, std::vector<Terrain> terrains, std::vector<Light> lights, Camera camera)
{
	m_gbuffer.BindForGeomPass();

	// Only the geometry pass updates the depth buffer
	glDepthMask(GL_TRUE);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);

	Transform transform;
	UseShader(&entityShader);
	currentShader->Bind();

	for (int i = 0; i < entities.size(); i++)
	{
		PrepareAndRender(
			entities[i].GetModel().GetRawModel(),
			entities[i].GetModel().GetTexture(),
			entities[i].GetModel().GetMaterial(),
			entities[i].GetPos(),
			entities[i].GetRotXYZ(),
			entities[i].GetScale(),
			camera
		);
	}	//renderer.render(entities, shader, camera);

	UseShader(&terrainShader);
	currentShader->Bind();
	for (int i = 0; i < terrains.size(); i++)
	{
		PrepareAndRender(
			terrains[i].GetRawModel(),
			terrains[i].GetTexture(),
			terrains[i].GetMaterial(),
			terrains[i].GetPos(),
			terrains[i].GetRotXYZ(),
			terrains[i].GetScale(),
			camera
		);
	}

	// When we get here the depth buffer is already populated and the stencil pass
	// depends on it, but it does not write to it.
	glDepthMask(GL_FALSE);
}

void MasterRenderer::DSStencilPass(Light light, Camera camera)
{
	m_gbuffer.BindForStencilPass();

	UseShader(&stencilShader);
	currentShader->Bind();

	glEnable(GL_DEPTH_TEST);

	glDisable(GL_CULL_FACE);

	glClear(GL_STENCIL_BUFFER_BIT);

	glStencilFunc(GL_ALWAYS, 0, 0);

	glStencilOpSeparate(GL_BACK, GL_KEEP, GL_INCR_WRAP, GL_KEEP);
	glStencilOpSeparate(GL_FRONT, GL_KEEP, GL_DECR_WRAP, GL_KEEP);

	m_sphere->SetScale(light.CalcPointLightBSphere());
	m_sphere->SetPos(light.m_posdir);
	PrepareAndRender(
		m_sphere->GetModel().GetRawModel(),
		m_sphere->GetModel().GetMaterial(),
		m_sphere->GetPos(),
		m_sphere->GetRotXYZ(),
		m_sphere->GetScale(),
		camera
	);
}

void MasterRenderer::DSPointLightPass(Light light, Camera camera)
{
	assert(light.m_type == POINT_LIGHT);

	m_gbuffer.BindForLightPass();
	UseShader(&pointShader);
	currentShader->Bind();
	currentShader->LoadLight(light);
	
	glStencilFunc(GL_NOTEQUAL, 0, 0xFF);

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendEquation(GL_FUNC_ADD);
	glBlendFunc(GL_ONE, GL_ONE);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);

	m_sphere->SetScale(light.CalcPointLightBSphere());
	m_sphere->SetPos(light.m_posdir);
	PrepareAndRender(
		m_sphere->GetModel().GetRawModel(),
		m_sphere->GetModel().GetMaterial(),
		m_sphere->GetPos(),
		m_sphere->GetRotXYZ(),
		m_sphere->GetScale(),
		camera
	);
	glCullFace(GL_BACK);

	glDisable(GL_BLEND);
}

void MasterRenderer::DSDirectionalLightPass(Light light, Camera camera)
{
	assert( light.m_type == DIRECTIONAL_LIGHT );

	m_gbuffer.BindForLightPass();

	//glDisable(GL_DEPTH_TEST);
	/*glEnable(GL_BLEND);
	glBlendEquation(GL_FUNC_ADD);
	glBlendFunc(GL_ONE, GL_ONE);*/

	UseShader(&dirShader);
	currentShader->Bind();
	currentShader->LoadLight(light);

	PrepareAndRender(
		m_rectangle->GetModel().GetRawModel(),
		m_rectangle->GetModel().GetMaterial(),
		m_rectangle->GetPos(),
		m_rectangle->GetRotXYZ(),
		m_rectangle->GetScale(),
		camera
	);

	//glEnable(GL_BLEND);
}

void MasterRenderer::DSFinalPass()
{
	m_gbuffer.BindForFinalPass();
	glBlitFramebuffer(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT,
		0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, GL_COLOR_BUFFER_BIT, GL_LINEAR);
}

void MasterRenderer::DSdebugLightningPass()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_gbuffer.BindForReading();

	GLsizei HalfWidth = (GLsizei)(WINDOW_WIDTH / 2.0f);
	GLsizei HalfHeight = (GLsizei)(WINDOW_HEIGHT / 2.0f);

	m_gbuffer.SetReadBuffer(GBUFFER_TEXTURE_TYPE_POSITION);
	glBlitFramebuffer(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT,
		0, 0, HalfWidth, HalfHeight, GL_COLOR_BUFFER_BIT, GL_LINEAR);

	m_gbuffer.SetReadBuffer(GBUFFER_TEXTURE_TYPE_DIFFUSE);
	glBlitFramebuffer(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT,
		0, HalfHeight, HalfWidth, WINDOW_HEIGHT, GL_COLOR_BUFFER_BIT, GL_LINEAR);

	m_gbuffer.SetReadBuffer(GBUFFER_TEXTURE_TYPE_NORMAL);
	glBlitFramebuffer(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT,
		HalfWidth, HalfHeight, WINDOW_WIDTH, WINDOW_HEIGHT, GL_COLOR_BUFFER_BIT, GL_LINEAR);

	m_gbuffer.SetReadBuffer(GBUFFER_TEXTURE_TYPE_TEXCOORD);
	glBlitFramebuffer(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT,
		HalfWidth, 0, WINDOW_WIDTH, HalfHeight, GL_COLOR_BUFFER_BIT, GL_LINEAR);
}

void MasterRenderer::Render(std::vector<Entity> entities, std::vector<Terrain> terrains, std::vector<Light> lights, Camera camera)
{
	m_gbuffer.StartFrame();

	DSgeometryPass(entities, terrains, lights, camera);
	
	int which = 2;
	if (which == 1)
	{
		DSdebugLightningPass();
	}
	else if (which == 2)
	{
		PrepareLightPass();

		glDisable(GL_STENCIL_TEST);

		DSDirectionalLightPass(lights[0], camera);

		//glEnable(GL_STENCIL_TEST);

		for (int i = 1; i < lights.size(); i++)
		{
			//DSStencilPass(lights[i], camera);
			DSPointLightPass(lights[i], camera);
		}

		glDisable(GL_STENCIL_TEST);

		DSFinalPass();
	}
}
 

////void cleanUp(){
////    shader.cleanUp();
////    terrainShader.cleanUp();
////}


void MasterRenderer::Prepare()
{
    glDepthMask(GL_TRUE);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f, 0.16f, 0.3f, 1.0f);
}