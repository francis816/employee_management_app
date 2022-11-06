#pragma once
#include <iostream>
#include "employee.h"
#include <fstream>
#define FILENAME "employeeData.txt"


class Admin
{
public:
	Admin();
	~Admin();
	void showMenu();
	void exitSystem();
	void addEmployee();
	void save();
	int getCurrentEmployeeNum(); 
	void initializeEmployee();
	void showEmployee();
	void deleteEmployee();
	int locateEmployee(int id);
	void modifyEmployee();
	void searchEmployee();
	void sortEmployee();
	void clearAllEmployee();
	
	bool m_fileEmpty;
	int m_totalEmployeeNumber;
	Employee** m_employeeArray;
};


