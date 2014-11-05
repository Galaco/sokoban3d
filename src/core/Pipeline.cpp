#include "Pipeline.h"

#define TO_RAD(x) x*(3.141592f/180.0f)

glm::mat4 Pipeline::m_trans;
glm::mat4 Pipeline::m_rot;
glm::mat4 Pipeline::m_scale;

glm::mat4 Pipeline::m_projection;
glm::mat4 Pipeline::m_view;
glm::mat4 Pipeline::VP;
glm::mat4 Pipeline::MVP;
glm::vec3 Pipeline::Eye = glm::vec3(0);

glm::vec3 m_vTrans = glm::vec3(0);
glm::vec3 m_vRot = glm::vec3(0);
glm::vec3 m_vScale = glm::vec3(1);

GLint Pipeline::m_MVPMatrix;
GLint Pipeline::m_VPMatrix;
GLint Pipeline::m_ProjectionMatrix;
GLint Pipeline::m_ViewMatrix;
GLint Pipeline::m_ModelMatrix;

float Pipeline::zNear = 0.25f;
float Pipeline::zFar = 1024.f;

void Pipeline::scale(float x, float y, float z){
	m_vScale.x = x;
	m_vScale.y = y;
	m_vScale.z = z;
}

void Pipeline::rotate(float x, float y, float z){
	m_vRot.x = x;
	m_vRot.y = y;
	m_vRot.z = z;
}

void Pipeline::position(float x, float y, float z){
	m_vTrans.x = x;
	m_vTrans.y = y;
	m_vTrans.z = z;
}

void Pipeline::scale(glm::vec3 s){
	m_vScale = s;
}
void Pipeline::rotate(glm::vec3 eulerRotation){
	m_vRot = eulerRotation;
}
void Pipeline::position(glm::vec3 p){
	m_vTrans = p;
}


glm::mat4 Pipeline::getTransformationMatrix(){
	glm::mat4 m_transform = glm::translate(glm::mat4(1.0f), m_vTrans);
	m_transform = glm::rotate(m_transform, TO_RAD(m_vRot.y), (glm::vec3(0.f, 1.f, 0.f)));
	m_transform = glm::rotate(m_transform, TO_RAD(m_vRot.x), (glm::vec3(-1.0f, 0.f, 0.f)));
	m_transform = glm::rotate(m_transform, TO_RAD(m_vRot.z), (glm::vec3(0.f, 0.f, 1.f)));
	m_transform = glm::scale(m_transform, m_vScale);

	m_vScale.x = 1;
	m_vScale.y = 1;
	m_vScale.z = 1;
	m_vRot.x = 0;
	m_vRot.y = 0;
	m_vRot.z = 0;
	m_vTrans.x = 0;
	m_vTrans.y = 0;
	m_vTrans.z = 0;

	return VP * m_transform;
}


glm::mat4 Pipeline::getTransformationMatrix2D(){
	glm::mat4 m_transform = glm::translate(glm::mat4(1.0f), m_vTrans);
	m_transform = glm::rotate(m_transform, TO_RAD(m_vRot.y), (glm::vec3(0.f, 1.f, 0.f)));
	m_transform = glm::rotate(m_transform, TO_RAD(m_vRot.x), (glm::vec3(-1.0f, 0.f, 0.f)));
	m_transform = glm::rotate(m_transform, TO_RAD(m_vRot.z), (glm::vec3(0.f, 0.f, 1.f)));
	m_transform = glm::scale(m_transform, m_vScale);

	m_vScale.x = 1;
	m_vScale.y = 1;
	m_vScale.z = 1;
	m_vRot.x = 0;
	m_vRot.y = 0;
	m_vRot.z = 0;
	m_vTrans.x = 0;
	m_vTrans.y = 0;
	m_vTrans.z = 0;

	return glm::mat4(1.f) * m_transform;
}

glm::mat4 Pipeline::getModelMatrix(){
	glm::mat4 m_transform = glm::translate(glm::mat4(1.0f), m_vTrans);
	m_transform = glm::rotate(m_transform, m_vRot.y, (glm::vec3(0.f, 1.f, 0.f)));
	m_transform = glm::rotate(m_transform, m_vRot.x, (glm::vec3(-1.0f, 0.f, 0.f)));
	m_transform = glm::rotate(m_transform, m_vRot.z, (glm::vec3(0.f, 0.f, 1.f)));
	m_transform = glm::scale(m_transform, m_vScale);

	m_vScale.x = 1;
	m_vScale.y = 1;
	m_vScale.z = 1;
	m_vRot.x = 0;
	m_vRot.y = 0;
	m_vRot.z = 0;
	m_vTrans.x = 0;
	m_vTrans.y = 0;
	m_vTrans.z = 0;

	return m_transform;
}

glm::mat4 Pipeline::getWorldMatrix(){
	return VP;
}

void Pipeline::setProjectionMatrix(glm::mat4 projection){
	m_projection = projection;
	VP = m_projection * m_view;
}

void Pipeline::setViewMatrix(glm::mat4 view){
	m_view = view;
	VP = m_projection * m_view;
}