/*********************************************************************
Project: Dissertation
Author: Josh Martin

Name: Pipeline
Description: Global pipeline for rendering. Stores matrices for 
rendering and calculation of render matrices as well.
*********************************************************************/
#ifndef PIPELINE_H
#define PIPELINE_H

#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <GLFW/glfw3.h>

class Pipeline {
public:
    Pipeline();
    ~Pipeline();
            
	static void scale(float x, float y, float z);
	static void rotate(float x, float y, float z);
	static void position(float x, float y, float z);
	static void scale(glm::vec3 s);
	static void rotate(glm::vec3 eulerRotation);
	static void position(glm::vec3 p);

	static glm::mat4 getTransformationMatrix();
	static glm::mat4 getTransformationMatrix2D();
	static glm::mat4 getModelMatrix();
	static glm::mat4 getWorldMatrix();

	static void setViewMatrix(glm::mat4);
	static void setProjectionMatrix(glm::mat4);
	
	
	static GLint m_MVPMatrix;
	static GLint m_VPMatrix;
	static GLint m_ProjectionMatrix;
	static GLint m_ViewMatrix;
	static GLint m_ModelMatrix;
	static glm::mat4 m_ShadowVP;

	//Global usage
	static glm::mat4 m_trans, m_rot, m_scale;
	static glm::mat4 m_projection, m_view, m_model, VP, MVP;
	static float zNear, zFar;

	static glm::vec3 Eye;
};
#endif