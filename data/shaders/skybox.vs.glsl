#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 Normal;

out vec2 UV;
out vec3 Normal0;
out vec3 WorldSpacePos0;

uniform mat4 MVP;
uniform mat4 VP;

void main()
{
    gl_Position =  MVP * vec4(vertexPosition_modelspace, 1);
    UV = vertexUV;
    Normal0        = (VP * vec4(Normal, 0.0)).xyz;
    WorldSpacePos0 = (VP * vec4(vertexPosition_modelspace, 1)).xyz;
}