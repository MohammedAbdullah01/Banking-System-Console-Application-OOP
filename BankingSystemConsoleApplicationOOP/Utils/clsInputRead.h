#pragma once
#include <iostream>
#include <string>
#include "clsInputValidate.h"

using namespace std;

class clsInputRead
{
public:
	static char ReadCharacter(string msg)
	{
		char charcter;
		cout << msg;
		cin >> charcter;
		return charcter;
	}

	static string ReadWord(string msg)
	{
		string Word;
		cout << msg;
		cin >> Word;
		return Word;
	}

	static string ReadWords(string msg)
	{
		string Inter = ReadWord(msg);
		getline(cin >> ws, Inter);
		return Inter;
	}

	template <typename T> static T ReadNumber()
	{
		T number;
		cin >> number;
		return number;
	}

	template <typename T> static T ReadPositiveNumber(string msgInvalid)
	{
		T number = ReadNumber<T>();
		while (number <= 0)
		{
			cout << msgInvalid << endl;
		}
		return number;
	}

	template <typename T> static T ReadNumberInRange(T from, T to , string msgInvalid)
	{

		T number = ReadNumber<T>();
		
		while ( !clsInputValidate::IsNumberBetween(number , from , to))
		{
			cout << msgInvalid << '\n';
			number = ReadNumber<T>();
		}
		return number;
	}

	static char ReadCharacterAsteriskOrPlusOrMinusOrDivide()
	{
		char character;
		do
		{
			character = ReadCharacter("Please Enter Asterisk Or Plus Or Minus Or Divide (*, +, -, /): ");
		} while (character != '*' &&
			character != '+' &&
			character != '-' &&
			character != '/');

		return character;
	}

};

