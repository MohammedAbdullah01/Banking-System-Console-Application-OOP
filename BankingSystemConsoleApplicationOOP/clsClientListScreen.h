#pragma once
#include <iostream>
#include <string>
#include "clsInputRead.h"
#include "clsScreen.h"
#include "clsBankClient.h"
#include <iomanip>

using namespace std;

class clsClientListScreen : protected clsScreen
{
private:
	static void PrintClientRecordLine(clsBankClient& client)
	{
		cout << setw(8) << left << "" << "| " << setw(15) << left << client.accountNumber;
		cout << "| " << setw(20) << left << client.getFullName();
		cout << "| " << setw(12) << left << client.phone;
		cout << "| " << setw(20) << left << client.email;
		cout << "| " << setw(10) << left << client.pinCode;
		cout << "| " << setw(12) << left << client.accountBalance;
	}

public:

	static void ShowClientsList()
	{
		if (!CheckAccessRight(clsUser::pListClients))
		{
			return;
		}
		vector<clsBankClient> vClients = clsBankClient::getClients();

		_DrawScreenHeader("\t\tClinet List Screen", "\t\t(" + to_string(vClients.size()) + ") Client(s)");

		cout << setw(8) << left << "" << "\n\t------------------------------------------------------";
		cout << "-------------------------------------------------\n" << endl;

		cout << setw(8) << left << "" << "| " << left << setw(15) << "Account Number";
		cout << "| " << left << setw(20) << "Client Name";
		cout << "| " << left << setw(12) << "Phone";
		cout << "| " << left << setw(20) << "Email";
		cout << "| " << left << setw(10) << "Pin Code";
		cout << "| " << left << setw(12) << "Balance";

		cout << setw(8) << left << "" << "\n\t------------------------------------------------------";
		cout << "-------------------------------------------------\n" << endl;

		if (vClients.size() == 0)
		{
			cout << "\t\t\t\t\tNo Clients Available In The System";
		}
		else
		{
			for (clsBankClient& client : vClients)
			{
				PrintClientRecordLine(client);
				cout << endl;
			}
		}

		cout << setw(8) << left << "" << "\n\t------------------------------------------------------";
		cout << "-------------------------------------------------\n" << endl;
	}

};

