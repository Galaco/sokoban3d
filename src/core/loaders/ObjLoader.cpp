#include "ObjLoader.h"

ObjLoader::ObjLoader(){

}

ObjLoader::~ObjLoader(){
    
}

Model* ObjLoader::load(std::string path){
	Model* m = new Model;
	m->setFormat("obj");
	int vertexOffset = 1;
	int uvOffset = 1;
	int normalOffset = 1;

	Mesh mesh;
	std::vector<GLfloat> storedNormals, storedUVs;
	std::vector<glm::vec3> localVertices, localNormals;
	std::vector<glm::vec2> localUVs;
	TriangleList triangles;
	std::vector<unsigned short> indices;
	std::ifstream file;
	std::string type , d;
	GLfloat coordx,coordy,coordz;
	GLushort val = 0;
	file.open( path );
	if( ! ( file.is_open() ) )
	{
		std::cout << "Model: could not load " << path << std::endl;
		return false;
	}
	while( file >> type )
	{
		if( type == "v" )
		{
			file >> coordx;
			file >> coordy;
			file >> coordz;
			localVertices.push_back( glm::vec3(coordx, coordy, coordz) );
		} else
		if( type == "f" ) //Note needs rewriting for support for models that have neither normals NOR UVs
		{
			getline(file, d, '\n');
			std::stringstream ver(d);

			for (unsigned int i=0; i<3; ++i)
			{
				std::string rawVert;
				ver >> rawVert;
				std::stringstream vert(rawVert);
				std::string segment;
				std::vector<std::string> seglist;
				Triangle triangle;
				while (std::getline(vert, segment, '/'))
				{
					seglist.push_back(segment);
				}

				if (seglist.size() == 1){
					if (d != "") {
						val = atoi(seglist[0].c_str());
						indices.push_back(val - vertexOffset);
						triangle.m_Indices[i] = val - vertexOffset;
					}
				} else
				if (seglist.size() == 2){
					if (seglist[0] != "") {
						val = atoi(seglist[0].c_str());
						indices.push_back(val - vertexOffset);
						triangle.m_Indices[i] = val - vertexOffset;
					}
					if (seglist[1] != "") {
						val = atoi(seglist[1].c_str());
						storedUVs.push_back((float)(val)-uvOffset);
					}
				} else
				if (seglist.size() == 3){
					if (seglist[0] != "") {
						val = atoi(seglist[0].c_str());
						indices.push_back(val - vertexOffset);
						triangle.m_Indices[i] = val - vertexOffset;
					}
					if (seglist[1] != "") {
						val = atoi(seglist[1].c_str());
						storedUVs.push_back((float)(val)-uvOffset);
					}
					if (seglist[2] != "") {
						val = atoi(seglist[2].c_str());
						storedNormals.push_back((float)(val)-normalOffset);
					}
				}

				triangles.push_back(triangle);
			}
		} else
		if( type == "vn" )
		{
			file >> coordx;
			file >> coordy;
			file >> coordz;
			localNormals.push_back( glm::vec3(coordx, coordy, coordz) );
		} else
		if( type == "vt" )
		{
			file >> coordx;
			file >> coordy;
			localUVs.push_back( glm::vec2(coordx, coordy) );
		}
		else 
		if (type == "o" && localVertices.size() != 0)
		{
			file >> d;
			Logger::log(INFO, d.c_str());
			Mesh nthMesh;
			for (unsigned int i = 0; i < localVertices.size(); ++i){
				Vertex v;
				v.m_Pos = localVertices[i];

				if (localNormals.size() > i) {
					v.m_Normal = localNormals[i];
				} else {
					v.m_Normal = glm::vec3(0, 1, 0);
				}

				if (localUVs.size() > i){
					v.m_Tex0 = localUVs[i];
				} else {
					v.m_Tex0 = glm::vec2(0, 1);
				}
				nthMesh.m_Verts.push_back(v);
			}
			
			//nthMesh.m_Tris = triangles;
			nthMesh.m_IndexBuffer = indices;

			this->prepareMesh(nthMesh, m);
			this->prepareNormals(nthMesh, m);
			this->buildMesh(nthMesh, m);

			vertexOffset = localVertices.size() + 1;
			uvOffset = localUVs.size() + 1;
			normalOffset = localNormals.size() + 1;
			localVertices.clear();
			localNormals.clear();
			localUVs.clear();
			indices.clear();
			storedUVs.clear();
			storedNormals.clear();
		}
		else
		{
			getline(file, d, '\n');
		}
	}

	file.close();

	for(unsigned int i = 0; i < localVertices.size(); ++i){
		Vertex v;
		v.m_Pos = localVertices[i];

		if (localNormals.size() > i) {
			v.m_Normal = localNormals[i];
		} else {
			v.m_Normal = glm::vec3(0, 1, 0);
		}

		if (localUVs.size() > i){
			v.m_Tex0 = localUVs[i];
		} else {
			v.m_Tex0 = glm::vec2(0, 1);
		}

		mesh.m_Verts.push_back(v);
	}

	//nthMesh.m_Tris = triangles;
	mesh.m_IndexBuffer = indices;

	this->prepareMesh(mesh, m);
	this->prepareNormals(mesh, m);
	this->buildMesh(mesh, m);

	return m;
}


