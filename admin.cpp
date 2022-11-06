#include <iostream>
#include "admin.h"
#include "associate.h"
#include "senior.h"
#include "manager.h"

Admin::Admin() // constrcutor, as long as we create an admin, we start reading file
{
	// load employees from file

	std::ifstream ifs;
	ifs.open(FILENAME, std::ios::in);

	if (!ifs.is_open())
	{
		//std::cout << "file not existed\n"; 
		m_totalEmployeeNumber = 0;
		m_employeeArray = nullptr;
		m_fileEmpty = true;
		ifs.close();
		return;
	}

	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//std::cout << "file empty\n";
		m_totalEmployeeNumber = 0;
		m_employeeArray = nullptr;
		m_fileEmpty = true;
		ifs.close();
		return;
	}

	int num = getCurrentEmployeeNum();

	//std::cout << "current employees: " << num << '\n';

	// read data from file

	m_totalEmployeeNumber = num;
	m_employeeArray = new Employee * [m_totalEmployeeNumber];

	initializeEmployee();

	//for (int i = 0; i < m_totalEmployeeNumber; i++)
	//{
	//	std::cout << "Employee ID: " << m_employeeArray[i]->m_id
	//		<< "\tEmployee Name: " << m_employeeArray[i]->m_name
	//		<< "\tEmployee Position: " << m_employeeArray[i]->m_positionId << "\n";
	//}

}

void Admin::showMenu()
{
	std::cout << "*****************************************************" << '\n';
	std::cout << "***** Welcome to the Employee Management System *****" << '\n';
	std::cout << "***** ----------------------------------------- *****" << '\n';
	std::cout << "*****          0. Exit System Program           *****" << '\n';
	std::cout << "*****          1. Add Employee Info             *****" << '\n';
	std::cout << "*****          2. Show Employee Info            *****" << '\n';
	std::cout << "*****          3. Delete Employee               *****" << '\n';
	std::cout << "*****          4. Edit Employee Info            *****" << '\n';
	std::cout << "*****          5. Search Employee               *****" << '\n';
	std::cout << "*****          6. Sort Employee List            *****" << '\n';
	std::cout << "*****          7. Clear all Employee Info       *****" << '\n';
	std::cout << "*****************************************************" << '\n';
	std::cout << '\n';
}


void Admin::exitSystem()
{
	std::cout << "You have exited the system successfully.\n";
	system("pause");
	exit(0);
}




void Admin::addEmployee()
{
	std::cout << "Please enter the amount of employees you want to add: \n";
	int addNum = 0;
	std::cin >> addNum;

	if (addNum > 0)
	{
		int newTotalEmployeeNumber = m_totalEmployeeNumber + addNum;

		// a pointer to an array of pointers
		// expand our array
		Employee** newEmployeeArray = new Employee* [newTotalEmployeeNumber];

		// if current employee array has data, copy and past to the new array
		if (m_employeeArray != nullptr)
		{
			for (int i = 0; i < m_totalEmployeeNumber; i++)
			{
				newEmployeeArray[i] = m_employeeArray[i];
			}
		}

		// adding new employee
		for (int i = 0; i < addNum; i++)
		{
			int id;
			std::string name;
			int positionSelect;

			std::cout << "Please enter " << i + 1 << ". employee ID: \n";
			std::cin >> id;

			std::cout << "Please enter " << i + 1 << ". employee Name: \n";
			std::cin.ignore(); // skip \n (enter key) from cin >> id;
			std::getline(std::cin, name);

			std::cout << "Please select employee position: \n";
			std::cout << "1. Associate\n";
			std::cout << "2. Senior\n";
			std::cout << "3. Manager\n";
			std::cin >> positionSelect;


			// maybe 
			Employee* employee = nullptr; // initialize 

			switch (positionSelect)
			{
			case 1:
				employee = new Associate(id, name, 1);
				break;
			case 2:
				employee = new Senior(id, name, 2);
				break;
			case 3:
				employee = new Manager(id, name, 3);
				break;
			default:
				break;
			}

			// save this newly added person into the new array at the correct index, 1st person = index 0
			newEmployeeArray[m_totalEmployeeNumber + i] = employee;
		}

		// after adding
		delete[] m_employeeArray;
		m_employeeArray = newEmployeeArray; // point to new place before it got destroyed

		m_totalEmployeeNumber = newTotalEmployeeNumber; // newTotalEmpoyeeNumber is also a local virable and will get destroyed after adding

		// save employee to file
		save();

		m_fileEmpty = false;

		if (addNum == 1)
			std::cout << "successfully added " << addNum << " new employee.\n";
		else
			std::cout << "successfully added " << addNum << " new employees.\n";
	}
	else
	{
		std::cout << "invalid number, please try again. \n";
	}

	system("pause");
	system("cls");
}


