#include <iostream>
#include "employee.h"
#include "senior.h"

Senior::Senior(int id, std::string name, int positionId)
{
	m_id = id;
	m_name = name;
	m_positionId = positionId;
}

void Senior::showInfo()
{
	std::cout << "Employee ID: " << m_id
		<< "\tEmployee Name: " << m_name
		<< "\tEmployee Position: " << getPosition() << '\n';
}

std::string Senior::getPosition()
{
	return "Senior";
}