void ObjLoader::buildMesh(Mesh& mesh, Model* m)
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

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.indexBuffer);

	glBindVertexArray(0);

	m->addMesh(mesh);
}

// Compute the position of the vertices in object local space
// in the skeleton's bind pose
bool ObjLoader::prepareMesh( Mesh& mesh, Model* m )
{
	mesh.m_PositionBuffer.clear();
	mesh.m_Tex2DBuffer.clear();

	// Compute vertex positions
	for ( unsigned int i = 0; i < mesh.m_Verts.size(); ++i )
	{
		Vertex& vert = mesh.m_Verts[i];

		mesh.m_PositionBuffer.push_back(vert.m_Pos);
		mesh.m_Tex2DBuffer.push_back(vert.m_Tex0);
	}

	mesh.m_NormalBuffer.clear();

	// Loop through all triangles and calculate the normal of each triangle
	for ( unsigned int i = 0; i < mesh.m_Tris.size(); ++i )
	{
		glm::vec3 v0 = mesh.m_Verts[ mesh.m_Tris[i].m_Indices[0] ].m_Pos;
		glm::vec3 v1 = mesh.m_Verts[ mesh.m_Tris[i].m_Indices[1] ].m_Pos;
		glm::vec3 v2 = mesh.m_Verts[ mesh.m_Tris[i].m_Indices[2] ].m_Pos;

		glm::vec3 normal = glm::cross( v2 - v0, v1 - v0 );

		mesh.m_Verts[ mesh.m_Tris[i].m_Indices[0] ].m_Normal += normal;
		mesh.m_Verts[ mesh.m_Tris[i].m_Indices[1] ].m_Normal += normal;
		mesh.m_Verts[ mesh.m_Tris[i].m_Indices[2] ].m_Normal += normal;
	}
	return true;
}


// Compute the vertex normals in the Mesh's bind pose
bool ObjLoader::prepareNormals( Mesh& mesh, Model* m )
{
	mesh.m_NormalBuffer.clear();

	// Loop through all triangles and calculate the normal of each triangle
	for ( unsigned int i = 0; i < mesh.m_Tris.size(); ++i )
	{
		glm::vec3 v0 = mesh.m_Verts[ mesh.m_Tris[i].m_Indices[0] ].m_Pos;
		glm::vec3 v1 = mesh.m_Verts[ mesh.m_Tris[i].m_Indices[1] ].m_Pos;
		glm::vec3 v2 = mesh.m_Verts[ mesh.m_Tris[i].m_Indices[2] ].m_Pos;

		glm::vec3 normal = glm::cross( v2 - v0, v1 - v0 );

		mesh.m_Verts[ mesh.m_Tris[i].m_Indices[0] ].m_Normal += normal;
		mesh.m_Verts[ mesh.m_Tris[i].m_Indices[1] ].m_Normal += normal;
		mesh.m_Verts[ mesh.m_Tris[i].m_Indices[2] ].m_Normal += normal;
	}

	// Now normalize all the normals
	for ( unsigned int i = 0; i < mesh.m_Verts.size(); ++i )
	{
		Vertex& vert = mesh.m_Verts[i];
		mesh.m_NormalBuffer.push_back( vert.m_Normal );
	}

	return true;
}