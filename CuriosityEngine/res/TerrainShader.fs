#version 430

layout (location = 0) out vec3 WorldPosOut;
layout (location = 1) out vec3 DiffuseOut;
layout (location = 2) out vec3 NormalOut;
layout (location = 3) out vec3 TexCoordOut;

in vec2 texCoord0;
in vec3 normal0;
in vec3 position0;
in mat3 tbnMatrix;

uniform sampler2D backgroundTexture;
uniform sampler2D normalMap;
uniform sampler2D dispMap;

uniform sampler2D rTexture;
uniform sampler2D rNormalMap;
uniform sampler2D rDispMap;

uniform sampler2D gTexture;
uniform sampler2D gNormalMap;
uniform sampler2D gDispMap;

uniform sampler2D bTexture;
uniform sampler2D bNormalMap;
uniform sampler2D bDispMap;

uniform sampler2D blendMap;

uniform mat4 transform;
uniform mat4 model;
uniform vec3 cameraPos;

void main()
{
	vec4 blendMapColour = texture2D(blendMap, texCoord0);

	vec3 normalLightDirection = tbnMatrix * normalize(vec3(-1.0f ,1.0f, -1.0f));
	
	float backgroundTextureAmount = 1- (blendMapColour.r + blendMapColour.g + blendMapColour.b);
	
	vec3 surfaceToCamera = normalize(cameraPos - position0);
	vec2 backTiledCoords = texCoord0 * 80.0f;
	vec2 rTiledCoords = texCoord0 * 80.0f;
	vec2 gTiledCoords = texCoord0 * 80.0f;
	vec2 bTiledCoords = texCoord0 * 80.0f;

	vec4 backgroundTextureColor = texture2D(backgroundTexture, backTiledCoords) * backgroundTextureAmount;
	vec4 rTextureColor = texture2D(rTexture, rTiledCoords) * blendMapColour.r ;
	vec4 gTextureColor = texture2D(gTexture, gTiledCoords) * blendMapColour.g ;
	vec4 bTextureColor = texture2D(bTexture, bTiledCoords) * blendMapColour.b;
	
	vec4 surfaceColor = backgroundTextureColor + rTextureColor + gTextureColor + bTextureColor;
	vec3 normal = tbnMatrix * ((255.0f/128.0f * texture2D(normalMap, backTiledCoords).xyz) - 1.0f);
	
	WorldPosOut = position0;
	DiffuseOut = surfaceColor.xyz;
	NormalOut = normalize(normal0);
	TexCoordOut = vec3(texCoord0 ,0.0);
}