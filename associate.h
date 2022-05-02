#pragma once
#include <iostream>
#include "employee.h"


class Associate : public Employee
{
public:
	Associate(int id, std::string name, int division);

	virtual void showInfo();
	virtual std::string getPosition();
};