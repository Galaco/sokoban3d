#version 430

struct LightInfo {
  vec4 Position;
  vec3 AmbientColor; 
  vec3 DiffuseIntensity;
  float AmbientIntensity;
  vec3 SpecularColor;
  vec3 Ls;
};
uniform LightInfo Light;

struct MaterialInfo {
  vec3 Kd;
};
uniform MaterialInfo Material;

//SHADOW MAPPING
in vec4 ShadowCoord;   
in vec3 LightPos;
layout(binding=0) uniform sampler2DShadow ShadowMap;
//END

layout(binding=1) uniform sampler2D textureDiffuse;
layout(binding=2) uniform sampler2D textureNormal;
layout(binding=3) uniform sampler2D textureSpecular; 
uniform float SpecularExponent;


in vec3 Position;
in vec3 Normal;
in vec2 TexCoord;
in vec3 Tangent;



in mat3 TBN;    //TBN Matrix for Normal Calculation
in vec2 parallaxScaleBias;

in vec3 vertPosEye;
in vec3 WorldPos0;

uniform int FullBright;
uniform int Translucent;

uniform float AmbientLight;
uniform vec3 DiffuseColor;
uniform vec3 SpecularColor;

uniform vec3 EyePosition;

layout( location = 0 ) out vec4 FragColour;

// Calculate the shadow effect at a given point
float calculateShadow()
{
    //Calculate Shadow
    float visibility = 0.0;
	float bias = 0.008; //bias helps eliminate acne
    
    vec4 tmp_shadow_coords = ShadowCoord;
    tmp_shadow_coords.z -= bias; //DEPTH OFFSET DISABLE HERE 
    
    //Basic shadow calculation

    //Percentage Closer Filtering (PCF)
    visibility += textureProjOffset(ShadowMap, tmp_shadow_coords, ivec2(-1, -1));
    visibility += textureProjOffset(ShadowMap, tmp_shadow_coords, ivec2(1, -1));
    visibility += textureProjOffset(ShadowMap, tmp_shadow_coords, ivec2(-1, 1));
    visibility += textureProjOffset(ShadowMap, tmp_shadow_coords, ivec2(1, 1));

    //comment below here for only minor PCF
    visibility += textureProjOffset(ShadowMap, tmp_shadow_coords, ivec2(-2, -2));
    visibility += textureProjOffset(ShadowMap, tmp_shadow_coords, ivec2(-1, -2));
    visibility += textureProjOffset(ShadowMap, tmp_shadow_coords, ivec2(1, -2));
    visibility += textureProjOffset(ShadowMap, tmp_shadow_coords, ivec2(2, -2));
    visibility += textureProjOffset(ShadowMap, tmp_shadow_coords, ivec2(-2, 2));
    visibility += textureProjOffset(ShadowMap, tmp_shadow_coords, ivec2(-1, 2));
    visibility += textureProjOffset(ShadowMap, tmp_shadow_coords, ivec2(1, 2));
    visibility += textureProjOffset(ShadowMap, tmp_shadow_coords, ivec2(2, 2));
    visibility += textureProjOffset(ShadowMap, tmp_shadow_coords, ivec2(-2, -1));
    visibility += textureProjOffset(ShadowMap, tmp_shadow_coords, ivec2(-2, 1));
    visibility += textureProjOffset(ShadowMap, tmp_shadow_coords, ivec2(2, -1));
    visibility += textureProjOffset(ShadowMap, tmp_shadow_coords, ivec2(2, 1));
	//end comment block

    visibility *= 0.25;
	visibility = 1;
    return visibility;
}

vec3 calculateBump()    //Calculate new normal based off Normal Texture and TBN matrix
{
	if( textureSize( textureNormal, 0).x > 0)
	{
		return Normal;
	}
    vec3 BumpMapNormal = texture(textureNormal, TexCoord).xyz;
    BumpMapNormal =  normalize(BumpMapNormal * 2.0 - 1.0);
    vec3 NewNormal;
    NewNormal = normalize(TBN * BumpMapNormal);
    return NewNormal;
}

vec2 calculateParallax()
{
    return TexCoord;
}


subroutine void RenderPassType();
subroutine uniform RenderPassType RenderPass;

subroutine (RenderPassType)
void recordDepth()
{
}

subroutine (RenderPassType)
void finalPass() 
{
	vec3 newnormal = calculateBump();
	vec2 newTexCoord = calculateParallax();
    float visibility = calculateShadow();

	if (FullBright == 1)
	{
		FragColour = texture(textureDiffuse, newTexCoord);
	} else {
		//Ambient
		vec4 ambient = vec4(Light.AmbientColor * Light.AmbientIntensity, 1.0) * texture(textureDiffuse, newTexCoord);

		//Diffuse
		vec3 s = normalize(vec3(LightPos) - Position);
		float sDotN = max( dot(s, newnormal), 0.0 );
		vec4 diffuse = vec4(clamp(Light.AmbientColor * vec3(texture(textureDiffuse, newTexCoord) ) + Light.DiffuseIntensity * vec3(texture(textureDiffuse, newTexCoord) ) * sDotN,0,1), 1.0);

		//Specular
		vec4 specular = vec4(0, 0, 0, 0);	
		float shininess = 255.0 - (texture2D(textureSpecular, vec2(newTexCoord.s, newTexCoord.t)).r * 255.0);	// Get specular shininess from specular texture
		vec3 VertexToEye = normalize((EyePosition) - WorldPos0);
		vec3 LightReflect = normalize(reflect(-normalize(vec3(LightPos)) - Position, newnormal));
		float SpecularFactor = max(dot(VertexToEye, LightReflect), 0.0);
		specular = pow(SpecularFactor, shininess) * vec4(Light.SpecularColor, 1.0) * vec4(Light.Ls, 0);
		specular = clamp(specular, 0.0, 1.0);


		//Final output
		FragColour = (ambient + diffuse + specular) * visibility;
	}




	if (Translucent == 1)
	{
		//if (FragColour.rgb == vec3(0.f,0.f,0.f))
		//{	
			FragColour.a = texture(textureDiffuse, newTexCoord).a;
		//}
	}
}

void main()
{
	RenderPass();
}