#include <iostream>
#include "manager.h"
#include <string>

Manager::Manager(int id, std::string name, int positionId)
{
	m_id = id;
	m_name = name;
	m_positionId = positionId;
}


void Manager::showInfo()
{
	std::cout << "Employee ID: " << m_id
		<< "\tEmployee Name: " << m_name
		<< "\tEmployee Position: " << getPosition() << '\n';
}


std::string Manager::getPosition()
{
	return "Manager";
}