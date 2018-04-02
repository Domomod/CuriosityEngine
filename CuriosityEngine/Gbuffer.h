#ifndef GBUFFER_H
#define GBUFFER_H

#include <Gl/glew.h>

enum GBUFFER_TEXTURE_TYPE
{
	GBUFFER_TEXTURE_TYPE_POSITION,
	GBUFFER_TEXTURE_TYPE_DIFFUSE,
	GBUFFER_TEXTURE_TYPE_NORMAL,
	GBUFFER_TEXTURE_TYPE_TEXCOORD,
	GBUFFER_NUM_TEXTURES
};

class Gbuffer
{
public:
	Gbuffer();

	~Gbuffer();

	bool Init(unsigned int WindowWidth, unsigned int WindowHeight);

	void StartFrame();
	void BindForGeomPass();
	void BindForStencilPass();
	void BindForLightPass();
	void BindForFinalPass();

	//only for debbuging render
	void BindForWriting();
	void BindForReading();

	void SetReadBuffer(GBUFFER_TEXTURE_TYPE TextureType);

private:

	GLuint m_fbo; //FrameBufferObject
	GLuint m_textures[GBUFFER_NUM_TEXTURES];
	GLuint m_depthTexture;
	GLuint m_finalTexture;
};

#endif //GBUFFER