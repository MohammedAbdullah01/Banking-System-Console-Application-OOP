#pragma once
#include <iostream>
#include <string>
#include "clsInputRead.h"
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"


using namespace std;

class clsAddNewClientScreen : protected clsScreen
{
private:

	static void _ReadClientInfo(clsBankClient& client)
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
		client.firstName = input;

		// Last Name
		do
		{
			input = clsInputRead::ReadWord("Enter Last Name: ");
			isValid = clsInputValidate::isValidName(input);

			if (!isValid) {
				cout << "Invalid last name. Please use only letters and spaces.\n";
			}

		} while (!isValid);
		client.lastName = input;

		// Email
		do
		{
			input = clsInputRead::ReadWord("Enter Email: ");
			isValid = clsInputValidate::isValidEmail(input);

			if (!isValid) {
				cout << "Invalid email format. Please enter a valid email address.\n";
			}

		} while (!isValid);
		client.email = input;


		// Phone
		do
		{
			input = clsInputRead::ReadWord("Enter Phone: ");
			isValid = clsInputValidate::isValidPhone(input);

			if (!isValid) {
				cout << "Invalid phone number. Please enter a valid phone number.\n";
			}

		} while (!isValid);
		client.phone = input;


		// PIN CODE
		do
		{
			input = clsInputRead::ReadWord("Enter PIN Code: ");
			isValid = clsInputValidate::isValidPinCode(input);

			if (!isValid) {
				cout << "Invalid PIN code. Must be at least 4 digits.\n";
			}

		} while (!isValid);
		client.setPinCode(input);


		// Account Balance
		float balance = clsInputValidate::ReadNumberWithValidateAndPositiveNumber<float>();
		client.setAccountBalance(balance);
	}

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

	static void ShowAddNewClientScreen()
	{
		if (!CheckAccessRight(clsUser::pAddNewClient))
		{
			return;
		}

		try
		{
			_DrawScreenHeader("\t\tAdd Newe Client Screen");

			string accountNumber;

			do {
				accountNumber = clsInputRead::ReadWord("Enter Account Number: ");

				if (clsBankClient::IsClientExist(accountNumber)) {
					cout << "\nAccount Number (" << accountNumber << ") already exists.\n";
				}

			} while (clsBankClient::IsClientExist(accountNumber));

			clsBankClient newClient = clsBankClient::getAddNewClientObject(accountNumber);

			_ReadClientInfo(newClient);

			clsBankClient::enSaveResults saveResults = newClient.Save();

			switch (saveResults)
			{

			case clsBankClient::enSaveResults::Failed_EmptyObject:
				cout << "\nError: Account was not saved because it's empty\n";
				break;

			case clsBankClient::enSaveResults::Succeeded:
				cout << "\n-----------------------------\n"
					<< "Account Added Successfully"
					<< "\n-----------------------------\n";
				_PrintClient(newClient);
				break;

			case clsBankClient::enSaveResults::Failed_AccountExists:
				cout << "\nError: Account could not be added - account number already exists\n";
				break;
			}
		}
		catch (exception& e)
		{
			cerr << "\nError adding new client: " << e.what() << endl;
		}

	}
};

