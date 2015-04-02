#include "Md5Loader.h"

Md5Loader::Md5Loader(){

}

Md5Loader::~Md5Loader(){
    
}

Model* Md5Loader::load(std::string path){
	Model* m = new Model;
	/*std::ifstream file(path);
	if ( !file.is_open() ) {
		Logger::log(ERROR_, std::string("Animation: Failed to open " + path).c_str());
		return false;
	}

	// store the parent path used for loading images relative to this file.
	int found = path.find_last_of("/");
	std::string parent_path = path.substr(0, found);

	std::string param;
	std::string junk;   // Read any irellevant data from the file (mostly { & })

	int pos = static_cast<int>(file.tellg());
	file.seekg(0, std::ios::end );
	int fileLength = static_cast<int>(file.tellg());
	// Restore the position of the get pointer
	file.seekg(pos);
	assert( fileLength > 0 );

	//m->getJoints().clear();
	m->getMeshes().clear();

	file >> param;

	while ( !file.eof() )
	{
		if (param == "MD5Version") {
			file >> junk;
			m->setFileFormatVersion(junk);
			assert(  m->getFileFormatVersion() == "10" );	//Confirm file is indeed md5. Not concrete as could be manually edited
		} else if (param == "commandline") {
			file.ignore( fileLength, '\n' );				//Doom specific entries it seems. Ignore
		} else if ( param == "numJoints" ) {
			file >> m->getJointCount();
			 //m->getJoints().reserve( m->getJointCount());	//Joints in the object
		} else if ( param == "numMeshes" ) {
			file >>  m->getMeshCount();
			 m->getMeshes().reserve( m->getMeshCount());	//Meshes in the object
		} else if ( param == "joints" ) {
			/*Joint joint;
			file >> junk; // Read the '{' character
			for ( int i = 0; i <  m->getJointCount(); ++i )	//Data is:name, parent, pos.xyz, rot.xyz
			{
				file >> joint.m_Name >> joint.m_ParentID >> junk
					>> joint.m_Pos.x >> joint.m_Pos.y >> joint.m_Pos.z >> junk >> junk
					>> joint.m_Orient.x >> joint.m_Orient.y >> joint.m_Orient.z >> junk;

				size_t n;
				while ( ( n = joint.m_Name.find('\"') ) != std::string::npos ) joint.m_Name.erase(n,1);
				float t = 1.0f - ( joint.m_Orient.x * joint.m_Orient.x ) - ( joint.m_Orient.y * joint.m_Orient.y ) - ( joint.m_Orient.z * joint.m_Orient.z );
				if ( t < 0.0f ) {
					joint.m_Orient.w = 0.0f;
				} else {
					joint.m_Orient.w = -sqrtf(t);
				}

				m->getJoints().push_back(joint);	//Add parsed joint to list
				// Ignore everything else on the line up to the end-of-line character.
				file.ignore( fileLength, '\n' );
			}
			file >> junk; // Read the '}' character
		}
		else if ( param == "mesh" )
		{
			Mesh mesh;	//Create mesh on the stack

			int numVerts, numTris, numWeights;

			file >> junk; // Read the '{' character
			file >> param;
			while ( param != "}" )  // Read until we get to the '}' character
			{
				if ( param == "shader" )
				{
					/*file >> mesh.m_Shader;
					size_t n;
					while ( ( n = mesh.m_Shader.find('\"') ) != std::string::npos ) mesh.m_Shader.erase(n,1);
					std::string shaderPath = mesh.m_Shader;
					std::string texturePath;
					int has_path= shaderPath.find_last_of("/");
					if ( has_path > 0 ) {
						texturePath = shaderPath;
					} else {
						texturePath = parent_path + "/" + shaderPath;
					}

					int findExt = path.find_last_of(".");
					int findLastDir = path.find_last_of("/");
					if ( findExt <= findLastDir ) {
						texturePath += ".tga";
					}	//Get directory info

					Texture* tex = new Texture;	//Create new texture (on the heap?!)
					mesh.m_TexID = tex->load(texturePath.c_str(), 'd');
					m->addTexture(texturePath, tex);

					file.ignore(fileLength, '\n' ); // Ignore everything else on the line
				} else if ( param == "numverts") {
					file >> numVerts;               // Read in the vertices
					file.ignore( fileLength, '\n' );
					for ( int i = 0; i < numVerts; ++i )
					{
						Vertex vert;

						file >> junk >> junk >> junk                    // vert vertIndex (
							>> vert.m_Tex0.x >> vert.m_Tex0.y >> junk  //  s t )
							>> vert.m_StartWeight >> vert.m_WeightCount;

						file.ignore( fileLength, '\n' );

						mesh.m_Verts.push_back(vert);
						mesh.m_Tex2DBuffer.push_back(vert.m_Tex0);
					}  
				} else if ( param == "numtris" ) {
					file >> numTris;
					file.ignore( fileLength, '\n' );
					for ( int i = 0; i < numTris; ++i )
					{
						Triangle tri;
						file >> junk >> junk >> tri.m_Indices[0] >> tri.m_Indices[1] >> tri.m_Indices[2];

						file.ignore( fileLength, '\n' );

						mesh.m_Tris.push_back(tri);
						mesh.m_IndexBuffer.push_back( (GLuint)tri.m_Indices[0] );
						mesh.m_IndexBuffer.push_back( (GLuint)tri.m_Indices[1] );
						mesh.m_IndexBuffer.push_back( (GLuint)tri.m_Indices[2] );
					}              
				} else if ( param == "numweights" ) {
					file >> numWeights;
					file.ignore( fileLength, '\n' );
					for ( int i = 0; i < numWeights; ++i )
					{
						Weight weight;
						file >> junk >> junk >> weight.m_JointID >> weight.m_Bias >> junk
							>> weight.m_Pos.x >> weight.m_Pos.y >> weight.m_Pos.z >> junk;

						file.ignore( fileLength, '\n' );
						mesh.m_Weights.push_back(weight);
					}
				} else {
					file.ignore( fileLength, '\n' );
				}

				file >> param;
			}

			this->prepareMesh(mesh, m);

			//Build the buffer object for upload
			glGenVertexArrays(1, &mesh.uiVAO); 
			glBindVertexArray(mesh.uiVAO); 

			glGenBuffers(1, &mesh.uiBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, mesh.uiBuffer);
			glBufferData(GL_ARRAY_BUFFER, mesh.m_PositionBuffer.size() * sizeof(glm::vec3), &mesh.m_PositionBuffer[0] , GL_STATIC_DRAW);	//STREAM_DRAW?

			glGenBuffers(1, &mesh.uvBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, mesh.uvBuffer);
			glBufferData(GL_ARRAY_BUFFER, mesh.m_Tex2DBuffer.size() * sizeof(glm::vec2), &mesh.m_Tex2DBuffer[0], GL_STATIC_DRAW);

			glGenBuffers(1, &mesh.normalBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, mesh.normalBuffer);
			glBufferData(GL_ARRAY_BUFFER, mesh.m_NormalBuffer.size() * sizeof(glm::vec3), &mesh.m_NormalBuffer[0], GL_STATIC_DRAW);	//STREAM DRAW?

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

		}

		file >> param;
	}

	assert(  m->getJoints().size() ==  m->getJointCount() );
	assert(  m->getMeshes().size() ==  m->getMeshCount() );

	m->setFormat("md5mesh");*/
	return m;
}


