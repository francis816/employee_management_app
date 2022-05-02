#include <iostream>
#include "admin.h"
//#include "employee.h"
//#include "associate.h"
//#include "senior.h"
//#include "manager.h"

int main()
{
	//Employee* employee = new Associate(1, "francis", 1);

	//
	//employee->showInfo();
	//
	//std::cout << "\n";

	//Employee* employee2 = new Senior(2, "gigi", 2);
	//employee2->showInfo();
	//std::cout << "\n";

	//Employee* employee3 = new Manager(3, "fifi", 3);
	//employee3->showInfo();
	//std::cout << "\n";


	Admin admin;

	int choice = 0;
	
	while (true)
	{
		admin.showMenu();
		std::cout << "Please select your function: \n";
		std::cin >> choice;

		switch (choice)
		{
		case 0: 
			admin.exitSystem();
			break;

		case 1:
			admin.addEmployee();
			break;

		case 2:
			admin.showEmployee();
			break;

		case 3:
			admin.deleteEmployee();
			break;

		case 4:
			admin.modifyEmployee();
			break;

		case 5:
			admin.searchEmployee();
			break;

		case 6:
			admin.sortEmployee();
			break;

		case 7:
			admin.clearAllEmployee();
			break;

		default:
			system("cls");
			break; 
		}
	}




	system("pause");
}