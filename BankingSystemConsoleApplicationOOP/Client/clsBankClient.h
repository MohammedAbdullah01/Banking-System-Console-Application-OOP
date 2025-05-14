#pragma once
#include <iostream>
#include <string>
#include "Global.h"
#include "clsPerson.h"
#include "clsString.h"
#include "clsInputRead.h"
#include "clsInputValidate.h"
#include <vector>
#include <fstream>



using namespace std;

class clsBankClient : public clsPerson
{
private :
	enum enMode { Empty = 0, Update, AddNew, Delete };

	enMode _Mode;
	string _AccountNumber, _PinCode;
	float _AccountBalance;
	bool _MarkedForDelete = false;
	static const string FILE_NAME;
	static const string FILE_TRANSFER_REGISTER_LOG;
	static const string SEPARATOR;

public:
	struct stTransferRegisterRecord
	{
		string DateTime = "",  UserName = "";
		float AmountTransferred = 0.0f;

		//Sender
		string SenderAccountNumber = "", SenderFullName = "";
		float SenderBalanceAfterTransfer = 0.0f;

		//Consignee
		string ConsigneeAccountNumber = "", ConsigneeFullName = "";
		float ConsigneeBalanceAfterTransfer = 0.0f;
	};

private:
	static clsBankClient _convertFromLineToClient(string line)
	{
		try
		{
			vector<string> data = clsString::SplitEachWordInVector(line, SEPARATOR);

			if (data.size() != 7) {
				throw runtime_error("Invalid client data line.");
			}

			return clsBankClient(enMode::Update, data[0], data[1], data[2],
				data[3], data[4], data[5], stof(data[6]));
		}
		catch (const exception& e)
		{
			cerr << "Error converting line to client: " << e.what() << endl;
			return _getEmptyClientObject();
		}
		
	}

	static string _convertClientToLine(clsBankClient& client)
	{
		return
			client.firstName + SEPARATOR +
			client.lastName + SEPARATOR +
			client.email + SEPARATOR +
			client.phone + SEPARATOR +
			client.accountNumber + SEPARATOR +
			client.pinCode + SEPARATOR +
			to_string(client.accountBalance) + SEPARATOR;
	}

	static clsBankClient _getEmptyClientObject()
	{
		return clsBankClient(enMode::Empty,"" , "", "", "","" ,"" , 0.0f);
	}

	static vector <clsBankClient> _LoadClientsDataFromFile()
	{
		vector <clsBankClient> _vClients;

		fstream myFile;

		myFile.open(FILE_NAME, ios::in);

		if (!myFile.is_open())
		{
			cerr << "Warning: Could not open clients file for reading" << endl;
			return _vClients;
		}

		string line = "";

		while (getline(myFile, line))
		{
			if (!line.empty()) {
				_vClients.push_back(_convertFromLineToClient(line));
			}
		}
		myFile.close();
		return _vClients;
	}

	static void _saveClientsDataToFile(vector <clsBankClient> & vClients)
	{
		fstream myFile;
		myFile.open(FILE_NAME, ios::out);

		if (!myFile.is_open()) {
			throw runtime_error("Failed to open Clients.txt for writing.");
		}

		for (clsBankClient & client : vClients)
		{
			if (!client._MarkedForDelete)
			{
				myFile << _convertClientToLine(client) << '\n';
			}
		}
		myFile.close();
	}

	void _Update()
	{
		vector <clsBankClient> _vClients = _LoadClientsDataFromFile();
		bool found = false;

		for (clsBankClient& client : _vClients)
		{
			if (client.accountNumber == _AccountNumber)
			{
				client = *this;
				found = true;
				break;
			}
		}

		if (!found) {
			throw runtime_error("Client not found for update");
		}

		_saveClientsDataToFile( _vClients);
	}

	void _AddNew()
	{
		fstream myFile;

		myFile.open(FILE_NAME, ios::out | ios::app);

		if (!myFile.is_open())
		{
			throw runtime_error("Could not open clients file for appending");
		}

		myFile << _convertClientToLine(*this) << endl;
		myFile.close();
	}

