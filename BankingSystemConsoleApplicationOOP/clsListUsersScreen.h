#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include "clsUser.h"
#include "clsScreen.h"

using namespace std;

class clsListUsersScreen : protected clsScreen
{
private:
	static void _PrintUserRecord(clsUser user)
	{
		cout << setw(8) << left << "" << "| " << left << setw(12) << user.getUserName();
		cout << "| " << setw(25) << left << user.getFullName();
		cout << "| " << setw(12) << left << user.getPhone();
		cout << "| " << setw(20) << left << user.getEmail();
		cout << "| " << setw(10) << left << user.getPassword();
		cout << "| " << setw(12) << left << user.getPermissions();
	}


public:
	static void  ShowListUsersScreen()
	{
		vector<clsUser> vUsers = clsUser::getUsers();

		_DrawScreenHeader("\t\tUser List Screen", "\t\t(" + to_string(vUsers.size()) + ") User(s)");

		cout << setw(8) << left << "" << "\n\t------------------------------------------------------";
		cout << "-------------------------------------------------\n" << endl;

		cout << setw(8) << left << "" << "| " << left << setw(12) << "UserName";
		cout << "| " << left << setw(25) << "Full Name";
		cout << "| " << left << setw(12) << "Phone";
		cout << "| " << left << setw(20) << "Email";
		cout << "| " << left << setw(10) << "Password";
		cout << "| " << left << setw(12) << "Permission";
		cout << setw(8) << left << "" << "\n\t------------------------------------------------------";
		cout << "-------------------------------------------------\n" << endl;

		if (vUsers.size() == 0)
		{
			cout << "\t\t\t\t\tNo Users Available In The System";
		}
		else
		{
			for (clsUser& users : vUsers)
			{
				_PrintUserRecord(users);
				cout << endl;
			}
		}
		cout << setw(8) << left << "" << "\n\t------------------------------------------------------";
		cout << "-------------------------------------------------\n" << endl;
	}
};

