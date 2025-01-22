#pragma once
#include <iostream>
#include <string>
#include "InterfaceCommunication.h"

using namespace std;

class clsPerson :public InterfaceCommunication
{
private:
	string _FirstName, _LastName, _Email, _Phone;

public:
	clsPerson(string firstName, string lastName, string phone)
		: clsPerson(firstName, lastName, phone, ""){}

	clsPerson(string firstName , string lastName , string email , string phone)
	{
		_FirstName = firstName;
			_LastName = lastName;
			_Email = email;
			_Phone = phone;
	}

	string getFirstName()
	{
		return _FirstName;
	}

	void setFirstName(string firstName)
	{
		_FirstName = firstName;
	}

	string getLastName()
	{
		return _LastName;
	}

	void setLastName(string lastName)
	{
		_LastName = lastName;
	}

	string getEmail()
	{
		return _Email;
	}

	void setEmail(string email)
	{
		_Email = email;
	}

	string getPhone()
	{
		return _Phone;
	}

	void setPhone(string phone)
	{
		_Phone = phone;
	}

	string getFullName()
	{
		return getFirstName() + " " + getLastName();
	}

	void SendEmail(string Title, string Body)
	{

	}

	void SendFax(string Title, string Body)
	{

	}

	void SendSMS(string Title, string Body)
	{

	}

	__declspec(property(get = getFirstName, put = setFirstName))string firstName;
	__declspec(property(get = getLastName,	put = setLastName))	string lastName;
	__declspec(property(get = getEmail,		put = setEmail))	string email;
	__declspec(property(get = getPhone,		put = setPhone))	string phone;

	

	
};

