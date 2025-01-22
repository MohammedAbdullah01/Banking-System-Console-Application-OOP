#pragma once
#include <iostream>
#include <iomanip>
#include "Global.h"
#include "clsScreen.h"
#include "clsInputRead.h"
#include "clsClientListScreen.h"
#include "clsFindClientScreen.h"
#include "clsManageUsersScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsTransactionMenueScreen.h"
#include "clsLoginRegisterScreen.h"

using namespace std;

class clsMainMenueScreen : protected clsScreen
{
private:
	enum enMainMenueOption
	{
		listClients = 1, AddClient, Delete, Update, FindClient, Transactions, ManageUsers, LoginRegister ,Logout
	};

	static short _ReadChoiseMainMenue()
	{
		cout << "\n" << setw(37) << left << "" << "Choose Between From (1) to (9) ";
		return clsInputRead::ReadNumberInRange((short)1, (short)9, "Invalid Choose From (1) To (9)\n");
	}

	static void _GoBackToMainMenue()
	{
		cout << "\nPress any key to go back to Main Menue...\n";
		system("pause>0");
		showMainMenue();
	}

	static void _ShowAllClientsScreen()
	{
		clsClientListScreen::ShowClientsList();
	}

	static void _PrintClientTotalBalance(clsBankClient& client)
	{
		cout << "| " << setw(15) << left << client.accountNumber;
		cout << "| " << setw(40) << left << client.getFullName();
		cout << "| " << setw(12) << left << client.accountBalance;
	}

	static void _ShowAllClientsTotalBalances()
	{
		vector<clsBankClient> vClients = clsBankClient::getClients();
		cout << "\t\t\t\t\tBalances List (" << vClients.size() << ") Client(s)";



		cout << "\n-------------------------------------------------";
		cout << "-------------------------------------------------\n" << endl;

		cout << "| " << left << setw(15) << "Account Number";
		cout << "| " << left << setw(40) << "Client Name";
		cout << "| " << left << setw(12) << "Balance";
		cout << "\n-------------------------------------------------";
		cout << "-------------------------------------------------\n" << endl;

		float totalBalances = clsBankClient::GetTotalBalances();
		if (vClients.size() == 0)
		{
			cout << "\t\t\t\t\tNo Clients Available In The System";
		}
		else
		{
			for (clsBankClient& client : vClients)
			{
				_PrintClientTotalBalance(client);
				cout << endl;
			}
		}
		cout << "\n-------------------------------------------------";
		cout << "-------------------------------------------------\n" << endl;

		cout << "\t\t\t\t\tTotal Balance	: $" << fixed << setprecision(2) << totalBalances << "\n\n";
		cout << "\t\t\t\t\t( " << clsUtil::numberToText(totalBalances) << " )\n\n";

	}

	static void _ShowAddNewClientScreen()
	{
		clsAddNewClientScreen::ShowAddNewClientScreen();
	}

	static void _ShowDeleteClientScreen()
	{
		clsDeleteClientScreen::ShowDeleteClientScreen();
	}

	static void _ShowUpdateClientScreen()
	{
		clsUpdateClientScreen::ShowUpdateClientScreen();
	}

	static void _ShowFindClientScreen()
	{
		clsFindClientScreen::ShowFindClientScreen();
	}

	static void _ShowTransactionsMenue()
	{ 
		clsTransactionMenueScreen::ShowTransactionsMenue();
	}

	static void _ShowManageUsersMenue()
	{ }

	static void _ShowLoginRegisterScreen()
	{
		clsLoginRegisterScreen::ShowLoginRegisterScreen();
	}

	static void _Logout()
	{ 
		string EmptyUsername = "", EmptyPassword = "";
		CurrentUser = clsUser::Find(EmptyUsername, EmptyPassword);
	}

	static void  MainMenue(enMainMenueOption chooseNumber)
	{

		switch (chooseNumber)
		{
		case enMainMenueOption::listClients:
			system("cls");
			_ShowAllClientsScreen();
			_GoBackToMainMenue();
			break;
		case enMainMenueOption::AddClient:
			system("cls");
			_ShowAddNewClientScreen();
			_GoBackToMainMenue();
			break;

		case enMainMenueOption::Delete:
			system("cls");
			_ShowDeleteClientScreen();
			_GoBackToMainMenue();
			break;

		case enMainMenueOption::Update:
			system("cls");
			_ShowUpdateClientScreen();
			_GoBackToMainMenue();
			break;
		case enMainMenueOption::FindClient:
			system("cls");
			_ShowFindClientScreen();
			_GoBackToMainMenue();
			break;
		case enMainMenueOption::Transactions:
			_ShowTransactionsMenue();
			_GoBackToMainMenue();
			break;
		case enMainMenueOption::ManageUsers:
			system("cls");
			clsManageUsersScreen::ShowManageUsersMenue();
			_GoBackToMainMenue();
			break;

		case enMainMenueOption::LoginRegister:
			system("cls");
			_ShowLoginRegisterScreen();
			_GoBackToMainMenue();
			break;

		case enMainMenueOption::Logout:
			system("cls");
			_Logout();
			break;
		}
	}

public:

	static void showMainMenue()
	{
		system("cls");

		_DrawScreenHeader("\t\t\tMain Screen");

		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t\t\tMain Menue\n";
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t[1] Show Clients List.\n";
		cout << setw(37) << left << "" << "\t[2] Add New Client.\n";
		cout << setw(37) << left << "" << "\t[3] Delete Client.\n";
		cout << setw(37) << left << "" << "\t[4] Update Client Info.\n";
		cout << setw(37) << left << "" << "\t[5] Find Client.\n";
		cout << setw(37) << left << "" << "\t[6] Transactions.\n";
		cout << setw(37) << left << "" << "\t[7] Manage Users.\n";
		cout << setw(37) << left << "" << "\t[8] Login Register.\n";
		cout << setw(37) << left << "" << "\t[9] Logout.\n";
		cout << setw(37) << left << "" << "===========================================\n";
		MainMenue((enMainMenueOption)_ReadChoiseMainMenue());
	}
};

