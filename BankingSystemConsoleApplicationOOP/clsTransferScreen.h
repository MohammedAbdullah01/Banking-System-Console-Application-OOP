#pragma once
#include "clsScreen.h"
#include "clsUser.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"


class clsTransferScreen : protected clsScreen
{
private:

	static void _PrintClient(clsBankClient& client)
	{
		cout << "\nClient Details:\n"
			<< "-------------------\n"
			<< "- FullName	: " << client.getFullName() << "\n"
			<< "- Acc. Number	: " << client.accountNumber << "\n"
			<< "- Balance	: $" << fixed << setprecision(2) << client.accountBalance << "\n\n";
	}

	static string _ReadAccountNumber(string msg)
	{
		string accountNumber = clsInputRead::ReadWord("Please Enter " + msg);
		while (!clsBankClient::IsClientExist(accountNumber))
		{
			accountNumber = clsInputRead::ReadWord("Please Enter " + msg);
		}
		return accountNumber;
	}

	static float _ReadTransferAmount(clsBankClient sourceClient)
	{
		cout << "\nPlease Enter Transfer Amount ? ";
		float transferAmount = clsInputValidate::ReadNumberWithValidateAndPositiveNumber<float>();

		while (transferAmount > sourceClient.accountBalance)
		{
			cout << "\nAmount Exceeds The Available Balance, Enter Another Amount ? ";
			transferAmount = clsInputValidate::ReadNumberWithValidateAndPositiveNumber<float>();
		}
		return transferAmount;
	}

public:

	static void ShowTransferScreen()
	{
		_DrawScreenHeader("\t\tTransfer Screen");

		string accNumberTransferForm = _ReadAccountNumber("Account Number To Transfer From ? ");
		clsBankClient clientTransferForm = clsBankClient::Find(accNumberTransferForm);
		_PrintClient(clientTransferForm);

		string accNumberTransferTo = _ReadAccountNumber("Account Number To Transfer To ? ");
		clsBankClient clientTransferTo = clsBankClient::Find(accNumberTransferTo);
		_PrintClient(clientTransferTo);

		float transferAmount = _ReadTransferAmount(clientTransferForm);

		char answer = clsInputRead::ReadCharacter("\nAre Your Shure You Want To Perform This Transaction ? y/n? ");
		if (tolower(answer) != 'y')
		{
			cout << "\nThe Operation Transfer Funds Has Been Cancelled\n";
			return;
		}

		if (clientTransferForm.Transfer(transferAmount, clientTransferTo , CurrentUser.username))
		{
			cout << "\n\nTransfer Done Successfully\n";
		}
		else
		{
			cout << "\nTransfer Funds Faild\n";
		}

		_PrintClient(clientTransferForm);
		_PrintClient(clientTransferTo);

	}
};

