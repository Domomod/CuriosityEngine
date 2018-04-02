#version 430

layout (location = 0) in vec3 position;

out vec3 position0;

uniform mat4 model;
uniform vec3 cameraPos;

void main()
{
	position0 = (model * vec4( position, 1.0f)).xyz; //tu jest chyba błąd
	gl_Position = vec4(position,  1.0f);
}