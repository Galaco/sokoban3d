#include "DaeLoader.h"

DaeLoader::DaeLoader(){

}

DaeLoader::~DaeLoader(){

}

Model* DaeLoader::load(std::string path){
	Model* m = new Model;
	m->setFormat("dae");

	const aiScene* scene = importer.ReadFile(path,
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType);

	// If the import failed, report it
	if (!scene)
	{
		Logger::log(ERROR_, (std::string("Model: could not load ") + path).c_str());
		return false;
	}
	// Now we can access the file's contents. 
	for (unsigned int i = 0; i < scene->mNumMeshes; ++i)
	{
		Mesh mesh;
		mesh.name = scene->mMeshes[i]->mName.C_Str();
		aiVector3D* verts = scene->mMeshes[i]->mVertices;
		aiVector3D* normals = scene->mMeshes[i]->mNormals;
		aiVector3D* uvs = scene->mMeshes[i]->mTextureCoords[0];
		aiVector3D* tangents = scene->mMeshes[i]->mTangents;

		for (unsigned int j = 0; j < scene->mMeshes[i]->mNumVertices; ++j)
		{
			glm::vec3 vertex;
			vertex.x = verts[j].x;
			vertex.y = verts[j].y;
			vertex.z = verts[j].z;
			mesh.m_PositionBuffer.push_back(vertex);
		}
		if (normals != NULL)
		{
			for (unsigned int j = 0; j < scene->mMeshes[i]->mNumVertices; ++j)
			{
				glm::vec3 normal;
				normal.x = normals[j].x;
				normal.y = normals[j].y;
				normal.z = normals[j].z;
				mesh.m_NormalBuffer.push_back(normal);
			}
		} else {
			for (unsigned int j = 0; j < scene->mMeshes[i]->mNumVertices; ++j)
			{
				mesh.m_NormalBuffer.push_back(glm::vec3());
			}
		}
		if (uvs != NULL)
		{
			for (unsigned int j = 0; j < scene->mMeshes[i]->mNumVertices; ++j)
			{
				glm::vec2 uv;
				uv.x = uvs[j].x;
				uv.y = uvs[j].y;
				mesh.m_Tex2DBuffer.push_back(uv);
			}
		} else {
			for (unsigned int j = 0; j < scene->mMeshes[i]->mNumVertices; ++j)
			{
				mesh.m_Tex2DBuffer.push_back(glm::vec2());
			}
		}
		/*if (tangents != NULL)
		{
			for (unsigned int j = 0; j < scene->mMeshes[i]->mNumVertices; ++j)
			{
				glm::vec4 tangent;
				tangent.x = tangents[j].x;
				tangent.y = tangents[j].y;
				tangent.z = tangents[j].z;
				mesh.m_TangentBuffer.push_back(tangent);
			}
		}*/
		for (unsigned int j = 0; j < scene->mMeshes[i]->mNumFaces; ++j)
		{
			mesh.m_IndexBuffer.push_back((unsigned short)scene->mMeshes[i]->mFaces[j].mIndices[0]);
			mesh.m_IndexBuffer.push_back((unsigned short)scene->mMeshes[i]->mFaces[j].mIndices[1]);
			mesh.m_IndexBuffer.push_back((unsigned short)scene->mMeshes[i]->mFaces[j].mIndices[2]);
		}
		if (mesh.m_PositionBuffer.size() > 0)
		{
			buildMesh(mesh, m);
		}
	}

	Logger::log(SUCCESS, (std::string("Loaded Model: ") + path).c_str());
	return m;
}


void DaeLoader::buildMesh(Mesh& mesh, Model* m)
{
	glGenVertexArrays(1, &mesh.uiVAO);
	glBindVertexArray(mesh.uiVAO);

	glGenBuffers(1, &mesh.uiBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mesh.uiBuffer);
	glBufferData(GL_ARRAY_BUFFER, mesh.m_PositionBuffer.size() * sizeof(glm::vec3), &mesh.m_PositionBuffer[0], GL_STATIC_DRAW);

	glGenBuffers(1, &mesh.uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mesh.uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, mesh.m_Tex2DBuffer.size() * sizeof(glm::vec2), &mesh.m_Tex2DBuffer[0], GL_STATIC_DRAW);

	glGenBuffers(1, &mesh.normalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mesh.normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, mesh.m_NormalBuffer.size() * sizeof(glm::vec3), &mesh.m_NormalBuffer[0], GL_STATIC_DRAW);

	//glGenBuffers(1, &mesh.tangentBuffer);
	//glBindBuffer(GL_ARRAY_BUFFER, mesh.tangentBuffer);
	//glBufferData(GL_ARRAY_BUFFER, mesh.m_TangentBuffer.size() * sizeof(glm::vec4), &mesh.m_TangentBuffer[0], GL_STATIC_DRAW);

	// Generate a buffer for the indices as well
	glGenBuffers(1, &mesh.indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.m_IndexBuffer.size() * sizeof(unsigned short), &mesh.m_IndexBuffer[0], GL_STATIC_DRAW);

	// Vertex positions
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, mesh.uiBuffer);
	glVertexAttribPointer(
		0,                  // attribute
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
		);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, mesh.uvBuffer);
	glVertexAttribPointer(
		1,                                // attribute
		2,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
		);

	// 3rd attribute buffer : normals
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, mesh.normalBuffer);
	glVertexAttribPointer(
		2,                                // attribute
		3,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
		);
	/*// 4rd attribute buffer : tangent
	glEnableVertexAttribArray(3);
	glBindBuffer(GL_ARRAY_BUFFER, mesh.tangentBuffer);
	glVertexAttribPointer(
		3,                                // attribute
		4,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
		);*/
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.indexBuffer);

	glBindVertexArray(0);

	m->addMesh(mesh);
}