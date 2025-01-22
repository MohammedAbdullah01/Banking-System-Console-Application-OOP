#pragma once
#include "clsInputRead.h"
#include "clsUser.h"
#include "clsScreen.h"


using namespace std;

class clsAddNewUserScreen  : protected clsScreen
{
private:

	static void _ReaduserInfo(clsUser& user)
	{
		string input;
		bool isValid;

		// First Name
		do
		{
			input = clsInputRead::ReadWord("Enter First Name: ");
			isValid = clsInputValidate::isValidName(input);

			if (!isValid) {
				cout << "Invalid first name. Please use only letters and spaces.\n";
			}

		} while (!isValid);
		user.firstName = input;

		// Last Name
		do
		{
			input = clsInputRead::ReadWord("Enter Last Name: ");
			isValid = clsInputValidate::isValidName(input);

			if (!isValid) {
				cout << "Invalid last name. Please use only letters and spaces.\n";
			}

		} while (!isValid);
		user.lastName = input;

		// Email
		do
		{
			input = clsInputRead::ReadWord("Enter Email: ");
			isValid = clsInputValidate::isValidEmail(input);

			if (!isValid) {
				cout << "Invalid email format. Please enter a valid email address.\n";
			}

		} while (!isValid);
		user.email = input;


		// Phone
		do
		{
			input = clsInputRead::ReadWord("Enter Phone: ");
			isValid = clsInputValidate::isValidPhone(input);

			if (!isValid) {
				cout << "Invalid phone number. Please enter a valid phone number.\n";
			}

		} while (!isValid);
		user.phone = input;


		// Password
		do
		{
			input = clsInputRead::ReadWord("Enter Password: ");
			isValid = clsInputValidate::isValidPinCode(input);

			if (!isValid) {
				cout << "Invalid Password. Must be at least 4 digits.\n";
			}

		} while (!isValid);
		user.password = input;


		// Permissions
		user.setPermission(_ReadPermissionsToSet());
	}

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

	static int _ReadPermissionsToSet()
	{
		int permissions = 0;

		char answer = clsInputRead::ReadCharacter("\nDo You Want To Give Full Access? y/n?");

		if (answer == 'Y' || answer == 'y')
		{
			return clsUser::enPermissions::pAll;
		}

		cout << "\nDo You Want To Give Access To :\n";
		answer = clsInputRead::ReadCharacter("\nShow user List ? y/n? ");

		if (answer == 'Y' || answer == 'y')
		{
			permissions += clsUser::enPermissions::pListClients;
		}

		answer = clsInputRead::ReadCharacter("\nAdd New user ? y/n? ");

		if (answer == 'Y' || answer == 'y')
		{
			permissions += clsUser::enPermissions::pAddNewClient;
		}

		answer = clsInputRead::ReadCharacter("\nDelete user ? y/n? ");

		if (answer == 'Y' || answer == 'y')
		{
			permissions += clsUser::enPermissions::pDeleteClient;
		}

		answer = clsInputRead::ReadCharacter("\nUpdate user ? y/n? ");

		if (answer == 'Y' || answer == 'y')
		{
			permissions += clsUser::enPermissions::pUpdateClient;
		}

		answer = clsInputRead::ReadCharacter("\nFins user ? y/n? ");

		if (answer == 'Y' || answer == 'y')
		{
			permissions += clsUser::enPermissions::pFindClient;
		}

		answer = clsInputRead::ReadCharacter("\nTransactions ? y/n? ");

		if (answer == 'Y' || answer == 'y')
		{
			permissions += clsUser::enPermissions::pTransactions;
		}

		answer = clsInputRead::ReadCharacter("\nManage Users ? y/n? ");

		if (answer == 'Y' || answer == 'y')
		{
			permissions += clsUser::enPermissions::pManageUser;
		}

		answer = clsInputRead::ReadCharacter("\nLogin Register ? y/n? ");

		if (answer == 'Y' || answer == 'y')
		{
			permissions += clsUser::enPermissions::pLoginRegister;
		}

		return permissions;
	}


public:
	void static ShowAddNewUserScreen()
	{
		try
		{
			_DrawScreenHeader("\t\tAdd New User Screen");

			string username;

			do {
				username = clsInputRead::ReadWord("Enter UserName: ");

				if (clsUser::IsUserExist(username)) {
					cout << "\nUserName (" << username << ") already exists.\n";
				}

			} while (clsUser::IsUserExist(username));

			clsUser newUser = clsUser::getAddNewUserObject(username);

			_ReaduserInfo(newUser);

			clsUser::enSaveResults saveResults = newUser.Save();

			switch (saveResults)
			{

			case clsUser::enSaveResults::Failed_EmptyObject:
				cout << "\nError: Account was not saved because it's empty\n";
				break;

			case clsUser::enSaveResults::Succeeded:
				cout << "\n-----------------------------\n"
					<< "User Added Successfully"
					<< "\n-----------------------------\n";
				_PrintUser(newUser);
				break;

			case clsUser::enSaveResults::Failed_AccountExists:
				cout << "\nError: Account could not be added - account number already exists\n";
				break;
			}
		}
		catch (exception& e)
		{
			cerr << "\nError adding new user: " << e.what() << endl;
		}
	}
};

