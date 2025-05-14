#pragma once
#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include "clsScreen.h"
#include "clsInputRead.h"
#include "clsDepositScreen.h"
#include "clsListUsersScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"

using namespace std;

class clsManageUsersScreen : protected clsScreen
{
private:
	enum enManageUsersMenue
	{
		ListUser = 1, AddNewUser, DeleteUser, UpdateUser, FindUser, MainMenue
	};

	static short _ReadChoiseManageUsersMenue()
	{
		cout << "\n" << setw(37) << left << "" << "Choose Between From (1) to (6) ";
		return clsInputRead::ReadNumberInRange((short)1, (short)6, "Invalid Choose From (1) To (6)\n");
	}

	static void _GoBackToManageUsersMenue()
	{
		cout << "\nPress any key to go back to Manage Users Menue...\n";
		system("pause>0");
		ShowManageUsersMenue();
	}

	static void _ShowListUsersScreen()
	{
		clsListUsersScreen::ShowListUsersScreen() ;
	}

	static void _ShowAddNewUserScreen()
	{
		clsAddNewUserScreen::ShowAddNewUserScreen();
	}

	static void _ShowDeleteUserScreen()
	{
		clsDeleteUserScreen::ShowDeleteUserScreen();
	}

	static void _ShowUpdateUserScreen()
	{
		clsUpdateUserScreen::ShowUpdateUserScreen();
	}

	static void _ShowFindUserScreen()
	{
			clsFindUserScreen::ShowFindUserScreen();
	}

	void GoBackToManageUsersMenue()
	{
		cout << "\nPress any key to go back to Manage Users Menue...\n";
		system("pause>0");
		ShowManageUsersMenue();
	}

	static void ManageUsersMenue(enManageUsersMenue chooseNumber)
	{

		switch (chooseNumber)
		{
		case ListUser:
			system("cls");
			_ShowListUsersScreen();
			_GoBackToManageUsersMenue();
			break;
		case AddNewUser:
			system("cls");
			_ShowAddNewUserScreen();
			_GoBackToManageUsersMenue();
			break;
		case DeleteUser:
			system("cls");
			_ShowDeleteUserScreen();
			_GoBackToManageUsersMenue();
			break;
		case UpdateUser:
			system("cls");
			_ShowUpdateUserScreen();
			_GoBackToManageUsersMenue();
			break;
		case FindUser:
			system("cls");
			_ShowFindUserScreen();
			_GoBackToManageUsersMenue();
			break;
		case MainMenue:
			break;
		}
	}

public:
	static void ShowManageUsersMenue()
	{
		if (!CheckAccessRight(clsUser::pManageUser))
		{
			return;
		}

		system("cls");

		_DrawScreenHeader("\t\tManage Users Menue Screen");

		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t\tManage Users Menue\n";
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t[1] List Users.\n";
		cout << setw(37) << left << "" << "\t[2] Add New User.\n";
		cout << setw(37) << left << "" << "\t[3] Delete User.\n";
		cout << setw(37) << left << "" << "\t[4] Update User.\n";
		cout << setw(37) << left << "" << "\t[5] Find User.\n";
		cout << setw(37) << left << "" << "\t[6] Return to Main Menu.\n";
		cout << setw(37) << left << "" << "===========================================\n";

		ManageUsersMenue((enManageUsersMenue)_ReadChoiseManageUsersMenue());
	}
};

