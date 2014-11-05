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

typedef std::vector<glm::vec3> PositionBuffer;
typedef std::vector<glm::vec3> NormalBuffer;
typedef std::vector<glm::vec2> Tex2DBuffer;
typedef std::vector<unsigned short> IndexBuffer;

struct Vertex
{
	glm::vec3   m_Pos;
	glm::vec3   m_Normal;
	glm::vec2   m_Tex0;
	int         m_StartWeight;
	int         m_WeightCount;
};
typedef std::vector<Vertex> VertexList;

struct Triangle
{
	int             m_Indices[3];
};
typedef std::vector<Triangle> TriangleList;

struct Weight
{
	int             m_JointID;
	float           m_Bias;
	glm::vec3       m_Pos;
};
typedef std::vector<Weight> WeightList;

struct Joint
{
	std::string     m_Name;
	int             m_ParentID;
	glm::vec3       m_Pos;
	glm::quat       m_Orient;
};
typedef std::vector<Joint> JointList;

struct Mesh
{
	Mesh(): m_TexID(99999){};
	std::string		name;
	std::string     m_Shader;
	// This vertex list stores the vertices in the bind pose.
	VertexList      m_Verts;
	TriangleList    m_Tris;
	WeightList      m_Weights;

	// A texture ID for the material
	GLuint          m_TexID;

	// These buffers are used for rendering the animated mesh
	PositionBuffer  m_PositionBuffer;   // Vertex position stream
	NormalBuffer    m_NormalBuffer;     // Vertex normals stream
	Tex2DBuffer     m_Tex2DBuffer;      // Texture coordinate set
	IndexBuffer     m_IndexBuffer;      // Vertex index buffer
	GLuint				uiVAO, uiBuffer, indexBuffer, uvBuffer, normalBuffer;
	int iSize, iBufferType;
	bool bDataUploaded;
};
typedef std::vector<Mesh> MeshList;

#endif
