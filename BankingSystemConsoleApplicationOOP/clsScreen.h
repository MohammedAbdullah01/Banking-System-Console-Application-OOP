#pragma once
#include <iostream>
#include "clsUser.h"
#include "Global.h"
#include "clsUtil.h"
#include "clsDate.h"

using namespace std;

class clsScreen
{
protected:

	static void _PrintUserNameAndCurrentDate()
	{
		cout << setw(37) << left << "" << "User: " << CurrentUser.username;
		cout << "\n" << setw(37) << left << "" << "Date: " << clsDate::FormatDate(clsDate::GetSystemDate()) << "\n\n";
	}

	static void _DrawScreenHeader(string title , const string & subTitle = "")
	{
		cout << "\n" << setw(37) << left << "" << "___________________________________________\n\n";
		cout << setw(37) << left << "" << title;
		if (!subTitle.empty())
		{
			cout << "\n" << setw(37) << left << "" << subTitle;
		}
		cout << "\n" << setw(37) << left << "" << "___________________________________________\n\n";

		_PrintUserNameAndCurrentDate();

	}

	static bool CheckAccessRight(clsUser::enPermissions permission)
	{
		if (!CurrentUser.checkAccessPermission(permission))
		{
			system("cls");
			cout << "\n" << setw(37) << left << "" << "___________________________________________\n\n";
			cout << setw(37) << left << "" << "\tAccess Denied! Contact Your Admin";
		
			cout << "\n" << setw(37) << left << "" << "___________________________________________\n\n";
			return false;
		}
		return true;
	}
};

