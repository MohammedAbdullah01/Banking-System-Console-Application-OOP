#pragma once
#include <iostream>
#include <string>
#include "clsScreen.h"
#include "clsBankClient.h"

using namespace std;
class clsFindClientScreen : protected clsScreen
{
private:
	static void _PrintClient(clsBankClient& client)
	{
		cout << "\nClient Details:\n"
			<< "-------------------\n"
			<< "- FirstName	: " << client.firstName << "\n"
			<< "- LastName	: " << client.lastName << "\n"
			<< "- FullName	: " << client.getFullName() << "\n"
			<< "- Email		: " << client.email << "\n"
			<< "- Phone		: " << client.phone << "\n"
			<< "- Acc. Number	: " << client.accountNumber << "\n"
			<< "- Password	: " << client.pinCode << "\n"
			<< "- Balance	: $" << fixed << setprecision(2) << client.accountBalance << "\n\n";
	}

public:
	static void ShowFindClientScreen()
	{
		if (!CheckAccessRight(clsUser::pFindClient))
		{
			return;
		}

		try
		{
			_DrawScreenHeader("\t\tFind Client Screen");

			string accountNumber = clsInputRead::ReadWord("Enter Client Account Number ? ");

			while (!clsBankClient::IsClientExist(accountNumber))
			{
				accountNumber = clsInputRead::ReadWord("Please enter another Account Number: ");
			}

			clsBankClient client = clsBankClient::Find(accountNumber);

			cout << "\nCurrent Client Information:\n";
			_PrintClient(client);
		}
		catch (const exception& e)
		{
			cerr << "\nError Find Client: " << e.what() << endl;
		}
	}
};

