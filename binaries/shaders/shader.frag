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

uniform sampler2D textureDiffuse, textureNormal, textureSpecular; 
uniform float SpecularExponent;


in vec3 Position;
in vec3 Normal;
in vec2 TexCoord;
in vec3 Tangent;

in mat3 TBN;    //TBN Matrix for Normal Calculation
in vec2 parallaxScaleBias;

in vec3 vertPosEye;
in vec3 lightPosEye;
in vec3 WorldPos0;

uniform int FullBright;
uniform int Translucent;

uniform float AmbientLight;
uniform vec3 DiffuseColor;
uniform vec3 SpecularColor;

uniform vec3 EyePosition;

layout( location = 0 ) out vec4 FragColour;



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

void main() 
{
	vec3 newnormal = calculateBump();
	vec2 newTexCoord = calculateParallax();


	if (FullBright == 1)
	{
		FragColour = texture(textureDiffuse, newTexCoord);
	} else {
		//Ambient
		vec4 ambient = vec4(Light.AmbientColor * Light.AmbientIntensity, 1.0) * texture(textureDiffuse, newTexCoord);

		//Diffuse
		vec3 s = normalize(vec3(Light.Position) - Position);
		float sDotN = max( dot(s, newnormal), 0.0 );
		vec4 diffuse = vec4(clamp(Light.AmbientColor * vec3(texture(textureDiffuse, newTexCoord) ) + Light.DiffuseIntensity * vec3(texture(textureDiffuse, newTexCoord) ) * sDotN,0,1), 1.0);

		//Specular
		vec4 specular = vec4(0, 0, 0, 0);
		vec3 VertexToEye = normalize((EyePosition) - WorldPos0);
		vec3 LightReflect = normalize(reflect(-normalize(vec3(Light.Position)) - Position, newnormal));
		float SpecularFactor = max(dot(VertexToEye, LightReflect), 0.0);
		specular = pow(SpecularFactor, SpecularExponent) * vec4(Light.SpecularColor, 1.0) * vec4(Light.Ls, 0);
		specular = clamp(specular, 0.0, 1.0);


		//Final output
		FragColour = (ambient + diffuse + specular);
	}

	if (Translucent == 1)
	{
		FragColour.a = texture(textureDiffuse, newTexCoord);
	}
}
