#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "clsPerson.h"
#include "clsString.h"
#include "clsDate.h"
#include "clsUtil.h"

using namespace std;

class clsUser : public clsPerson
{
private:
	enum enMode 
	{
		EmptyMode = 0, UpdateMode, AddNewMode
	};

	enMode _Mode;
	string _UserName;
	string _Password;
	int _Permissions;
	bool _MarkForDelete = false;

	static const string FILE_NAME; 
	static const string FILE_LOG_IN_REGISTER;
	static const string SEPARATOR;
	
	static clsUser _convertFromLineToUser(string line)
	{
		try
		{
			vector<string> data = clsString::SplitEachWordInVector(line, SEPARATOR);

			if (data.size() != 7) {
				throw runtime_error("Invalid user data line.");
			}

			return clsUser(enMode::UpdateMode, data[0], data[1], data[2],data[3], data[4], clsUtil::DecryptionText(data[5]), stoi(data[6]));
		}
		catch (const exception& e)
		{
			cerr << "Error converting line to client: " << e.what() << endl;
			return _getEmptyUserObject();
		}

	}
	 
	static string _convertUserToLine(clsUser& user)
	{
		return
			user.firstName + SEPARATOR +
			user.lastName + SEPARATOR +
			user.email + SEPARATOR +
			user.phone + SEPARATOR +
			user._UserName + SEPARATOR +
			clsUtil::EncryptionText(user._Password) + SEPARATOR +
			to_string(user._Permissions);
	}

