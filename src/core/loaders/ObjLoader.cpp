#include "ObjLoader.h"

ObjLoader::ObjLoader(){

}

ObjLoader::~ObjLoader(){
    
}

Model* ObjLoader::load(std::string path){
	Model* m = new Model;
	m->setFormat("obj");
	std::vector <glm::vec3> points;
	std::vector <glm::vec3> normals;
	std::vector <glm::vec2> texCoords;
	std::vector <int> faces, uvIndex;

	int nFaces = 0;

	std::ifstream objStream(path, std::ios::in);

	if (!objStream) {
		return m;
	}

	std::string line, token;
	std::vector<int> face;

	getline(objStream, line);
	while (!objStream.eof()) {
		trimString(line);
		if (line.length() > 0 && line.at(0) != '#') {
			std::istringstream lineStream(line);

			lineStream >> token;

			if (token == "v") {
				float x, y, z;
				lineStream >> x >> y >> z;
				points.push_back(glm::vec3(x, y, z));
			}
			else if (token == "vt") {
				// Process texture coordinate
				float s, t;
				lineStream >> s >> t;
				texCoords.push_back(glm::vec2(s, t));
			}
			else if (token == "vn") {
				float x, y, z;
				lineStream >> x >> y >> z;
				normals.push_back(glm::vec3(x, y, z));
			}
			else if (token == "f") {
				nFaces++;

				// Process face
				face.clear();
				size_t slash1, slash2;
				//int point, texCoord, normal;
				while (lineStream.good()) {
					std::string vertString;
					lineStream >> vertString;
					int pIndex = -1, nIndex = -1, tcIndex = -1;

					slash1 = vertString.find("/");
					if (slash1 == std::string::npos){
						pIndex = atoi(vertString.c_str()) - 1;
					}
					else {
						slash2 = vertString.find("/", slash1 + 1);
						pIndex = atoi(vertString.substr(0, slash1).c_str())
							- 1;
						if (slash2 > slash1 + 1) {
							tcIndex =
								atoi(vertString.substr(slash1 + 1, slash2).c_str())
								- 1;
						}
						nIndex =
							atoi(vertString.substr(slash2 + 1, vertString.length()).c_str())
							- 1;
					}
					if (pIndex == -1) {
						printf("Missing point index!!!");
					}
					else {
						face.push_back(pIndex);
					}
				}
				// If number of edges in face is greater than 3,
				// decompose into triangles as a triangle fan.
				if (face.size() > 3) {
					int v0 = face[0];
					int v1 = face[1];
					int v2 = face[2];
					// First face
					faces.push_back(v0);
					faces.push_back(v1);
					faces.push_back(v2);
					for (GLuint i = 3; i < face.size(); i++) {
						v1 = v2;
						v2 = face[i];
						faces.push_back(v0);
						faces.push_back(v1);
						faces.push_back(v2);
					}
				}
				else {
					faces.push_back(face[0]);
					faces.push_back(face[1]);
					faces.push_back(face[2]);
				}
			}
		}
		getline(objStream, line);
	}

	objStream.close();

	if (normals.size() == 0) {
		generateAveragedNormals(points, normals, faces);
	}

	std::vector<glm::vec4> tangents;
	if (texCoords.size() > 0) {
		generateTangents(points, normals, faces, texCoords, tangents);
	}

	Mesh mesh;
	mesh.m_PositionBuffer = points;
	mesh.m_NormalBuffer = normals;
	mesh.m_Tex2DBuffer = texCoords;
	mesh.m_TangentBuffer = tangents;

	std::vector<Triangle> faceList;
	std::vector<unsigned short> indices;
	for (unsigned int i = 0; i < faces.size(); i += 3)
	{
		Triangle triangle;
		triangle.m_Indices[0] = faces[i];
		triangle.m_Indices[1] = faces[i+1];
		triangle.m_Indices[2] = faces[i+2];
		faceList.push_back(triangle);
		indices.push_back(faces[i]);
		indices.push_back(faces[i+1]);
		indices.push_back(faces[i+2]);
	}

	mesh.m_IndexBuffer = indices;
	mesh.m_Tris = faceList;

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

	glGenBuffers(1, &mesh.tangentBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mesh.tangentBuffer);
	glBufferData(GL_ARRAY_BUFFER, mesh.m_TangentBuffer.size() * sizeof(glm::vec4), &mesh.m_TangentBuffer[0], GL_STATIC_DRAW);

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

	// 4rd attribute buffer : tangents
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, mesh.tangentBuffer);
	glVertexAttribPointer(
		3,                                // attribute
		4,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
		);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.indexBuffer);

	glBindVertexArray(0);

	m->addMesh(mesh);
}

