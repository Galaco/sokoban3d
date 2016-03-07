/*********************************************************************
Project: Dissertation
Author: Josh Martin
Name: Deferred Shaders
Description: Deferred shader code. Compiled into the engine
*********************************************************************/
#ifndef DEFERREDSHADERS_H
#define DEFERREDSHADERS_H



namespace spire{
	namespace deferred{
		//Geometry shaders
		int geometryFragLines = 20;
		const char* geometryFrag[] = {
			"#version 330 core",
			"\n",
			"in vec2 UV;\n",
			"in vec3 Normal0;",
			"in vec3 WorldSpacePos0;",
			"",
			"layout(location = 0) out vec3 WorldSpacePosOut;",
			"layout(location = 1) out vec3 DiffuseOut;",
			"layout(location = 2) out vec3 NormalOut;",
			"layout(location = 3) out vec3 TexCoordOut;",
			"",
			"uniform sampler2D gColorMap;",
			"",
			"void main()",
			"{",
			"	WorldSpacePosOut = WorldSpacePos0;",
			"	DiffuseOut = texture(gColorMap, UV).xyz;",
			"	NormalOut = normalize(Normal0);",
			"	TexCoordOut = vec3(UV, 0.0);",
			"}"
		};







	};
};

#endif
