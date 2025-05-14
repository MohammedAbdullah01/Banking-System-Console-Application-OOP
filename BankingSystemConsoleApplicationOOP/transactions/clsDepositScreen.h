#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputRead.h"
#include "clsInputValidate.h"
using namespace std;

class clsDepositScreen : protected clsScreen
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

	static void ShowDepositScreen()
	{
		_DrawScreenHeader("\t\tDeposit Screen");
		string accountNumber = clsInputRead::ReadWord("Enter Client Account Number ? ");

		while (!clsBankClient::IsClientExist(accountNumber))
		{
			accountNumber = clsInputRead::ReadWord("Please enter another Account Number: ");
		}

		clsBankClient client = clsBankClient::Find(accountNumber);

		_PrintClient(client);

		cout << "\nPlease Enter Deposit Amount?\n";
		float amount = clsInputValidate::ReadNumberWithValidateAndPositiveNumber<float>();

		char answer = clsInputRead::ReadCharacter("\nAre Your Shure You Want To Perform This Transaction ? y/n? ");

		if (tolower(answer) != 'y')
		{
			cout << "\nThe operation has been cancelled\n";
			return;
		}

		float amountBeforeDeposit = client.accountBalance;
		client.Deposit(amount);
		cout << "\nAmount Deposited Successfully\n";
		cout << "\nAmount Before Deposit   : $" << fixed << setprecision(2) << amountBeforeDeposit << "\n";
		cout << "\nAmount Deposit		: $" << fixed << setprecision(2) << amount << "\n";
		cout << "\nCurrent Amount		: $" << fixed << setprecision(2) << client.accountBalance << "\n";

	}
};