// Compute the position of the vertices in object local space
// in the skeleton's bind pose
bool Md5Loader::prepareMesh( Mesh& mesh, Model* m )
{
	/*mesh.m_PositionBuffer.clear();
	mesh.m_Tex2DBuffer.clear();

	// Compute vertex positions
	for ( unsigned int i = 0; i < mesh.m_Verts.size(); ++i )
	{
		glm::vec3 finalPos(0);
		Vertex& vert = mesh.m_Verts[i];

		vert.m_Pos = glm::vec3(0);
		vert.m_Normal = glm::vec3(0);

		// Sum the position of the weights
		for ( int j = 0; j < vert.m_WeightCount; ++j )
		{
			const Weight& weight = mesh.m_Weights[vert.m_StartWeight + j];
			const Joint& joint = m->getJoints()[weight.m_JointID];

			// Convert the weight position from Joint local space to object space
			glm::vec3 rotPos = joint.m_Orient * weight.m_Pos;

			vert.m_Pos += ( joint.m_Pos + rotPos ) * weight.m_Bias;
		}

		mesh.m_PositionBuffer.push_back(vert.m_Pos);
		mesh.m_Tex2DBuffer.push_back(vert.m_Tex0);
	}

	//weird fix to stop collada
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

		glm::vec3 normal = glm::normalize( vert.m_Normal );
		mesh.m_NormalBuffer.push_back( normal );

		// Reset the normal to calculate the bind-pose normal in joint space
		vert.m_Normal = glm::vec3(0);

		// Put the bind-pose normal into joint-local space
		// so the animated normal can be computed faster later
		for ( int j = 0; j < vert.m_WeightCount; ++j )
		{
			const Weight& weight = mesh.m_Weights[vert.m_StartWeight + j];
			const Joint& joint = m->getJoints()[weight.m_JointID];
			vert.m_Normal += ( normal * joint.m_Orient ) * weight.m_Bias;
		}
	}*/

	return true;
}


// Compute the vertex normals in the Mesh's bind pose
bool Md5Loader::prepareNormals( Mesh& mesh, Model* m )
{
	/*mesh.m_NormalBuffer.clear();

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

		glm::vec3 normal = glm::normalize( vert.m_Normal );
		mesh.m_NormalBuffer.push_back( normal );

		// Reset the normal to calculate the bind-pose normal in joint space
		vert.m_Normal = glm::vec3(0);

		// Put the bind-pose normal into joint-local space
		// so the animated normal can be computed faster later
		for ( int j = 0; j < vert.m_WeightCount; ++j )
		{
			const Weight& weight = mesh.m_Weights[vert.m_StartWeight + j];
			const Joint& joint = m->getJoints()[weight.m_JointID];
			vert.m_Normal += ( normal * joint.m_Orient ) * weight.m_Bias;
		}
	}
	*/
	return true;
}