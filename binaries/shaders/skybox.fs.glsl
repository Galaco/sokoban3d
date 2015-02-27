#version 430

in vec3 TexCoord;
uniform samplerCube cubeMap;

layout( location = 0 ) out vec4 FragColour;


void main()
{
	FragColour = texture (cubeMap, TexCoord);
}