	static string _convertTransferRegisterRecordToLine(stTransferRegisterRecord& transferRegister)
	{
		return
			transferRegister.DateTime + SEPARATOR +
			transferRegister.SenderAccountNumber + SEPARATOR +
			transferRegister.SenderFullName + SEPARATOR +
			transferRegister.ConsigneeAccountNumber + SEPARATOR +
			transferRegister.ConsigneeFullName + SEPARATOR +
			to_string(transferRegister.AmountTransferred) + SEPARATOR +
			to_string(transferRegister.SenderBalanceAfterTransfer) + SEPARATOR +
			to_string(transferRegister.ConsigneeBalanceAfterTransfer) + SEPARATOR +
			transferRegister.UserName;
	}

	static stTransferRegisterRecord _convertFromLineToRegisterTransferRecord(string& line)
	{
		try
		{
			vector<string> data = clsString::SplitEachWordInVector(line, SEPARATOR);

			if (data.size() != 9) {
				throw runtime_error("Invalid Transfer Register data line.");
			}

			stTransferRegisterRecord TransferRegisterRecord;
			TransferRegisterRecord.DateTime = data[0];
			TransferRegisterRecord.SenderAccountNumber = data[1];
			TransferRegisterRecord.SenderFullName = data[2];
			TransferRegisterRecord.ConsigneeAccountNumber = data[3];
			TransferRegisterRecord.ConsigneeFullName = data[4];
			TransferRegisterRecord.AmountTransferred = stof(data[5]);
			TransferRegisterRecord.SenderBalanceAfterTransfer = stof(data[6]);
			TransferRegisterRecord.ConsigneeBalanceAfterTransfer = stof(data[7]);
			TransferRegisterRecord.UserName = data[8];

			return TransferRegisterRecord;

		}
		catch (const exception& e)
		{
			cerr << "Error converting line to Transfer Register: " << e.what() << endl;
			return stTransferRegisterRecord();
		}

	}

	static vector <stTransferRegisterRecord> _loadTransferRegisterDataFromFile()
	{
		vector <stTransferRegisterRecord> VTransferRegisterRecord;

		fstream myFile;

		myFile.open(FILE_TRANSFER_REGISTER_LOG, ios::in);

		if (!myFile.is_open())
		{
			cerr << "Warning: Could not open Transfer Register Log file for reading" << endl;
			return VTransferRegisterRecord;
		}

		string line = "";

		while (getline(myFile, line))
		{
			if (!line.empty()) {
				VTransferRegisterRecord.push_back(_convertFromLineToRegisterTransferRecord(line));
			}
		}
		myFile.close();
		return VTransferRegisterRecord;
	}

	void _RegisterTransferLog(float amount , clsBankClient& transferTo ,string& userName)
	{
		fstream myFile;
		myFile.open(FILE_TRANSFER_REGISTER_LOG, ios::out | ios::app);

		if (!myFile.is_open())
		{
			cerr << "Warning: Could not open Register Transfer Log file for appending" << endl;
			return;
		}

		stTransferRegisterRecord TransferRegisterRecord;
		TransferRegisterRecord.DateTime = clsDate::GetCurrentTimestamp();
		TransferRegisterRecord.SenderAccountNumber = accountNumber;
		TransferRegisterRecord.ConsigneeAccountNumber = transferTo.accountNumber;
		TransferRegisterRecord.SenderFullName = getFullName();
		TransferRegisterRecord.ConsigneeFullName = transferTo.getFullName();
		TransferRegisterRecord.AmountTransferred = amount;
		TransferRegisterRecord.SenderBalanceAfterTransfer = accountBalance;
		TransferRegisterRecord.ConsigneeBalanceAfterTransfer = transferTo.accountBalance;
		TransferRegisterRecord.UserName = userName;

		myFile << _convertTransferRegisterRecordToLine(TransferRegisterRecord) << "\n";
		myFile.close();

	}

	
public:

	enum class enSaveResults {
		Failed_EmptyObject,
		Succeeded,
		Failed_AccountExists
	};

	clsBankClient(enMode mode , string firstName , string lastName , string email , 
		string phone , string accountNumber , string pinCode , float accountBalance) 

		: clsPerson( firstName,  lastName,  email,  phone)
	{
		_Mode = mode;
		_AccountNumber = accountNumber;
		_PinCode = pinCode;
		_AccountBalance = accountBalance;
	}

	bool IsEmpty()
	{
		return _Mode == enMode::Empty;
	}

