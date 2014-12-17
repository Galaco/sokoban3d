#version 330 core

in vec3 UV;
uniform samplerCube cubeMap;

layout( location = 0 ) out vec4 FragColour;

uniform sampler2D gColorMap;

void main()
{
	FragColour = texture (cubeMap, UV);
}