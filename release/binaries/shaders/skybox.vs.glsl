#version 430

layout(location = 0) in vec3 Position;

uniform mat4 VP;

out vec3 TexCoord;

void main()
{
	gl_Position = (VP * vec4 (Position, 1.0)).xyww;
    TexCoord = Position;
}