#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include "clsScreen.h"
#include "clsInputRead.h"
#include "clsDepositScreen.h"
#include "clsTransferScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalanccesScreen.h"
#include "clsTransferRegisterScreen.h"

using namespace std;

class clsTransactionMenueScreen :protected clsScreen
{

private:
	enum enTransactionMenueOption
	{
		Deposit = 1, Withdraw, Transfer, TransferLog, TotalBalancces, MainMenue
	};

	static short _ReadChoiseTransactionMenue()
	{
		cout << "\n" << setw(37) << left << "" << "Choose Between From (1) to (6) ";
		return clsInputRead::ReadNumberInRange((short)1, (short)6, "Invalid Choose From (1) To (6)\n");
	}

	static void _ShowDepositScreen()
	{
		clsDepositScreen::ShowDepositScreen();
	}

	static void _ShowWithdrawScreen()
	{
		clsWithdrawScreen::ShowWithdrawScreen();
	}

	static void _ShowTotalBalanccesScreen()
	{
		clsTotalBalanccesScreen::ShowTotalBalanccesScreen();
	}

	static void _ShowTransferScreen()
	{
		clsTransferScreen::ShowTransferScreen();
	}

	static void _ShowTransferRegisterScreen()
	{
		clsTransferRegisterScreen::ShowTransferRegisterScreen();
	}

	static void _GoBackToTransactionMenue()
	{
		cout << "\nPress any key to go back to Transaction Menue...\n";
		system("pause>0");
		ShowTransactionsMenue();
	}

	static void _TransactionsMenue(enTransactionMenueOption chooseNumber)
	{

		switch (chooseNumber)
		{
		case Deposit:
			system("cls");
			_ShowDepositScreen();
			_GoBackToTransactionMenue();
			break;
		case Withdraw:
			system("cls");
			_ShowWithdrawScreen();
			_GoBackToTransactionMenue();
			break;

		case TotalBalancces:
			system("cls");
			_ShowTotalBalanccesScreen();
			_GoBackToTransactionMenue();
			break;

		case Transfer:
			system("cls");
			_ShowTransferScreen();
			_GoBackToTransactionMenue();
			break;

		case TransferLog:
			system("cls");
			_ShowTransferRegisterScreen();
			_GoBackToTransactionMenue();
			break;

		case MainMenue:
			break;
		}
	}

public:
	static void ShowTransactionsMenue()
	{
		if (!CheckAccessRight(clsUser::pTransactions))
		{
			return;
		}

		system("cls");

		_DrawScreenHeader("\t\tTransactions Screen");

		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t\tTransactions Menue\n";
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t[1] Deposit Funds.\n";
		cout << setw(37) << left << "" << "\t[2] Withdraw Funds.\n";
		cout << setw(37) << left << "" << "\t[3] Transfer Funds.\n";
		cout << setw(37) << left << "" << "\t[4] Transfer Log.\n";
		cout << setw(37) << left << "" << "\t[5] View Total Balances.\n";
		cout << setw(37) << left << "" << "\t[6] Return to Main Menu.\n";
		cout << setw(37) << left << "" << "===========================================\n";

		_TransactionsMenue((enTransactionMenueOption)_ReadChoiseTransactionMenue());
	}
};

