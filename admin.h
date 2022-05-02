#pragma once
#include <iostream>
#include "employee.h"
#include <fstream>
#define FILENAME "employeeData.txt"


class Admin
{
public:
	Admin();

	void showMenu();

	void exitSystem();




	int m_totalEmployeeNumber;
	Employee** m_employeeArray;

	void addEmployee();

	void save();
	
	bool m_fileEmpty;

	int getCurrentEmployeeNum(); 

	void initializeEmployee();




	void showEmployee();



	void deleteEmployee();
	int locateEmployee(int id);


	void modifyEmployee();


	void searchEmployee();

	void sortEmployee();


	void clearAllEmployee();


	~Admin();
};