void ObjLoader::generateAveragedNormals(
	const std::vector<glm::vec3> & points,
	std::vector<glm::vec3> & normals,
	const std::vector<int> & faces)
{
	for (glm::uint i = 0; i < points.size(); i++) {
		normals.push_back(glm::vec3(0.0f));
	}

	for (glm::uint i = 0; i < faces.size(); i += 3) {
		const glm::vec3 & p1 = points[faces[i]];
		const glm::vec3 & p2 = points[faces[i + 1]];
		const glm::vec3 & p3 = points[faces[i + 2]];

		glm::vec3 a = p2 - p1;
		glm::vec3 b = p3 - p1;
		glm::vec3 n = glm::normalize(glm::cross(a, b));

		normals[faces[i]] += n;
		normals[faces[i + 1]] += n;
		normals[faces[i + 2]] += n;
	}

	for (glm::uint i = 0; i < normals.size(); i++) {
		normals[i] = glm::normalize(normals[i]);
	}
}

void ObjLoader::generateTangents(
	const std::vector<glm::vec3> & points,
	const std::vector<glm::vec3> & normals,
	const std::vector<int> & faces,
	const std::vector<glm::vec2> & texCoords,
	std::vector<glm::vec4> & tangents)
{
	std::vector<glm::vec3> tan1Accum;
	std::vector<glm::vec3> tan2Accum;

	for (glm::uint i = 0; i < points.size(); i++) {
		tan1Accum.push_back(glm::vec3(0.0f));
		tan2Accum.push_back(glm::vec3(0.0f));
		tangents.push_back(glm::vec4(0.0f));
	}

	// Compute the tangent vector
	for (glm::uint i = 0; i < faces.size(); i += 3)
	{
		const glm::vec3 &p1 = points[faces[i]];
		const glm::vec3 &p2 = points[faces[i + 1]];
		const glm::vec3 &p3 = points[faces[i + 2]];

		const glm::vec2 &tc1 = texCoords[faces[i]];
		const glm::vec2 &tc2 = texCoords[faces[i + 1]];
		const glm::vec2 &tc3 = texCoords[faces[i + 2]];

		glm::vec3 q1 = p2 - p1;
		glm::vec3 q2 = p3 - p1;
		float s1 = tc2.x - tc1.x, s2 = tc3.x - tc1.x;
		float t1 = tc2.y - tc1.y, t2 = tc3.y - tc1.y;
		float r = 1.0f / (s1 * t2 - s2 * t1);
		glm::vec3 tan1((t2*q1.x - t1*q2.x) * r,
			(t2*q1.y - t1*q2.y) * r,
			(t2*q1.z - t1*q2.z) * r);
		glm::vec3 tan2((s1*q2.x - s2*q1.x) * r,
			(s1*q2.y - s2*q1.y) * r,
			(s1*q2.z - s2*q1.z) * r);
		tan1Accum[faces[i]] += tan1;
		tan1Accum[faces[i + 1]] += tan1;
		tan1Accum[faces[i + 2]] += tan1;
		tan2Accum[faces[i]] += tan2;
		tan2Accum[faces[i + 1]] += tan2;
		tan2Accum[faces[i + 2]] += tan2;
	}

	for (glm::uint i = 0; i < points.size(); ++i)
	{
		const glm::vec3 &n = normals[i];
		glm::vec3 &t1 = tan1Accum[i];
		glm::vec3 &t2 = tan2Accum[i];

		// Gram-Schmidt orthogonalize
		tangents[i] = glm::vec4(glm::normalize(t1 - (glm::dot(n, t1) * n)), 0.0f);
		// Store handedness in w
		tangents[i].w = (glm::dot(glm::cross(n, t1), t2) < 0.0f) ? -1.0f : 1.0f;
	}
	tan1Accum.clear();
	tan2Accum.clear();
}


void ObjLoader::trimString(std::string & str) {
	const char * whiteSpace = " \t\n\r";
	size_t location;
	location = str.find_first_not_of(whiteSpace);
	str.erase(0, location);
	location = str.find_last_not_of(whiteSpace);
	str.erase(location + 1);
}

