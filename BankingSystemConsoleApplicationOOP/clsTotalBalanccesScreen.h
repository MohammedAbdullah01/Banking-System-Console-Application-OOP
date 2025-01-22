#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "clsScreen.h"
#include "clsInputRead.h"
#include "clsBankClient.h"

using namespace std;

class clsTotalBalanccesScreen :protected clsScreen
{
private:
	static void PrintClientRecordTotalBalance(clsBankClient client)
	{
		cout << setw(25) << left << "" << "| " << setw(15) << left << client.accountNumber;
		cout << "| " << setw(40) << left << client.getFullName();
		cout << "| " << setw(12) << left << client.accountBalance;
	}
	
public:
	static void ShowTotalBalanccesScreen()
	{
		vector<clsBankClient> vClients = clsBankClient::getClients();
		_DrawScreenHeader("\t\tBalances List Screen\n" , "\t\t   (" + to_string(vClients.size()) + ") Client(s)");

		cout << setw(25) << left << "" << "----------------------------------------------------------------------\n\n";

		cout << setw(25) << left << ""  << "| " << left << setw(15) << "Account Number";
		cout << "| " << left << setw(40) << "Client Name";
		cout << "| " << left << setw(12) << "Balance";
		cout << "\n\n" << setw(25) << left << "" << "----------------------------------------------------------------------\n";

		if (vClients.size() == 0)
		{
			cout << "\t\t\t\tNo Clients Available In The System\n";
		}
		else
		{
			for (clsBankClient& client : vClients)
			{
				PrintClientRecordTotalBalance(client);
				cout << endl;
			}
			cout << setw(25) << left << "" << "----------------------------------------------------------------------\n";

			cout << setw(25) << left << "" << "Total Balances : $" << fixed << setprecision(2) << clsBankClient::GetTotalBalances() << "\n\n";
		}
	}
};

