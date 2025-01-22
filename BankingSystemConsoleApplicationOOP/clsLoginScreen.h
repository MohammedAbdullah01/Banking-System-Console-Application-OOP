#pragma once
#include <iostream>
#include "clsUser.h"
#include "clsUtil.h"
#include "clsDate.h"
#include "clsScreen.h"
#include "clsInputRead.h"
#include "clsMainMenueScreen.h"


using namespace std;

class clsLoginScreen : protected clsScreen
{
private:
	
	static bool _Login()
	{
		string username = "", password = "";
		bool isInvalid = false;
		short trials = 3;

		do
		{
			if (isInvalid)
			{
				cout << "\nInvalid Username OR Password\n";
				trials--;
				cout << "You Have " << trials << " To Login\n\n";

				if (trials == 0)
				{
					cout << "Your Are Locked After 3 Faild Trails\n";
					return false;
				}
			}

			username = clsInputRead::ReadWord("Enter Username ? ");

			password = clsInputRead::ReadWord("Enter Password ? ");

			CurrentUser = clsUser::Find(username , password);

			isInvalid = CurrentUser.IsEmpty();

		} while (isInvalid);

		CurrentUser.RegisterLogIn();
		clsMainMenueScreen::showMainMenue();
		return true;
	}

public:

	static bool ShowLoginScreen()
	{
		system("cls");
		_DrawScreenHeader("\t\t    Login Screen");
		return _Login();
	}
};

