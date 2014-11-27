#version 330 core

in vec2 UV;
in vec3 Normal0;
in vec3 WorldSpacePos0;

layout (location = 0) out vec3 WorldSpacePosOut;
layout (location = 1) out vec3 DiffuseOut;
layout (location = 2) out vec3 NormalOut;
layout (location = 3) out vec3 TexCoordOut;

uniform sampler2D gColorMap;

void main()
{
	WorldSpacePosOut = WorldSpacePos0;
	DiffuseOut      = texture(gColorMap, UV).xyz;
	NormalOut       = normalize(Normal0);
	TexCoordOut     = vec3(UV, 0.0);
}