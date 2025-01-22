#pragma once
#include "clsScreen.h"
#include <iostream>
#include <iomanip>
#include "clsBankClient.h"


using namespace std;
class clsTransferRegisterScreen : protected clsScreen
{
private:
	static void _PrintTransferRegisterRecordLine(clsBankClient::stTransferRegisterRecord TransferRegister)
	{
		cout << setw(8) << left << ""
			<< "| " << setw(25) << left << TransferRegister.DateTime
			<< "| " << setw(20) << left << TransferRegister.SenderAccountNumber
			<< "| " << setw(25) << left << TransferRegister.SenderFullName
			<< "| " << setw(20) << left << TransferRegister.ConsigneeAccountNumber
			<< "| " << setw(25) << left << TransferRegister.ConsigneeFullName
			<< "| " << setw(20) << left << TransferRegister.AmountTransferred
			<< "| " << setw(25) << left << TransferRegister.SenderBalanceAfterTransfer
			<< "| " << setw(25) << left << TransferRegister.ConsigneeBalanceAfterTransfer
			<< "| " << setw(15) << left << TransferRegister.UserName
			<< "|" << endl;
	}

public:

	static void ShowTransferRegisterScreen()
	{
		if (!CheckAccessRight(clsUser::pTransferRegister))
		{
			return;
		}
		vector<clsBankClient::stTransferRegisterRecord> vTransferRegister = clsBankClient::getTransferRegisterList();

		_DrawScreenHeader("\t\tTransfer Register List Screen", "\t\t(" + to_string(vTransferRegister.size()) + ") Record(s)");

		// Header
		cout << setw(8) << left << "" << "+-------------------------+--------------------+-------------------------+--------------------+-------------------------+--------------------+-------------------------+-------------------------+-----------------+" << endl;
		cout << setw(8) << left << ""
			<< "| " << setw(25) << left << "Date/Time"
			<< "| " << setw(20) << left << "Sender Account No."
			<< "| " << setw(25) << left << "Sender Full Name"
			<< "| " << setw(20) << left << "Consignee Acc. No."
			<< "| " << setw(25) << left << "Consignee Full Name"
			<< "| " << setw(20) << left << "Amount"
			<< "| " << setw(25) << left << "Sender Balance After"
			<< "| " << setw(25) << left << "Consignee Balance After"
			<< "| " << setw(15) << left << "Username"
			<< "|" << endl;

		cout << setw(8) << left << "" << "+-------------------------+--------------------+-------------------------+--------------------+-------------------------+--------------------+-------------------------+-------------------------+-----------------+" << endl;

		if (vTransferRegister.size() == 0)
		{
			cout << "\t\t\t\tNo Transfer Register Available In The System" << endl;
		}
		else
		{
			for (clsBankClient::stTransferRegisterRecord& transferRegister : vTransferRegister)
			{
				_PrintTransferRegisterRecordLine(transferRegister);
				cout << endl;
			}
		}

		// Footer
		cout << setw(8) << left << "" << "+-------------------------+--------------------+-------------------------+--------------------+-------------------------+--------------------+-------------------------+-------------------------+-----------------+" << endl;
	}
};

