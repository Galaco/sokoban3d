#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;

out vec3 UV;

uniform mat4 VP;

void main()
{
    UV = vertexPosition_modelspace;
	gl_Position = VP * vec4 (vertexPosition_modelspace, 1.0);
}