void Admin::save()
{
	std::ofstream ofs;
	ofs.open(FILENAME, std::ios::out);

	for (int i = 0; i < m_totalEmployeeNumber; i++)
	{
		ofs << m_employeeArray[i]->m_id << " " << m_employeeArray[i]->m_name << " " << m_employeeArray[i]->m_positionId << '\n';
	}

	ofs.close();

}


int Admin::getCurrentEmployeeNum()
{
	std::ifstream ifs;
	ifs.open(FILENAME, std::ios::in);


	int id;
	std::string name;
	int positionId;
	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> positionId)
	{
		num++;
	}
	return num;
}


void Admin::initializeEmployee()
{
	std::ifstream ifs;
	ifs.open(FILENAME, std::ios::in);
	
	int id;
	std::string name;
	int positionId;
	
	int index = 0;

	while (ifs >> id && ifs >> name && ifs >> positionId)
	{
		Employee* employee = nullptr;
		if (positionId == 1) employee = new Associate(id, name, positionId);

		else if (positionId == 2) employee = new Senior(id, name, positionId);

		else if (positionId == 3) employee = new Manager(id, name, positionId);


		m_employeeArray[index] = employee;
		index++;
	}

	ifs.close();
}


void Admin::showEmployee()
{
	if (m_fileEmpty)
	{
		std::cout << "current employee record is empty.\n";
	}
	else
	{
		for (int i = 0; i < m_totalEmployeeNumber; i++)
		{
			m_employeeArray[i]->showInfo();
		}
	}

	system("pause");
	system("cls");
}



int Admin::locateEmployee(int id)
{
	int index = -1;
	for (int i = 0; i < m_totalEmployeeNumber; i++)
	{
		if (m_employeeArray[i]->m_id == id)
		{
			index = i;
			break;
		}
	}
	return index;
}



void Admin::deleteEmployee()
{
	if (m_fileEmpty) std::cout << "no employee record\n";
	else
	{
		std::cout << "please enter the employee ID of the meployee you want to remove from system\n";
		int id = 0;
		std::cin >> id;

		int result = locateEmployee(id);
		if (result != -1)
		{
			for (int i = result; i < m_totalEmployeeNumber - 1; i++)
			{
				m_employeeArray[i] = m_employeeArray[i + 1]; // move employees forward starting from the location we want (to cover the employee we want to remove)
			}
			m_totalEmployeeNumber -= 1;

			save(); // save to document 

			std::cout << "employee sucessfully deleted\n";
		}
		else
			std::cout << "cannot find this employee\n";


		system("pause");
		system("cls");
	}
}




void Admin::modifyEmployee()
{
	if (m_fileEmpty) 
		std::cout << "no employee record\n";
	else
	{
		std::cout << "Please enter the employee Id of employee you want to modifiy.\n";
		
		int id;
		std::cin >> id;

		int result = locateEmployee(id);

		if (result != -1)
		{
			std::string newName{};
			int newPositionId{};


			std::cout << "found: \n";
			m_employeeArray[result]->showInfo();
			
			std::cout << "Please enter new name: \n";
			std::cin >> newName;

			std::cout << "Please select new position of the employee: \n";
			std::cout << "1. Associate\n";
			std::cout << "2. Senior\n";
			std::cout << "3. Manager\n";
			std::cin >> newPositionId;


			// we cannot modify employee in place (even if we created employee via stack)
			// we need to change the employee class type (bc we used polymorphism), so just changing positionID won't help
			delete m_employeeArray[result];

			Employee* employee = nullptr;
			if (newPositionId == 1) employee = new Associate(id, newName, newPositionId);

			else if (newPositionId == 2) employee = new Senior(id, newName, newPositionId);

			else if (newPositionId == 3) employee = new Manager(id, newName, newPositionId);


			m_employeeArray[result] = employee;


			save();

			std::cout << "employee information has been modified.\n";


		}
		else
		{
			std::cout << "cannot find this employee\n";
		}

		system("pause");
		system("cls");
	}
}




