#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <algorithm>
#include "clsDate.h"
#include "clsInputRead.h"

using namespace std;

class clsInputValidate
{
public:

	template <typename T> static bool IsNumberBetween(T num, T numFrom, T numTo)
	{
		return num >= numFrom && num <= numTo;
	}

	static bool IsDateBetween(clsDate currentDate , clsDate dateFrom , clsDate dateTo)
	{
		if ((currentDate.CompareDates(dateFrom) == clsDate::enDateCompare::After) &&
			(currentDate.CompareDates(dateTo) == clsDate::enDateCompare::Before))
		{
			return true;
		}

		if ((currentDate.CompareDates(dateTo) != clsDate::enDateCompare::Before) &&
			(currentDate.CompareDates(dateFrom) != clsDate::enDateCompare::After))
			return true;

		return false;
	}

	template <typename T> static T ReadNumberWithValidate(string msgInvalid)
	{
		T number;
		string input;

		while (true)
		{
			cin >> input; // Read input as string

			// Try to convert the input to a double
			stringstream ss(input);
			if (ss >> number && ss.eof())  // Ensure the entire string is valid and can be converted to a double
			{
				break;  // Exit the loop if the number is valid
			}
			else
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
				cout << msgInvalid; // Print the invalid message
			}
		}

		return number;
	}

	template <typename T> static T ReadNumberWithValidateAndPositiveNumber()
	{
		T num;
		do
		{
			num = ReadNumberWithValidate<T>("\nYou have to enter a number only!, Enter another number ? ");

			if (num <= 0)
			{
				cout << "\nThe number must be positive! , Enter another number ? ";
			}

		} while (num <= 0);
		return num;
	}

	static bool IsValidateDate(clsDate date) {
		return clsDate::validateDate(date);
	}

	static bool isValidName(string& name) {
		return !name.empty() && name.length() <= 15 &&
			all_of(name.begin(), name.end(), [](char c) {
			return isalpha(c) || isspace(c);
				});
	}

	static bool isValidEmail(string& email) {
		// Basic email validation
		return email.find('@') != string::npos &&
			email.find('.') != string::npos &&
			email.length() >= 5;
	}

	static bool isValidPhone(string& phone) {
		return !phone.empty() && phone.length() >= 10 &&
			all_of(phone.begin(), phone.end(), [](char c) {
			return isdigit(c) || c == '+' || c == '-';
				});
	}

	static bool isValidPinCode(string& pin) {
		return pin.length() >= 4 &&
			all_of(pin.begin(), pin.end(), ::isdigit);
	}
};

