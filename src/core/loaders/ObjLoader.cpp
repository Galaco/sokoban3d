#include "ObjLoader.h"

ObjLoader::ObjLoader(){

}

ObjLoader::~ObjLoader(){
    
}

Model* ObjLoader::load(std::string path){
	Model* m = new Model;

	Mesh mesh;
	std::vector<GLfloat> storedNormals, storedUVs;
	std::vector<glm::vec3> localVertices, localNormals;
	std::vector<glm::vec2> localUVs;
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
		if( ( type == "#" ) || ( type == "g" ) || ( type == "s" ) )
		{
			getline(file , d , '\n' );
		} else
			if( type == "v" )
			{
				file >> coordx;
				file >> coordy;
				file >> coordz;
				localVertices.push_back( glm::vec3(coordx, coordy, coordz) );
			} else
			if( type == "f" )
			{
				for( int i=0 ; i < 2 ; ++i )
				{
					getline(file , d , '/' );
					val = atoi( d.c_str() );	
					indices.push_back( val - 1 );
					getline(file , d , '/' );
					if (d != ""){
						val = atoi( d.c_str() );
						storedUVs.push_back( (float)(val)-1 );
					}
					getline(file , d , ' ' );
					val = atoi( d.c_str() );
					storedNormals.push_back( (float)(val)-1 );
				}
				getline(file , d , '/' );
				val = atoi( d.c_str() );	
				indices.push_back( val - 1 );
				getline(file , d , '/' );
				if (d != ""){
					val = atoi( d.c_str() );
					storedUVs.push_back( (float)(val)-1 );
				}
				getline(file , d , '\n' );
				val = atoi( d.c_str() );
				storedNormals.push_back( (float)(val)-1 );
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
	}

	file.close();

	m->setFormat("obj");

	for(unsigned int i = 0; i < localVertices.size(); ++i){
		Vertex v;
		v.m_Pos = localVertices[i];
		if (localNormals.size() > i) {
			v.m_Normal = localNormals[i];
		}
		if (localUVs.size() < 1){
			v.m_Tex0 = glm::vec2(0,1);
		} else {
			v.m_Tex0 = localUVs[i];
		}
		mesh.m_Verts.push_back(v);
	}

	mesh.m_IndexBuffer = indices;

	this->prepareMesh(mesh, m);
	this->prepareNormals(mesh, m);
	glGenVertexArrays(1, &mesh.uiVAO); 
	glBindVertexArray(mesh.uiVAO); 

	glGenBuffers(1, &mesh.uiBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mesh.uiBuffer);
	glBufferData(GL_ARRAY_BUFFER, mesh.m_PositionBuffer.size() * sizeof(glm::vec3), &mesh.m_PositionBuffer[0] , GL_STATIC_DRAW);

	glGenBuffers(1, &mesh.uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mesh.uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, mesh.m_Tex2DBuffer.size() * sizeof(glm::vec2), &mesh.m_Tex2DBuffer[0], GL_STATIC_DRAW);

	glGenBuffers(1, &mesh.normalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mesh.normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, mesh.m_NormalBuffer.size() * sizeof(glm::vec3), &mesh.m_NormalBuffer[0], GL_STATIC_DRAW);

	// Generate a buffer for the indices as well
	glGenBuffers(1, &mesh.indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.m_IndexBuffer.size() * sizeof(unsigned short), &mesh.m_IndexBuffer[0] , GL_STATIC_DRAW);

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
	return m;
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