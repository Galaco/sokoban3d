#include "CSelectable.h"

CSelectable::CSelectable(){
	m_type = "Selectable";
	m_selected = false;
	m_hovered = false;
}

CSelectable::~CSelectable(){
	
}


void CSelectable::setSelected(bool isSelected)
{
	m_selected = isSelected;
}

void CSelectable::setHovered(bool isHovered)
{
	m_hovered = isHovered;
}

bool CSelectable::getSelected()
{
	return m_selected;
}

bool CSelectable::getHovered()
{
	return m_hovered;
}