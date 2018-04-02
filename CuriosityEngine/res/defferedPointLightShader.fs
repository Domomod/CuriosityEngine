#version 430

struct LightSource
{
/*
This structure handles all types of Light Sources.
Type:[int]0- directional, 1- point light, 2- spot light(not implemented yet)
Position:[vec3] position of light source, only matters in point and spot 
Attenuation:[vec3] [ConstantAttenuation, LinearAttenuation,QuadratiocAttenuation] attenuation descibes the gradual loss of flux in a medium:
					const- 
					linear- 
					quadratis- 
Direction:[vec3] 	for directional light it's the direction of rays of light
					for spot light it's the direction of the cone of light
Color:[vec3] color of the light in rgb
*/
        vec3 PosDir;
        vec3 Attenuation;
        vec3 Color;
		float AmbientCoefficient;
};
uniform LightSource light;

struct Material
{
/*
This structure descibes currently lit material. 
Emmision:[vec3]	the color of light object is emmiting
Ambient:[vec3] affects the outcome color of ambient lightning
Diffuse:[vec3] affects the outcome color of diffuse lightning
Specular:[vec3] affects the outcome of specular lightning
Shininess;[float] scale 0.0f to 1.0f how bright is the object shining
DispMapScale:[float]
DispMapBias:[float]
*/
	vec3 Specular;
	float Shininess;
};
uniform Material material;

in vec3 position0;

uniform sampler2D gPositionMap;
uniform sampler2D gColorMap;
uniform sampler2D gNormalMap;

uniform mat4 transform;
uniform mat4 model;
uniform vec3 cameraPos;

vec2 CalcTexCoord()
{
   return gl_FragCoord.xy / vec2(800.0f, 600.0f);
}

vec3 ambient(vec3 surfaceColor)
{
	vec3 ambientComponent = light.AmbientCoefficient * light.Color * surfaceColor.rgb ;
	return ambientComponent;
}

vec3 diffuse(vec3 normal, vec3 LightDirection, vec3 surfaceColor)
{
	float diff =  dot(-LightDirection, normal);
	diff = max(0.0f, diff);
	vec3 diffuseComponent = vec3(surfaceColor.rgb * light.Color * diff);
	return diffuseComponent;
}

vec3 specular(vec3 normal, vec3 LightDirection)
{
	vec3 reflectionVector = reflect(LightDirection, normal);
	vec3 surfaceToCamera = normalize(cameraPos - position0);
	float cosAngle = max(0.0, dot(surfaceToCamera, reflectionVector));
	cosAngle = max(0.0f, cosAngle);
	vec3 specularComponent = material.Specular *
							pow(max(dot(reflectionVector,surfaceToCamera),0.0f),0.3f*material.Shininess);
	return specularComponent;
}

vec3 ApplyLight(vec3 WorldPos, vec3 SurfaceColor, vec3 Normal)
/*
Handles all calculations nedded to lit the object by any type of Light.
*/
{
	vec3 dir = WorldPos - light.PosDir;
	float dist = length(dir);
	dir = normalize(dir);
	float attenuation = min((1 / ( light.Attenuation[0] 
								+ (dist * light.Attenuation[1]) 
								+ (dist * dist * light.Attenuation[2]))), 1.0f);
								
	vec3 Color = vec3(0.0f, 0.0f, 0.0f);
	Color += ambient(SurfaceColor) * attenuation;
	Color += diffuse(Normal, dir, SurfaceColor)*attenuation;
	Color += specular(Normal, dir) * attenuation;
	//Color *= attenuation;
	Color = clamp(Color, 0.0f, 1.0f);
	return Color;
}

void main()
{
	vec2 TexCoord = CalcTexCoord();
   	vec3 WorldPos = texture(gPositionMap, TexCoord).xyz;
   	vec3 SurfaceColor = texture(gColorMap, TexCoord).xyz;
   	vec3 Normal = texture(gNormalMap, TexCoord).xyz;
   	Normal = normalize(Normal);

	vec3 Color = ApplyLight(WorldPos, SurfaceColor, Normal);
	
	gl_FragColor = vec4(Color, 1.0f);
}