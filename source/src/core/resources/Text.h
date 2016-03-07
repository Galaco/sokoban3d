/*********************************************************************
Project: Dissertation
Author: Josh Martin

Name: Text
Description: A text class for holding inforamtion for font rendering
*********************************************************************/
#ifndef TEXT_H
#define TEXT_H

#include <string>

#include <glm/glm.hpp>

#include "Model.h"
#include "Mesh.h"
#include "Texture.h"

class Text {
public:
	Text(const char* string = "", double height = 12, Model* model = nullptr);
	~Text();

	void setColor(glm::vec3 color);
	glm::vec3& getColor();

	double getScaleScreenSpace();
	double getScale();

	std::string& getString();
	Model& getModel();

	static Texture* texture;

private:
	void generate(Model* model = nullptr);

	Model m_model;

	std::string m_string;
	glm::vec3 m_color;
	double m_height;
};
#endif
