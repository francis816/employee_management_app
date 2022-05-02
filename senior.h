#pragma once
#include <iostream>
#include "employee.h"
#include <string>


class Senior : public Employee
{
public:
	Senior(int id, std::string name, int positionId);

	virtual void showInfo();
	virtual std::string getPosition();

};