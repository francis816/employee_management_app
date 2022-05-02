#pragma once

#include <iostream>
#include <string>

class Employee
{
public:
	virtual void showInfo() = 0;
	virtual std::string getPosition() = 0;

	int m_id;
	std::string m_name;
	int m_positionId;

};