#include "associate.h"
#include <iostream>

Associate::Associate(int id, std::string name, int positionId)
{
	m_id = id;
	m_name = name;
	m_positionId = positionId;
}


void Associate::showInfo()
{
	std::cout << "Employee ID: " << m_id
		<< "\tEmployee Name: " << m_name
		<< "\tEmployee Position: " << getPosition() << '\n';
}


std::string Associate::getPosition() 
{

	return "Associate";
}