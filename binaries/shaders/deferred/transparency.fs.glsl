#version 330 core

in vec2 UV;
in vec3 Normal0;

layout (location = 0) out vec4 FragColour;

uniform sampler2D gColorMap;

void main()
{
	FragColour = texture(gColorMap, UV);
}