	string getAccountNumber()
	{
		return _AccountNumber;
	}

	string getPinCode()
	{
		return _PinCode;
	}

	void setPinCode(string& pinCode)
	{
		if (pinCode.empty()) {
			throw invalid_argument("PIN code cannot be empty");
		}

		_PinCode = pinCode;
	}

	float getAccountBalance()
	{
		return _AccountBalance;
	}

	void setAccountBalance(float accountBalance)
	{
		if (accountBalance < 0) {
			throw invalid_argument("Account balance cannot be negative");
		}

		_AccountBalance = accountBalance;
	}

	bool IsDeleteClient()
	{
		vector <clsBankClient> _vClients = _LoadClientsDataFromFile();
		bool found = false;

		for (clsBankClient& c : _vClients)
		{
			if (c.getAccountNumber() == _AccountNumber)
			{
				c._MarkedForDelete = true;
				found = true;
				break;
			}
		}

		if (!found) {
			return false;
		}
		_saveClientsDataToFile(_vClients);

		*this = _getEmptyClientObject();

		return true;
	}

	static clsBankClient Find(string& accNumber)
	{
		vector<clsBankClient> clients = _LoadClientsDataFromFile();

		for (clsBankClient& client : clients) {
			if (client._AccountNumber == accNumber) {
				return client;
			}
		}
		return _getEmptyClientObject();
	}

	static clsBankClient Find(string& accountNumber, string& pinCode)
	{
		clsBankClient client = Find(accountNumber);
		if (!client.IsEmpty() && pinCode == client._PinCode)
		{
			return client;
		}
		return _getEmptyClientObject();
	}

	static bool IsClientExist(string& accountNumber)
	{
		return !Find(accountNumber).IsEmpty();
	}

	enSaveResults Save()
	{
		try
		{
			switch (_Mode)
			{
			case enMode::Empty:
				return enSaveResults::Failed_EmptyObject;

			case enMode::Update:
				_Update();
				return enSaveResults::Succeeded;

			case enMode::AddNew:
				if (clsBankClient::IsClientExist(_AccountNumber))
				{
					return enSaveResults::Failed_AccountExists;
				}
				_AddNew();
				_Mode = enMode::Update;
				return enSaveResults::Succeeded;

			case enMode::Delete:
				if (IsDeleteClient()) {
					return enSaveResults::Succeeded;
				}
					return enSaveResults::Failed_AccountExists;

			default:
				return enSaveResults::Failed_EmptyObject;
			}
		}
		catch (const exception& e) {
			cerr << "Error saving client: " << e.what() << endl;
			return enSaveResults::Failed_EmptyObject;
		}
	}

	static clsBankClient getAddNewClientObject(string& accountNumber)
	{
		return clsBankClient(enMode::AddNew , "","","","", accountNumber, "",0.0);
	}

	static vector <clsBankClient> getClients()
	{
		return _LoadClientsDataFromFile();
	}

	static float GetTotalBalances()
	{
		float sumBalaces = 0.00;
		for (clsBankClient& client : getClients())
		{
			sumBalaces += client.accountBalance;
		}
		return sumBalaces;
	}

	void Deposit(float amount)
	{
		accountBalance += amount;
		Save();
	}

	bool Withdraw(float amount)
	{
		if (amount > accountBalance)
		{
			return false;
		}

		accountBalance -= amount;
		Save();
		return true;
	}

	bool Transfer(float amount , clsBankClient& transferTo , string userName)
	{
		if (amount > accountBalance)
		{
			return false;
		}
		Withdraw(amount);
		transferTo.Deposit(amount);
		_RegisterTransferLog(amount , transferTo , userName);
		return true;
	}

	static vector<stTransferRegisterRecord> getTransferRegisterList()
	{
		return _loadTransferRegisterDataFromFile();
	}
	
	__declspec(property(get = getAccountNumber)) string accountNumber;

	__declspec(property(get = getPinCode, put = setPinCode)) string pinCode;

	__declspec(property(get = getAccountBalance, put = setAccountBalance))	
		float accountBalance;
};


const string clsBankClient::FILE_NAME = "Clients.txt";
const string clsBankClient::FILE_TRANSFER_REGISTER_LOG = "TransferRegisterLog.txt";
const string clsBankClient::SEPARATOR = "#//#";

