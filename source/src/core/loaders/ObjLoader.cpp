#include "ObjLoader.h"

ObjLoader::ObjLoader(){

}

ObjLoader::~ObjLoader(){

}

Model* ObjLoader::load(std::string path){
	Model* m = new Model;
	m->setFormat("obj");

	const aiScene* scene = importer.ReadFile(path,
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_GenNormals |
		aiProcess_SortByPType);

	// If the import failed, report it
	if (!scene)
	{
		Logger::log(ERROR_, (std::string("Model: Failed to load Mesh: ") + path).c_str());
		return false;
	}
	// Now we can access the file's contents. 

	Mesh mesh;
	aiMatrix4x4 tempMat = scene->mRootNode->mTransformation.Inverse();
	mesh.m_GlobalInverseTransform =
		glm::mat4(
		tempMat.a1, tempMat.a2, tempMat.a3, tempMat.a4,
		tempMat.b1, tempMat.b2, tempMat.b3, tempMat.b4,
		tempMat.c1, tempMat.c2, tempMat.c3, tempMat.c4,
		tempMat.d1, tempMat.d2, tempMat.d3, tempMat.d4
		);

	// Create the VAO
	glGenVertexArrays(1, &mesh.m_VAO);
	glBindVertexArray(mesh.m_VAO);

	// Create the buffers for the vertices attributes
	glGenBuffers(6, mesh.m_Buffers);

	mesh.m_Entries.resize(scene->mNumMeshes);
	mesh.m_Textures.resize(scene->mNumMaterials);

	std::vector<glm::vec3> Positions;
	std::vector<glm::vec3> Normals;
	std::vector<glm::vec2> TexCoords;
	std::vector<glm::vec4> Tangents;
	std::vector<VertexBoneData> Bones;
	std::vector<GLuint> Indices;

	GLuint NumVertices = 0;
	GLuint NumIndices = 0;

	// Count the number of vertices and indices
	for (GLuint i = 0; i < mesh.m_Entries.size(); i++) {
		mesh.m_Entries[i].MaterialIndex = scene->mMeshes[i]->mMaterialIndex;
		mesh.m_Entries[i].NumIndices = scene->mMeshes[i]->mNumFaces * 3;
		mesh.m_Entries[i].BaseVertex = NumVertices;
		mesh.m_Entries[i].BaseIndex = NumIndices;

		NumVertices += scene->mMeshes[i]->mNumVertices;
		NumIndices += mesh.m_Entries[i].NumIndices;
	}


	// Reserve space in the vectors for the vertex attributes and indices
	Positions.reserve(NumVertices);
	Normals.reserve(NumVertices);
	TexCoords.reserve(NumVertices);
	Tangents.reserve(NumVertices);
	Bones.resize(NumVertices);
	Indices.reserve(NumIndices);

	// Initialize the meshes in the scene one by one
	for (GLuint i = 0; i < mesh.m_Entries.size(); i++) {
		const aiMesh* paiMesh = scene->mMeshes[i];
		InitMesh(i, paiMesh, Positions, Normals, TexCoords, Tangents, Bones, Indices, mesh);
	}

	/*if (!InitMaterials(pScene, Filename)) {
		return false;
		}*/


	// Generate and populate the buffers with vertex attributes and the indices
	glBindBuffer(GL_ARRAY_BUFFER, mesh.m_Buffers[POS_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Positions[0]) * Positions.size(), &Positions[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, mesh.m_Buffers[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(TexCoords[0]) * TexCoords.size(), &TexCoords[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, mesh.m_Buffers[NORMAL_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Normals[0]) * Normals.size(), &Normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);


	if (Tangents.size() > 0)
	{
		glBindBuffer(GL_ARRAY_BUFFER, mesh.m_Buffers[TANGENT_VB]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Tangents[0]) * Tangents.size(), &Tangents[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 0, 0);
	}
	


	glBindBuffer(GL_ARRAY_BUFFER, mesh.m_Buffers[BONE_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Bones[0]) * Bones.size(), &Bones[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(5);
	glVertexAttribIPointer(5, 4, GL_INT, sizeof(VertexBoneData), (const GLvoid*)0);
	glEnableVertexAttribArray(6);
	glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(VertexBoneData), (const GLvoid*)16);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.m_Buffers[INDEX_BUFFER]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices[0]) * Indices.size(), &Indices[0], GL_STATIC_DRAW);


	m->addMesh(mesh);

	Logger::log(SUCCESS, (std::string("Model: Loaded Mesh: ") + path).c_str());
	return m;
}


void ObjLoader::InitMesh(GLuint MeshIndex,
	const aiMesh* paiMesh,
	std::vector<glm::vec3>& Positions,
	std::vector<glm::vec3>& Normals,
	std::vector<glm::vec2>& TexCoords,
	std::vector<glm::vec4>& Tangents,
	std::vector<VertexBoneData>& Bones,
	std::vector<GLuint>& Indices, Mesh& mesh)
{
	const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

	// Populate the vertex attribute vectors
	for (unsigned int i = 0; i < paiMesh->mNumVertices; i++) {
		const aiVector3D* pPos = &(paiMesh->mVertices[i]);
		const aiVector3D* pNormal = &(paiMesh->mNormals[i]);
		const aiVector3D* pTexCoord = paiMesh->HasTextureCoords(0) ? &(paiMesh->mTextureCoords[0][i]) : &Zero3D;
		const aiVector3D* pTangent = paiMesh->HasTangentsAndBitangents() ? &(paiMesh->mTangents[i]) : &Zero3D;

		Positions.push_back(glm::vec3(pPos->x, pPos->y, pPos->z));
		Normals.push_back(glm::vec3(pNormal->x, pNormal->y, pNormal->z));
		TexCoords.push_back(glm::vec2(pTexCoord->x, pTexCoord->y));
		Tangents.push_back(glm::vec4(pTangent->x, pTangent->y, pTangent->z, 1.f));
	}

	LoadBones(MeshIndex, paiMesh, Bones, mesh);

	// Populate the index buffer
	for (unsigned int i = 0; i < paiMesh->mNumFaces; i++) {
		const aiFace& Face = paiMesh->mFaces[i];
		assert(Face.mNumIndices == 3);
		Indices.push_back(Face.mIndices[0]);
		Indices.push_back(Face.mIndices[1]);
		Indices.push_back(Face.mIndices[2]);
	}
}


void ObjLoader::LoadBones(unsigned int MeshIndex, const aiMesh* pMesh, std::vector<VertexBoneData>& Bones, Mesh& mesh)
{
	for (unsigned int i = 0; i < pMesh->mNumBones; i++) {
		unsigned int BoneIndex = 0;
		std::string BoneName(pMesh->mBones[i]->mName.data);

		if (mesh.m_BoneMapping.find(BoneName) == mesh.m_BoneMapping.end()) {
			// Allocate an index for a new bone
			BoneIndex = mesh.m_NumBones;
			mesh.m_NumBones++;
			BoneInfo bi;
			mesh.m_BoneInfo.push_back(bi);
			aiMatrix4x4 temp = pMesh->mBones[i]->mOffsetMatrix;
			mesh.m_BoneInfo[BoneIndex].BoneOffset = glm::mat4(
				temp.a1, temp.a2, temp.a3, temp.a4,
				temp.b1, temp.b2, temp.b3, temp.b4,
				temp.c1, temp.c2, temp.c3, temp.c4,
				temp.d1, temp.d2, temp.d3, temp.d4
				);
			mesh.m_BoneMapping[BoneName] = BoneIndex;
		}
		else {
			BoneIndex = mesh.m_BoneMapping[BoneName];
		}

		for (unsigned int j = 0; j < pMesh->mBones[i]->mNumWeights; j++) {
			unsigned int VertexID = mesh.m_Entries[MeshIndex].BaseVertex + pMesh->mBones[i]->mWeights[j].mVertexId;
			float Weight = pMesh->mBones[i]->mWeights[j].mWeight;
			Bones[VertexID].AddBoneData(BoneIndex, Weight);
		}
	}
}