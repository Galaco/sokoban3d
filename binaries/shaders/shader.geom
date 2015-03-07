#version 430

in vec3 Position_V;
in vec3 Normal_V;
in vec2 TexCoord_V;
in vec3 Tangent_V;
in vec3 LightPos_V;
in vec4 ShadowCoord_V;
in mat3 TBN_V;
in vec3 vertPosEye_V; //Vertex position in eye coords
in vec3 lightPosEye_V; //Light position in eye coords
in vec3 targetPosEye_V; //Light position in eye coords
in vec3 WorldPos0_V;

out vec3 Position;
out vec3 Normal;
out vec2 TexCoord;
out vec3 Tangent;
out vec3 LightPos;
out vec4 ShadowCoord;
out mat3 TBN;
out vec3 vertPosEye; //Vertex position in eye coords
out vec3 lightPosEye; //Light position in eye coords
out vec3 targetPosEye; //Light position in eye coords
out vec3 WorldPos0;

layout (triangles) in;
layout (triangle_strip) out;
layout (max_vertices = 3) out;

void main(void)
{
    for (int i = 0; i < gl_in.length(); i++) 
	{
		/*gl_in[i].gl_Position.x = gl_in[i].gl_Position.x * sqrt(1.0 - (gl_in[i].gl_Position.y*gl_in[i].gl_Position.y/2.0) - (gl_in[i].gl_Position.z*gl_in[i].gl_Position.z/2.0) + (gl_in[i].gl_Position.y*gl_in[i].gl_Position.y*gl_in[i].gl_Position.z*gl_in[i].gl_Position.z/3.0));
		gl_in[i].gl_Position.y = gl_in[i].gl_Position.y * sqrt(1.0 - (gl_in[i].gl_Position.z*gl_in[i].gl_Position.z/2.0) - (gl_in[i].gl_Position.x*gl_in[i].gl_Position.x/2.0) + (gl_in[i].gl_Position.z*gl_in[i].gl_Position.z*gl_in[i].gl_Position.x*gl_in[i].gl_Position.x/3.0));
		gl_in[i].gl_Position.z = gl_in[i].gl_Position.z * sqrt(1.0 - (gl_in[i].gl_Position.x*gl_in[i].gl_Position.x/2.0) - (gl_in[i].gl_Position.y*gl_in[i].gl_Position.y/2.0) + (gl_in[i].gl_Position.x*gl_in[i].gl_Position.x*gl_in[i].gl_Position.y*gl_in[i].gl_Position.y/3.0));

		float dx = gl_in[i].gl_Position.x * sqrt(1.0 - (gl_in[i].gl_Position.y*gl_in[i].gl_Position.y/2.0) - (gl_in[i].gl_Position.z*gl_in[i].gl_Position.z/2.0) + (gl_in[i].gl_Position.y*gl_in[i].gl_Position.y*gl_in[i].gl_Position.z*gl_in[i].gl_Position.z/3.0));
		float dy = gl_in[i].gl_Position.y * sqrt(1.0 - (gl_in[i].gl_Position.z*gl_in[i].gl_Position.z/2.0) - (gl_in[i].gl_Position.x*gl_in[i].gl_Position.x/2.0) + (gl_in[i].gl_Position.z*gl_in[i].gl_Position.z*gl_in[i].gl_Position.x*gl_in[i].gl_Position.x/3.0));
		float dz = gl_in[i].gl_Position.z * sqrt(1.0 - (gl_in[i].gl_Position.x*gl_in[i].gl_Position.x/2.0) - (gl_in[i].gl_Position.y*gl_in[i].gl_Position.y/2.0) + (gl_in[i].gl_Position.x*gl_in[i].gl_Position.x*gl_in[i].gl_Position.y*gl_in[i].gl_Position.y/3.0));
		*/

        gl_Position = gl_in[i].gl_Position;

		Position = Position_V;
		Normal = Normal_V;
		TexCoord = TexCoord_V;
		Tangent = Tangent_V;
		LightPos = LightPos_V;
		ShadowCoord = ShadowCoord_V;
		TBN = TBN_V;
		vertPosEye = vertPosEye_V;
		lightPosEye = lightPosEye_V; 
		targetPosEye = targetPosEye_V;
		WorldPos0 = WorldPos0_V;


        EmitVertex();
    }

    EndPrimitive();
}