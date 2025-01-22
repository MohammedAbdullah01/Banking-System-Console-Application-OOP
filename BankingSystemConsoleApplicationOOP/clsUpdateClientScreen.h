#pragma once
#include <iostream>
#include <string>
#include "clsInputRead.h"
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

using namespace std;

class clsUpdateClientScreen : protected clsScreen
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
	static void ShowUpdateClientScreen()
	{
		if (!CheckAccessRight(clsUser::pUpdateClient))
		{
			return;
		}

		try
		{
			_DrawScreenHeader("\t\tUpdate Client Screen");

			string accountNumber = clsInputRead::ReadWord("Enter Client Account Number ? ");

			while (!clsBankClient::IsClientExist(accountNumber))
			{
				accountNumber = clsInputRead::ReadWord("Please enter another Account Number: ");
			}

			clsBankClient client = clsBankClient::Find(accountNumber);

			cout << "\nCurrent Client Information:\n";
			_PrintClient(client);

			cout << "\nUpdate Client Information:\n"
				<< "_____________________________\n";

			_ReadClientInfo(client);

			clsBankClient::enSaveResults saveResult = client.Save();

			switch (saveResult)
			{

			case clsBankClient::enSaveResults::Failed_EmptyObject:
				cout << "\nError: Account was not saved because it's empty\n";
				break;

			case clsBankClient::enSaveResults::Succeeded:
				cout << "\n-----------------------------\n"
					<< "Account Updated Successfully"
					<< "\n----------------------------- \n";
				_PrintClient(client);
				break;

			case clsBankClient::enSaveResults::Failed_AccountExists:
				cout << "\nError: Update failed - account number already exists\n";
				break;
			}
		}
		catch (const exception& e)
		{
			cerr << "\nError updating client: " << e.what() << endl;
		}
	}
};

