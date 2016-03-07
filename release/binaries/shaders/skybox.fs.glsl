#version 430

in vec3 TexCoord;
uniform samplerCube cubeMap;

out vec4 FragColour;


void main()
{
	FragColour = texture (cubeMap, TexCoord);
}