	static clsUser _getEmptyUserObject()
	{
		return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static vector <clsUser> _LoadUsersDataFromFile()
	{
		vector <clsUser> _vUsers;

		fstream myFile;

		myFile.open(FILE_NAME, ios::in);

		if (!myFile.is_open())
		{
			cerr << "Warning: Could not open Users file for reading" << endl;
			return _vUsers;
		}

		string line = "";

		while (getline(myFile, line))
		{
			if (!line.empty()) {
				_vUsers.push_back(_convertFromLineToUser(line));
			}
		}
		myFile.close();
		return _vUsers;
	}

	static void _saveUsersDataToFile(vector <clsUser>& vClients)
	{
		fstream myFile;
		myFile.open(FILE_NAME, ios::out);

		if (!myFile.is_open()) {
			throw runtime_error("Failed to open Users.txt for writing.");
		}

		for (clsUser& user : vClients)
		{
			if (!user._MarkForDelete)
			{
				myFile << _convertUserToLine(user) << '\n';
			}
		}
		myFile.close();
	}

	void _Update()
	{
		vector <clsUser> _vClients = _LoadUsersDataFromFile();
		bool found = false;

		for (clsUser& client : _vClients)
		{
			if (client.getUserName() == _UserName)
			{
				client = *this;
				found = true;
				break;
			}
		}

		if (!found) {
			throw runtime_error("User not found for update");
		}

		_saveUsersDataToFile(_vClients);
	}

	void _AddNew()
	{
		fstream myFile;

		myFile.open(FILE_NAME, ios::out | ios::app);

		if (!myFile.is_open())
		{
			throw runtime_error("Could not open Users file for appending");
		}

		myFile << _convertUserToLine(*this) << endl;
		myFile.close();
	}

public:
	struct stLoginRegisterRecord
	{
		string DateTime = "", Username = "", Password = "";
		int Permissions = 0;
	};

private:

	string _PrepareLogInRecord()
	{
		return clsDate::GetCurrentTimestamp() + SEPARATOR + username + SEPARATOR
			+ clsUtil::EncryptionText(password) + SEPARATOR + to_string(getPermissions()) + "\n";
	}

	static stLoginRegisterRecord convertFromLineToSTLoginRegisterRecord(string line)
	{
		try
		{
			vector<string> data = clsString::SplitEachWordInVector(line, SEPARATOR);

			if (data.size() != 4) {
				throw runtime_error("Invalid Login Register data line.");
			}

			stLoginRegisterRecord LoginRegisterRecord;
			LoginRegisterRecord.DateTime = data[0];
			LoginRegisterRecord.Username = data[1];
			LoginRegisterRecord.Password = clsUtil::DecryptionText(data[2]);
			LoginRegisterRecord.Permissions = stoi(data[3]);

			return LoginRegisterRecord;

		}
		catch (const exception& e)
		{
			cerr << "Error converting line to LoginRegisterRecord: " << e.what() << endl;
			return stLoginRegisterRecord();
		}

	}

	static vector <stLoginRegisterRecord> loadLoginRegisterDataFromFile()
	{
		vector <stLoginRegisterRecord> VLoginRegisterRecord;

		fstream myFile;

		myFile.open(FILE_LOG_IN_REGISTER, ios::in);

		if (!myFile.is_open())
		{
			cerr << "Warning: Could not open LOG IN REGISTER file for reading" << endl;
			return VLoginRegisterRecord;
		}

		string line = "";

		while (getline(myFile, line))
		{
			if (!line.empty()) {
				VLoginRegisterRecord.push_back(convertFromLineToSTLoginRegisterRecord(line));
			}
		}
		myFile.close();
		return VLoginRegisterRecord;
	}

public:

	enum enPermissions
	{
		pAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4, pUpdateClient = 8,
		pFindClient = 16, pTransactions = 32, pManageUser = 64 , pLoginRegister = 128, pTransferRegister = 256
	};

	enum class enSaveResults {
		Failed_EmptyObject,
		Succeeded,
		Failed_AccountExists
	};

	clsUser(enMode mode, string firstName, string lastName, string email, string phone, string username, string password , int permission ) 
		: clsPerson(firstName , lastName, email , phone)
	{
		_Mode = mode;
		_UserName = username;
		_Password = password;
		_Permissions = permission;
	}

	bool IsEmpty()
	{
		return _Mode == enMode::EmptyMode;
	}

	bool MarkFoDelete()
	{
		return _MarkForDelete;
	}

	string getUserName() { return _UserName; }

	string getPassword() { return _Password; }

	int getPermissions() { return _Permissions; }

	void setUserName(string username)
	{
		_UserName = username;
	}

	void setPassword(string password)
	{
		_Password = password;
	}

	void setPermission(int permission)
	{
		_Permissions = permission;
	}

	static clsUser Find(string& userName)
	{
		vector<clsUser> users = _LoadUsersDataFromFile();

		for (clsUser& user : users) {
			if (user._UserName == userName) {
				return user;
			}
		}
		return _getEmptyUserObject();
	}

	static clsUser Find(string& userName, string& password)
	{
		clsUser user = Find(userName);
		if (!user.IsEmpty() && password == user._Password)
		{
			return user;
		}
		return _getEmptyUserObject();
	}

	static bool IsUserExist(string& username)
	{
		return !Find(username).IsEmpty();
	}

	bool IsDeleteUser()
	{
		vector <clsUser> _vUsers = _LoadUsersDataFromFile();
		bool found = false;

		for (clsUser& u : _vUsers)
		{
			if (u.getUserName() == _UserName)
			{
				u._MarkForDelete = true;
				found = true;
				break;
			}
		}

		if (!found) {
			return false;
		}
		_saveUsersDataToFile(_vUsers);

		*this = _getEmptyUserObject();

		return true;
	}

	enSaveResults Save()
	{
		try
		{
			switch (_Mode)
			{
			case enMode::EmptyMode:
				if (IsEmpty())
				{
					return enSaveResults::Failed_EmptyObject;
				}

			case enMode::UpdateMode:
				_Update();
				return enSaveResults::Succeeded;

			case enMode::AddNewMode:
				if (clsUser::IsUserExist(_UserName))
				{
					return enSaveResults::Failed_AccountExists;
				}
				_AddNew();
				_Mode = enMode::UpdateMode;
				return enSaveResults::Succeeded;

			default:
				return enSaveResults::Failed_EmptyObject;
			}
		}
		catch (const exception& e) {
			cerr << "Error saving client: " << e.what() << endl;
			return enSaveResults::Failed_EmptyObject;
		}
	}

	static clsUser getAddNewUserObject(string& username)
	{
		return clsUser(enMode::AddNewMode, "", "", "", "", username, "", 0);
	}

	static vector <clsUser> getUsers()
	{
		return _LoadUsersDataFromFile();
	}

	bool checkAccessPermission(enPermissions permission)
	{
		if (enPermissions::pAll == getPermissions())
			return true;

		if ((getPermissions() & permission) == permission)
			return true;

		else
			return false;
	}

	void RegisterLogIn()
	{
		string stDateLine = _PrepareLogInRecord();

		fstream myFile;
		myFile.open(FILE_LOG_IN_REGISTER, ios::out | ios::app);

		if (!myFile.is_open())
		{
			cerr << "Warning: Could not open clients file for reading" << endl;
			return;
		}

		myFile << stDateLine;
		myFile.close();
	}

	static vector<stLoginRegisterRecord> getLoginRegisterList()
	{
		return loadLoginRegisterDataFromFile();
	}

	__declspec(property(get = getUserName, put = setUserName)) string username;

	__declspec(property(get = getPassword, put = setPassword)) string password;

	__declspec(property(get = getPermissions, put = setPermission)) int accountBalance;
};

const string clsUser::FILE_NAME = "Users.txt";
const string clsUser::FILE_LOG_IN_REGISTER = "LogInRegister.txt";
const string clsUser::SEPARATOR = "#//#";

