/*********************************************************************
Project: Dissertation
Author: Josh Martin

Name: Text
Description: A text class for holding inforamtion for font rendering
*********************************************************************/
#ifndef TEXT_H
#define TEXT_H

#include <glm/glm.hpp>

#include "Texture.h"
#include "Model.h"
#include "Mesh.h"

#include <string>

class Text {
public:
	Text(const char* string = "", double height = 12);
	~Text();

	void setColor(glm::vec3 color);
	glm::vec3& getColor();

	double getScaleScreenSpace();
	double getScale();

	std::string& getString();
	Model& getModel();

	static Texture* texture;

private:
	void generate();

	Model m_model;

	std::string m_string;
	glm::vec3 m_color;
	double m_height;
};
#endif
