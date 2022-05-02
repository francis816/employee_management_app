#pragma once
#include <iostream>
#include "employee.h"
#include <string>

class Manager : public Employee
{
public:
	Manager(int id, std::string name, int positionId);

	void showInfo();
	std::string getPosition();

};