void Admin::searchEmployee()
{
	if (m_fileEmpty)
		std::cout << "no employee record\n";
	else
	{
		std::cout << "Please enter the way you want to search: \n";
		std::cout << "1. Search according to employee ID\n";
		std::cout << "2. Search according to employee name\n";

		int select{};
		std::cin >> select;


		if (select == 1)
		{
			int id{};
			std::cout << "Please enter the employee ID of the employee you want to search for: \n";
			std::cin >> id;

			int result = locateEmployee(id);
			if (result != -1)
			{
				std::cout << "Found: \n";
				m_employeeArray[result]->showInfo();

			}
			else
				std::cout << "Cannot find this employee according to the employee ID you entered. \n";
		}

		else if (select == 2)
		{
			std::string name{};
			std::cout << "Please enter the employee name of the employee you want to search for: \n";
			std::cin >> name;


			bool found = false;

			for (int i = 0; i < m_totalEmployeeNumber; i++)
			{
				if (m_employeeArray[i]->m_name == name)
				{
					found = true;
					break;
				}
			}
			if (found == true)
			{
				std::cout << "Found: \n";
				for (int i = 0; i < m_totalEmployeeNumber; i++)
				{
					if (m_employeeArray[i]->m_name == name)
					{
						m_employeeArray[i]->showInfo();
					}
				}
			}
			if (found == false)
				std::cout << "Cannot find this employee according to the name you entered\n";
		}

		else
			std::cout << "Please enter a valid option\n";
	}

	system("pause");
	system("cls");
}


void Admin::sortEmployee()
{
	if (m_fileEmpty)
		std::cout << "no employee record\n";
	else
	{
		std::cout << "Please select the order you want to sort: \n";
		std::cout << "1. Ascending Order \n";
		std::cout << "2. Descending Order \n";

		int select{};
		std::cin >> select;

		for (int i = 0; i < m_totalEmployeeNumber; i++)
		{
			int minOrMax = i;

			for (int j = i + 1; j < m_totalEmployeeNumber; j++)
			{
				if (select == 1)
				{
					if (m_employeeArray[minOrMax]->m_id > m_employeeArray[j]->m_id)
					{
						minOrMax = j;
					}
				}
				else if (select == 2)
				{
					if (m_employeeArray[minOrMax]->m_id < m_employeeArray[j]->m_id)
					{
						minOrMax = j;
					}
				}
			}

			if (i != minOrMax)
			{
				Employee* temp = m_employeeArray[i];
				m_employeeArray[i] = m_employeeArray[minOrMax];
				m_employeeArray[minOrMax] = temp;
			}
		}

		std::cout << "employee list sorted successfully.\n";
		save();
	}

	system("pause");
	system("cls");
}


void Admin::clearAllEmployee()
{
	std::cout << "Are you sure you want to clear all employees record in the system?\n";
	std::cout << "1. No\n";
	std::cout << "2. Yes\n";

	int select{};
	std::cin >> select;

	if (select == 2)
	{
		std::cout << "Please type in \"12345\" to confirm that you want to delete all records.\n";
		int confirm{};
		std::cin >> confirm;
		if (confirm == 12345)
		{
			std::ofstream ofs(FILENAME, std::ios::trunc);
			ofs.close();


			for (int i = 0; i < m_totalEmployeeNumber; i++)
			{
				delete m_employeeArray[i];
			}
			m_totalEmployeeNumber = 0;
			delete[] m_employeeArray;
			m_employeeArray = nullptr;
			m_fileEmpty = true;

			std::cout << "all records have been removed successfully.\n ";
		}
		else
		{
			std::cout << "invalid number\n";
		}
	}

	system("pause");
	system("cls");

}


Admin::~Admin() 
{
	delete[] m_employeeArray;
	m_employeeArray = nullptr;
}


