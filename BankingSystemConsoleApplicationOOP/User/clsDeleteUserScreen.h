#pragma once
#include "clsScreen.h"
#include "clsUser.h"

using namespace std;

class clsDeleteUserScreen  : protected clsScreen
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
	void static ShowDeleteUserScreen()
	{
		try
		{
			_DrawScreenHeader("\t\tDelete User Screen");

			string username = clsInputRead::ReadWord("Enter UserName ? ");

			while (!clsUser::IsUserExist(username))
			{
				username = clsInputRead::ReadWord("Please enter another Account Number: ");
			}

			clsUser user = clsUser::Find(username);

			cout << "\nUser To Be Deleted:\n";
			_PrintUser(user);

			char answer;
			do
			{
				answer = tolower(clsInputRead::ReadCharacter("\nAre you sure you want to delete this user? (y/n): "));

			} while (answer != 'y' && answer != 'n');

			if (answer == 'y')
			{
				clsUser::enSaveResults saveResult = user.Save();

				switch (saveResult)
				{

				case clsUser::enSaveResults::Failed_EmptyObject:
					cout << "\nError: Deletion failed - user information is empty\n";
					break;

				case clsUser::enSaveResults::Succeeded:
					if (user.IsDeleteUser())
					{
						cout << "\n-----------------------------\n"
							<< "\tUser Deleted Successfully"
							<< "\n-----------------------------\n";
						_PrintUser(user);
						break;
					}

				case clsUser::enSaveResults::Failed_AccountExists:
					cout << "\nError: Deletion failed - user not found\n";
					break;
				}
			}
			else
			{
				cout << "\nDeletion cancelled.\n";
			}
		}
		catch (exception& e)
		{
			cerr << "\nError deleting user: " << e.what() << endl;
		}
	}
};

