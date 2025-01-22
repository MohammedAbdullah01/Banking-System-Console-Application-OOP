#pragma once
#include "clsScreen.h"
#include <iostream>
#include <iomanip>
#include "clsUser.h"


using namespace std;

class clsLoginRegisterScreen : protected clsScreen
{
private:
	static void _PrintLoginRegisterRecordLine(clsUser::stLoginRegisterRecord loginRegister)
	{
		cout << setw(8) << left << "" << "| " << setw(25) << left << loginRegister.DateTime;
		cout << "| " << setw(20) << left << loginRegister.Username;
		cout << "| " << setw(10) << left << loginRegister.Password;
		cout << "| " << setw(12) << left << loginRegister.Permissions;
	}

public:

	static void ShowLoginRegisterScreen()
	{
		if (!CheckAccessRight(clsUser::pLoginRegister))
		{
			return;
		}
		vector<clsUser::stLoginRegisterRecord> vLoginRegister = clsUser::getLoginRegisterList();

		_DrawScreenHeader("\t\tLogin Register List Screen", "\t\t(" + to_string(vLoginRegister.size()) + ") Record(s)");

		cout << setw(8) << left << "" << "\n\t------------------------------------------------------";
		cout << "-------------------------------------------------\n" << endl;

		cout << setw(8) << left << "" << "| " << left << setw(25) << "Date/Time";
		cout << "| " << left << setw(20) << "UserName";
		cout << "| " << left << setw(10) << "Password";
		cout << "| " << left << setw(12) << "Permissions";

		cout << setw(8) << left << "" << "\n\t------------------------------------------------------";
		cout << "-------------------------------------------------\n" << endl;

		if (vLoginRegister.size() == 0)
		{
			cout << "\t\t\t\t\tNo Login Register Available In The System";
		}
		else
		{
			for (clsUser::stLoginRegisterRecord& loginRegister : vLoginRegister)
			{
				_PrintLoginRegisterRecordLine(loginRegister);
				cout << endl;
			}
		}

		cout << setw(8) << left << "" << "\n\t------------------------------------------------------";
		cout << "-------------------------------------------------\n" << endl;
	}
};

