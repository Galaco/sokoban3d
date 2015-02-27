#version 430

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec2 VertexUV;
layout (location = 2) in vec3 VertexNormal;
layout (location = 3) in vec4 VertexTangent;

out vec3 Position;
out vec3 Normal;
out vec2 TexCoord;
out vec3 Tangent;

out mat3 TBN;


out vec3 vertPosEye; //Vertex position in eye coords
out vec3 lightPosEye; //Light position in eye coords
out vec3 targetPosEye; //Light position in eye coords
out vec3 WorldPos0;


uniform vec3 LightPosition; // Light position 
uniform mat3 NormalMatrix;
uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

void calculateTBN()
{
    vec3 Tangent0 = normalize(VertexTangent.xyz * NormalMatrix);
	vec3 norm0=normalize( NormalMatrix * VertexNormal);
    vec3 Bitangent = normalize(NormalMatrix * vec4( cross( VertexTangent.xyz, VertexNormal ) * VertexTangent.w, 0.0 ).xyz );
    TBN = mat3(Tangent0, Bitangent, norm0);
}

void main()
{
	calculateTBN();
	Normal = normalize( NormalMatrix * VertexNormal);
    Position = vec3( M * vec4(VertexPosition,1.0) );
    TexCoord = VertexUV;


   vertPosEye = vec3(V * M * vec4(VertexPosition,1.0)); 
     
   lightPosEye = LightPosition;
   targetPosEye = vec3(V  * vec4(0,0,0,1.0));

   
   WorldPos0 = (M * vec4(VertexPosition, 1.0)).xyz;

   gl_Position = P * V * M * vec4(VertexPosition,1.0);
}
