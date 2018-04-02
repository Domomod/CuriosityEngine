#version 430

layout (location = 0) out vec3 WorldPosOut;
layout (location = 1) out vec3 DiffuseOut;
layout (location = 2) out vec3 NormalOut;
layout (location = 3) out vec3 TexCoordOut;

in vec2 texCoord0;
in vec3 normal0;
in vec3 position0;
in mat3 tbnMatrix;

uniform sampler2D textureMap;
uniform sampler2D normalMap;
uniform sampler2D dispMap;

uniform mat4 transform;
uniform mat4 model;
uniform vec3 cameraPos;

void main()
{
	vec3 surfaceToCamera = normalize(cameraPos - position0);
	vec2 texCoords = texCoord0;

	vec3 normal = tbnMatrix * ((255.0f/128.0f * texture2D(normalMap, texCoords).xyz) - 1.0f);
	
	vec4 surfaceColor = texture2D(textureMap, texCoords);
	if(surfaceColor.a < 0.25f)
		discard;
	
	WorldPosOut = position0;
	DiffuseOut = surfaceColor.xyz;
	NormalOut = normalize(normal0);
	TexCoordOut = vec3(texCoord0 ,0.0);
}