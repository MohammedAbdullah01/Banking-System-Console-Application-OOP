#pragma once
#include <iostream>
#include <string>
#include "clsInputRead.h"
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsAddNewClientScreen.h"

using namespace std;

class clsDeleteClientScreen : protected clsScreen
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

	static void ShowDeleteClientScreen()
	{
		if (!CheckAccessRight(clsUser::pDeleteClient))
		{
			return;
		}

		try
		{
			_DrawScreenHeader("\t\tDelete Client Screen");

			string accountNumber = clsInputRead::ReadWord("Enter Client Account Number ? ");

			while (!clsBankClient::IsClientExist(accountNumber))
			{
				accountNumber = clsInputRead::ReadWord("Please enter another Account Number: ");
			}

			clsBankClient client = clsBankClient::Find(accountNumber);

			cout << "\nClient to be deleted:\n";
			_PrintClient(client);

			char answer;
			do
			{
				answer = tolower(clsInputRead::ReadCharacter("\nAre you sure you want to delete this client? (y/n): "));

			} while (answer != 'y' && answer != 'n');

			if (answer == 'y')
			{
				clsBankClient::enSaveResults saveResult = client.Save();

				switch (saveResult)
				{

				case clsBankClient::enSaveResults::Failed_EmptyObject:
					cout << "\nError: Deletion failed - client information is empty\n";
					break;

				case clsBankClient::enSaveResults::Succeeded:
					if (client.IsDeleteClient())
					{
						cout << "\n-----------------------------\n"
							<< "Client Deleted Successfully"
							<< "\n-----------------------------\n";
						_PrintClient(client);
						break;
					}

				case clsBankClient::enSaveResults::Failed_AccountExists:
					cout << "\nError: Deletion failed - client not found\n";
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
			cerr << "\nError deleting client: " << e.what() << endl;
		}

	}
};

