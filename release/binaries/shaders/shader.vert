#version 430

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec2 VertexUV;
layout (location = 2) in vec3 VertexNormal;
layout (location = 3) in vec4 VertexTangent;

layout (location = 4) in ivec4 BoneIDs;
layout (location = 5) in vec4 Weights;

out vec3 Position;
out vec3 Normal;
out vec2 TexCoord;
out vec3 Tangent;


const int MAX_BONES = 100;
uniform mat4 gBones[MAX_BONES];

//Shadowmapping
out vec3 LightPos;
out vec4 ShadowCoord;
uniform mat4 ShadowMatrix;
//End

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
	vec3 norm0 = normalize( NormalMatrix * VertexNormal);
    vec3 Bitangent = normalize(NormalMatrix * vec4( cross( VertexTangent.xyz, VertexNormal ) * VertexTangent.w, 0.0 ).xyz );
    TBN = mat3(Tangent0, Bitangent, norm0);
}

void main()
{
	mat4 BoneTransform = gBones[BoneIDs[0]] * Weights[0];
    BoneTransform += gBones[BoneIDs[1]] * Weights[1];
    BoneTransform += gBones[BoneIDs[2]] * Weights[2];
    BoneTransform += gBones[BoneIDs[3]] * Weights[3];


	calculateTBN();
	//Normal = normalize( NormalMatrix * vec3(BoneTransform * vec4(VertexNormal, 1.0)).xyz);
	Normal = normalize( NormalMatrix * VertexNormal);
    Position = vec3( M * vec4(VertexPosition,1.0) );
    TexCoord = VertexUV;


	vertPosEye = vec3(V * M * vec4(VertexPosition,1.0)); 
     
	targetPosEye = vec3(V  * vec4(0,0,0,1.0));
   
	//WorldPos0 = (M * (BoneTransform * vec4(VertexPosition,1.0))).xyz;
	WorldPos0 = (M * vec4(VertexPosition,1.0)).xyz;

    //Shadowmapping
    ShadowCoord = ShadowMatrix * vec4(VertexPosition,1.0);
	LightPos = vec3(V * vec4(LightPosition, 1.0));
	//End

	//gl_Position = P * V * M * (BoneTransform * vec4(VertexPosition,1.0));
	gl_Position = P * V * M * vec4(VertexPosition,1.0);
}