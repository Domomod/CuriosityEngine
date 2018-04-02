#include "Gbuffer.h"
#include "stdio.h"

Gbuffer::Gbuffer()
{
	m_fbo = 0;
	m_depthTexture = 0;
	m_finalTexture = 0;
}


Gbuffer::~Gbuffer()
{
	if (m_fbo != 0) {
		glDeleteFramebuffers(1, &m_fbo);
	}

	if (m_textures[0] != 0) {
		glDeleteTextures(sizeof(m_textures)/sizeof(m_textures[0]), m_textures);
	}

	if (m_depthTexture != 0) {
		glDeleteTextures(1, &m_depthTexture);
	}

	if (m_finalTexture != 0) {
		glDeleteTextures(1, &m_finalTexture);
	}
}


bool Gbuffer::Init(unsigned int WindowWidth, unsigned int WindowHeight)
{
	//Create FrameBufferObject
	glGenFramebuffers(1, &m_fbo);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo);

	unsigned int M_TEXTURES_ARRAY_SIZE = sizeof(m_textures) / sizeof(m_textures[0]);
	//Create the gbuffer textures
	glGenTextures(M_TEXTURES_ARRAY_SIZE, m_textures);
	glGenTextures(1, &m_depthTexture);
	glGenTextures(1, &m_finalTexture);

	for (unsigned int i = 0; i < M_TEXTURES_ARRAY_SIZE; i++)
	{
		glBindTexture(GL_TEXTURE_2D, m_textures[i]);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, WindowWidth, WindowHeight,
			0, GL_RGB, GL_FLOAT, NULL);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i,
			GL_TEXTURE_2D, m_textures[i], 0);
	}
	
	// depth
	glBindTexture(GL_TEXTURE_2D, m_depthTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH32F_STENCIL8, WindowWidth,
		WindowHeight, 0, GL_DEPTH_STENCIL, GL_FLOAT_32_UNSIGNED_INT_24_8_REV, NULL);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, 
		GL_TEXTURE_2D, m_depthTexture, 0);

	//final
	glBindTexture(GL_TEXTURE_2D, m_finalTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, WindowWidth, WindowHeight,
		0, GL_RGB, GL_FLOAT, NULL);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT4,
		GL_TEXTURE_2D, m_finalTexture, 0);

	GLenum DrawBuffers[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1,
		GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
	glDrawBuffers(sizeof(DrawBuffers) / sizeof(DrawBuffers[0]), DrawBuffers);

	GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	if (Status != GL_FRAMEBUFFER_COMPLETE) 
	{
		printf("FB error, status: 0x%x\n", Status);
		return false;
	}
	
	//restore default FBO
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

	return true;
}


void Gbuffer::StartFrame()
/*at the start of each frame we need to clear the final
texture which is attached to attachment point number 4.*/
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo);
	glDrawBuffer(GL_COLOR_ATTACHMENT4);
	glClear(GL_COLOR_BUFFER_BIT);
}


void Gbuffer::BindForGeomPass()
/*we keep changing the FBO to we need to config
the draw buffers for the attributes each time.*/
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo);

	GLenum DrawBuffers[] = { GL_COLOR_ATTACHMENT0,
							GL_COLOR_ATTACHMENT1,
							GL_COLOR_ATTACHMENT2 };

	glDrawBuffers(sizeof(DrawBuffers)/sizeof(DrawBuffers[0]), DrawBuffers);
}


void Gbuffer::BindForStencilPass()
/*in that case the default output color from the FS is black.
In order to avoid garbaging the final buffer with a black image
of the bounding sphere we disable the draw buffers here.*/
{
	glDrawBuffer(GL_NONE);
}

void Gbuffer::BindForLightPass()
/*The light pass is straightforward. We set the target to be 
the final buffer and bind the attribute buffers as a source.*/
{
	glDrawBuffer(GL_COLOR_ATTACHMENT4);

	for (unsigned int i = 0; i < sizeof(m_textures)/sizeof(m_textures[0]); i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, m_textures[GBUFFER_TEXTURE_TYPE_POSITION + i]);
	}
}

void Gbuffer::BindForFinalPass()
/*at this point the final buffer is populated with the desired image.
We set things up for glBlitFramebuffer() that will be used in scene
render code. The default FBO will be our target to which we will copy
the image from the G Buffer FBO.
*/
{
	glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo);
	glReadBuffer(GL_COLOR_ATTACHMENT4);
}


void Gbuffer::BindForWriting()
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo);
}


void Gbuffer::BindForReading()
/*experimental prepare for glBlitFramebuffer(), used only for debug
render in which we can see the data buffers*/
{
	glBindFramebuffer(GL_READ_FRAMEBUFFER, m_fbo);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

	for (unsigned int i = 0; i < sizeof(m_textures)/sizeof(m_textures[0]); i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, m_textures[GBUFFER_TEXTURE_TYPE_POSITION + i]);
	}
}


void Gbuffer::SetReadBuffer(GBUFFER_TEXTURE_TYPE TextureType)
{
	glReadBuffer(GL_COLOR_ATTACHMENT0 + TextureType);
}