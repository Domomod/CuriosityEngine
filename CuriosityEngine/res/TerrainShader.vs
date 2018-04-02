#version 430

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec3 tangent;

out vec2 texCoord0;
out vec3 normal0;
out vec3 position0;
out mat3 tbnMatrix;

uniform mat4 transform;
uniform mat4 model;
uniform mat4 viewMatrix;

void main()
{
	position0 = (model * vec4( position, 1.0f)).xyz; //tu jest chyba błąd
	gl_Position = transform  * vec4(position,  1.0f);
	texCoord0 = texCoord;
	normal0 = (model * vec4(normal, 0.0f)).xyz;
	
	vec3 n = normalize((model * vec4(normal, 0.0f)).xyz);
	vec3 t = normalize((model * vec4(1.0f, 0.0f, 0.0f ,0.0f)).xyz);
	
	//t = normalize(t - dot(t, n) * n);
	
	vec3 b = cross(t, n);
	
	tbnMatrix = mat3(t, b, n);
}