/*********************************************************************
Project: Dissertation
Author: Josh Martin

Name: Mesh
Description: Storage for raw mesh data. Note the differences between
			 a Model & a Mesh.
*********************************************************************/
#ifndef MESH_H
#define MESH_H

#include <vector>
#include <string>

#include <GL\glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtx/compatibility.hpp>
#include <glm/gtx/matrix_operation.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>


#define INVALID_MATERIAL 0xFFFFFFFF
#define NUM_BONES_PER_VERTEX 4

enum VB_TYPES {
	INDEX_BUFFER,
	POS_VB,
	NORMAL_VB,
	TEXCOORD_VB,
	BONE_VB,
	NUM_VBs
};

struct BoneInfo
{
	glm::mat4 BoneOffset;
	glm::mat4 FinalTransformation;

	BoneInfo()
	{
		//BoneOffset.SetZero();
		//FinalTransformation.SetZero();
	}
};

struct VertexBoneData
{
	GLuint IDs[NUM_BONES_PER_VERTEX];
	float Weights[NUM_BONES_PER_VERTEX];

	VertexBoneData()
	{
		Reset();
	};

	void Reset()
	{
		IDs[0] = 0;
		IDs[1] = 0;
		IDs[2] = 0;
		IDs[3] = 0;
		Weights[0] = 0;
		Weights[1] = 0;
		Weights[2] = 0;
		Weights[3] = 0;
	}

	void AddBoneData(unsigned int BoneID, float Weight)
	{
		for (unsigned int i = 0; i < NUM_BONES_PER_VERTEX; i++) {
			if (Weights[i] == 0.0) {
				IDs[i] = BoneID;
				Weights[i] = Weight;
				return;
			}
		}

		// should never get here - more bones than we have space for
		assert(0);
	}
};

struct MeshEntry {
	MeshEntry()
	{
		NumIndices = 0;
		BaseVertex = 0;
		BaseIndex = 0;
		MaterialIndex = INVALID_MATERIAL;
	}

	unsigned int NumIndices;
	unsigned int BaseVertex;
	unsigned int BaseIndex;
	unsigned int MaterialIndex;
};


class Mesh {
public:
	Mesh()
	{
		numTextures = 0;
		for (unsigned int i = 0; i < 16; ++i)
		{
			m_texID[i] = 99999;
		}
	};


	std::vector<MeshEntry> m_Entries;
	std::vector<Texture*> m_Textures;


	std::map<std::string, GLuint> m_BoneMapping; // maps a bone name to its index
	GLuint m_NumBones;
	std::vector<BoneInfo> m_BoneInfo;
	glm::mat4 m_GlobalInverseTransform;

	GLuint m_texID[16];
	unsigned int numTextures;

	GLuint m_VAO;
	GLuint m_Buffers[NUM_VBs];

	glm::vec2 BBX, BBY, BBZ;
};







#endif
