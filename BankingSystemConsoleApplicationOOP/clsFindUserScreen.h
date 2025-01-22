#pragma once
#include "clsScreen.h"
#include "clsUser.h"

using namespace std;

class clsFindUserScreen  : protected clsScreen
{

private:

	static void _PrintUser(clsUser& user)
	{
		cout << "\nuser Details:\n"
			<< "-------------------\n"
			<< "- UserName	: " << user.username << "\n"
			<< "- FullName	: " << user.getFullName() << "\n"
			<< "- Email		: " << user.email << "\n"
			<< "- Phone		: " << user.phone << "\n"
			<< "- Password	: " << user.password << "\n"
			<< "- Permissions	: " << user.getPermissions() << "\n";
	}


public:
	void static ShowFindUserScreen()
	{
		try
		{
			_DrawScreenHeader("\t\tFind User Screen");

			string username = clsInputRead::ReadWord("Enter User UserName? ");

			while (!clsUser::IsUserExist(username))
			{
				username = clsInputRead::ReadWord("Please enter another UserName: ");
			}

			clsUser user = clsUser::Find(username);

			cout << "\nCurrent User Information:\n";
			_PrintUser(user);
		}
		catch (const exception& e)
		{
			cerr << "\nError Find User: " << e.what() << endl;
		}
	}
};

