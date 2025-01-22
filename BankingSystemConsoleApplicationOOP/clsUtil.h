#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "clsString.h"
#include "clsDate.h"
#include <ctime>

using namespace std;

class clsUtil
{
private:
	static const string ONES[];
	static const string TEENS[];
	static const string TENS[];
	static const string SCALES[];
	static constexpr double MAX_SUPPORTED_NUMBER = 999999999999.99;

	static string convertGroup(int number) {
		string result;

		// Handle hundreds
		if (number >= 100) {
			result += ONES[number / 100] + " Hundred";
			number %= 100;
			if (number > 0) {
				result += " ";
			}
		}

		// Handle tens and ones
		if (number >= 20) {
			result += TENS[number / 10];
			if (number % 10 > 0) {
				result += "-" + ONES[number % 10];
			}
		}
		else if (number >= 10) {
			result += TEENS[number - 10];
		}
		else if (number > 0) {
			result += ONES[number];
		}

		return result;
	}
	

public:
	static float CalculateHalfIsNumber(float number)
	{
		return  number / 2;
	}

	static int GetMax2Number(int num1, int num2)
	{
		return (num1 > num2) ? num1 : num2;
	}

	static int GetMax3Number(int num1, int num2, int num3)
	{
		int moreThan = GetMax2Number(num1, num2);
		return (moreThan > num3) ? moreThan : num3;
	}

	static void Swap2Number(int& num1, int& num2)
	{
		int temp = num1;
		num1 = num2;
		num2 = temp;
	}

	static bool ValidationAge(int age)
	{
		return (age >= 18 && age <= 45);
	}

	static int CalculateSumOddNumbers(int n)
	{
		int sum = 0;
		for (int i = 1; i <= n; i += 2)
		{
			sum += i;
		}
		return sum;
	}

	static int CalculateSumEvenNumbers(int n)
	{
		int sum = 0;
		for (int i = 2; i <= n; i += 2)
		{
			sum += i;
		}
		return sum;
	}

	static int CalculateFactorialNumber(int n)
	{
		int f = 1;
		for (int i = 2; i <= n; i++)
		{
			f *= i;
		}
		return f;
	}

	static short PowerOf_2(short num)
	{
		return num * num;
	}

	static short PowerOf_3(short num)
	{
		return PowerOf_2(num) * num;
	}

	static short PowerOf_4(short num)
	{
		return PowerOf_3(num) * num;
	}

	static int CalculatePowerNumber(short num, short powerNumber)
	{
		if (powerNumber == 0)
			return 1;

		int result = num;

		for (int i = 1; i < powerNumber; i++)
		{
			result *= num;
		}
		return result;
	}

	static double GetCommissionPercentage(int totalSales)
	{
		if (totalSales > 1000000)
			return 0.01;

		else if (totalSales > 500000 and totalSales <= 1000000)
			return 0.02;

		else if (totalSales > 100000 and totalSales <= 500000)
			return 0.03;

		else if (totalSales > 50000 and totalSales <= 100000)
			return 0.05;

		else
			return 0.00;
	}

	static double calculateTotalCommission(int totalSales)
	{
		return (double)GetCommissionPercentage(totalSales) * totalSales;
	}

	struct  stMoneyCategories
	{
		float Pennies = 0, Nickels = 0, Dimes = 0, Quarter = 0, Dollars = 0;
	};

	enum enMoneyCategories
	{
		Pennies = 1, Nickels = 5, Dimes = 10, Quarter = 25, Dollars = 100
	};

	static float CalaculateTotalPennies(stMoneyCategories moneyCategories)
	{
		return
			(moneyCategories.Pennies * enMoneyCategories::Pennies) +
			(moneyCategories.Nickels * enMoneyCategories::Nickels) +
			(moneyCategories.Dimes * enMoneyCategories::Dimes) +
			(moneyCategories.Quarter * enMoneyCategories::Quarter) +
			(moneyCategories.Dollars * enMoneyCategories::Dollars);
	}

	static float CalaculateTotalDollars(float totalPennies)
	{
		return totalPennies / enMoneyCategories::Dollars;
	}

	static short SumNumbersUntil_99(short number)
	{
		int  sum = 0;

		while (number != -99)
		{
			sum += number;
			cout << "Enter Number ? " << endl;
			cin >> number;
		}
		return sum;
	}

	enum enPrimeOrNotPrime { Prime = 1, NotPrime = 2 };

	static enPrimeOrNotPrime checkNumberPrime(short num) {
		if (num <= 1) {
			return enPrimeOrNotPrime::NotPrime; // Numbers <= 1 are not prime
		}
		if (num <= 3) {
			return enPrimeOrNotPrime::Prime; // 2 and 3 are prime numbers
		}
		if (num % 2 == 0 || num % 3 == 0) {
			return enPrimeOrNotPrime::NotPrime; // Eliminate multiples of 2 and 3 early
		}

		// Check divisors from 5 to sqrt(num), skipping even numbers
		for (short i = 5; i * i <= num; i += 6) {
			if (num % i == 0 || num % (i + 2) == 0) {
				return enPrimeOrNotPrime::NotPrime;
			}
		}
		return enPrimeOrNotPrime::Prime;
	}

	struct stInvoice
	{
		float totalBill, cachePaid;
	};

	static float CalculateRemainder(stInvoice invoice)
	{
		float remainder = 0.00;
		if (invoice.cachePaid > invoice.totalBill)
		{
			remainder = invoice.cachePaid - invoice.totalBill;
		}
		return remainder;
	}

	static double CalculateTotalBillAfterChargesServicesAndSalesTax(double totalBill)
	{
		totalBill = totalBill * 1.1;
		totalBill = totalBill * 1.16;

		return totalBill;
	}

	struct stWeeksAndDaysAndHoursAndMinutesAndSeconds
	{
		int numberOfWeeks, numberOfDays, numberOfHours, numberOfMinutes, numberOfSeconds;
	};

	stWeeksAndDaysAndHoursAndMinutesAndSeconds
		CalculateTheNumberOfWeeksAndDaysInThatNumberOFHours(stWeeksAndDaysAndHoursAndMinutesAndSeconds wDHMS)
	{
		wDHMS.numberOfWeeks = 24 * 7,
			wDHMS.numberOfDays = wDHMS.numberOfHours / 24,
			wDHMS.numberOfWeeks = wDHMS.numberOfHours / wDHMS.numberOfWeeks;
		return wDHMS;
	}

	static double CalculateDurationInSeconds(stWeeksAndDaysAndHoursAndMinutesAndSeconds wDHMS)
	{
		return (wDHMS.numberOfDays * 24 * 60 * 60) +
			(wDHMS.numberOfHours * 60 * 60) +
			(wDHMS.numberOfMinutes * 60) + wDHMS.numberOfSeconds;
	}

	enum CalculateSeconds
	{
		secondsOfMinutes = 60,
		secondsOfHours = 3600,
		secondsOfDays = 86400
	};

	static stWeeksAndDaysAndHoursAndMinutesAndSeconds CalculateSecondsTo_Days_Hours_Minutes_Seconds(int totalSeconds)
	{
		stWeeksAndDaysAndHoursAndMinutesAndSeconds wDHMS;
		int Remainder;

		wDHMS.numberOfDays = totalSeconds / CalculateSeconds::secondsOfDays;

		Remainder = totalSeconds % CalculateSeconds::secondsOfDays;

		wDHMS.numberOfHours = Remainder / CalculateSeconds::secondsOfHours;

		Remainder = Remainder % CalculateSeconds::secondsOfHours;

		wDHMS.numberOfMinutes = Remainder / CalculateSeconds::secondsOfMinutes;

		Remainder = Remainder % CalculateSeconds::secondsOfMinutes;

		wDHMS.numberOfSeconds = Remainder;

		return wDHMS;
	}

	enum DaysOfWeekInNumbers
	{
		SunDay = 1, MonDay, TuesDay, WednesDay, ThursDay, FriDay, SatrDay
	};

	void PrintNameDayAgainstNumber(int numberDay)
	{
		switch (numberDay)
		{
		case DaysOfWeekInNumbers::SunDay:
			cout << "SunDay" << endl;
			break;
		case DaysOfWeekInNumbers::MonDay:
			cout << "MonDay" << endl;
			break;
		case DaysOfWeekInNumbers::TuesDay:
			cout << "TuesDay" << endl;
			break;
		case DaysOfWeekInNumbers::WednesDay:
			cout << "WednesDay" << endl;
			break;
		case DaysOfWeekInNumbers::ThursDay:
			cout << "ThursDay" << endl;
			break;
		case DaysOfWeekInNumbers::FriDay:
			cout << "FriDay" << endl;
			break;
		case DaysOfWeekInNumbers::SatrDay:
			cout << "SatrDay" << endl;
			break;

		default:
			cout << "Invalid day number. Please provide a number between "
				<< DaysOfWeekInNumbers::SunDay << " and "
				<< DaysOfWeekInNumbers::SatrDay << "." << std::endl;
			break;
		}
	}

	enum Months
	{
		January = 1, February, March, April, May, June,
		July, August, September, October, November, December
	};

	static void PrintNameMonthAgainstNumber(int numberMonth)
	{
		switch (numberMonth)
		{
		case Months::January:
			cout << "January" << endl;
			break;
		case Months::February:
			cout << "February" << endl;
			break;
		case Months::March:
			cout << "March" << endl;
			break;
		case Months::April:
			cout << "April" << endl;
			break;
		case Months::May:
			cout << "May" << endl;
			break;
		case Months::June:
			cout << "June" << endl;
			break;
		case Months::July:
			cout << "July" << endl;
			break;
		case Months::August:
			cout << "August" << endl;
			break;
		case Months::September:
			cout << "Septembe" << endl;
			break;
		case Months::October:
			cout << "October" << endl;
			break;
		case Months::November:
			cout << "November" << endl;
			break;
		case Months::December:
			cout << "December" << endl;
			break;
		default:
			cout << "Invalid Month number. Please provide a number between "
				<< Months::January << " and "
				<< Months::December << "." << std::endl;
			break;
		}
	}

	static void PrintFromAToZ()
	{
		for (int i = 65; i <= 90; i++)
		{
			cout << (char)i << " , ";
		}
	}

	static float calculateNumberMonthRepayAmount(float loanAmount, float monthlyPayment)
	{
		return loanAmount / monthlyPayment;
	}

	static float CalculateMonthlyInstallmentEveryMonth(float loanAmount, float howManyMonths)
	{
		return loanAmount / howManyMonths;
	}

	static bool isAcceptsDivision(int num1, int num2)
	{
		return num1 % num2 == 0;
	}

	static int SumAllDivisors(int num)
	{
		int sum = 0;
		for (int i = 1; i < num; i++)
		{
			if (isAcceptsDivision(num, i))
			{
				sum += i;
			}
		}
		return sum;
	}

	static int SumOfDigits(int number)
	{
		int remainder = 0, sum = 0;

		while (number > 0)
		{
			remainder = number % 10;
			number /= 10;
			sum += remainder;
		}
		return sum;
	}

	static int reverseNumber(int number)
	{
		int remainder = 0, result = 0;

		while (number > 0)
		{
			remainder = number % 10;
			number /= 10;
			result = result * 10 + remainder;
		}
		return result;
	}

	static short countDigitFrequency(int number, short digit)
	{
		short remainder = 0, counter = 0;

		while (number > 0)
		{
			remainder = number % 10;
			number /= 10;
			if (digit == remainder)
				counter++;
		}
		return counter;
	}

	static bool IsPalindromeNumber(int currentNum)
	{
		return currentNum == reverseNumber(currentNum);
	}

	static void PrintInvertedLetterPatternAsc(int num)
	{
		for (int i = 65; i < (65 + num); i++)
		{
			for (int a = 65; a <= i; a++)
			{
				cout << (char)i;
			}
			cout << endl;
		}
	}

	static void PrintAllWordsFromAAAToZZZ()
	{
		string result = "";

		for (int i = 65; i <= 90; i++)
		{
			for (int j = 65; j <= 90; j++)
			{
				for (int a = 65; a <= 90; a++)
				{
					result += (char)i;
					result += (char)j;
					result += (char)a;
					cout << result << endl;
					result = "";
				}
			}
		}
	}

	static bool GuessPassword(string originalPassword)
	{
		int counter = 0;
		string guessPass = "";
		for (int i = 65; i <= 90; i++)
		{
			for (int j = 65; j <= 90; j++)
			{
				for (int h = 65; h <= 90; h++)
				{
					guessPass += (char)i;
					guessPass += (char)j;
					guessPass += (char)h;
					counter++;

					cout << "Trial[" << counter << "] : " << guessPass << endl;

					if (guessPass == originalPassword)
					{
						cout << "--------------------------------------\n";
						cout << "Password Is " + originalPassword;
						cout << "Found after " << counter << " Trail" << endl;
						cout << "--------------------------------------";
						return true;
					}
					guessPass = "";
				}
			}
		}
	}

	static string EncryptionText(string text)
	{
		string EncryptText = "";
		for (int i = 0; i < text.length(); i++)
		{
			int asciiCode = (int)text[i];
			asciiCode += 2;
			EncryptText += (char)asciiCode;
		}
		return EncryptText;
	}

	static string DecryptionText(string encrypttext)
	{
		string DecryptText = "";
		for (int i = 0; i < encrypttext.length(); i++)
		{
			int asciiCode = (int)encrypttext[i];
			asciiCode -= 2;
			DecryptText += (char)asciiCode;
		}
		return DecryptText;
	}

	static int RandomNumber(int from, int to)
	{
		return rand() % (to - from + 1) + from;
	}

	enum enCharacterType{ SmallLetter, CapitalLetter, SpecialCharacter, DigitInOrder };

	static char GetCharacterRandom(enCharacterType charType)
	{
		switch (charType)
		{
		case enCharacterType::SmallLetter:
			return (char)RandomNumber(97, 122);

		case enCharacterType::CapitalLetter:
			return (char)RandomNumber(65, 90);

		case enCharacterType::SpecialCharacter:
			return (char)RandomNumber(33, 47);

		case enCharacterType::DigitInOrder:
			return (char)RandomNumber(48, 57);

		default:
			// Handle unexpected input gracefully
			return '\0';  // Return a null character as a fallback
		}
	}

	static string GenerateWord(enCharacterType charType, short Length)
	{
		string word = "";
		for (int i = 0; i < Length; i++)
		{
			word += GetCharacterRandom(charType);
		}
		return word;
	}

	static string GenerateKey()
	{
		string key = "";

		for (int i = 0; i < 4; i++)
		{
			key += GenerateWord(enCharacterType::CapitalLetter, 4);
			if (i < 3)
			{
				key += "-";
			}
		}

		return key;
	}

	static void PrintGenerateKeysFrom1ToN(short num)
	{
		for (int i = 1; i <= num; i++)
		{
			cout << "Key[" << i << "] : " << GenerateKey() << endl;
		}
	}

	static float MyAbs(float numNegative)
	{
		return (numNegative > 0) ? numNegative : numNegative * -1;
	}

	static float GetFraction(float number)
	{
		return number - (int)number;
	}

	static int MyRound(float number)
	{
		int intNumber = (int)number;

		if (abs(GetFraction(number)) >= .5)
		{
			if (intNumber > 0)
				++intNumber;
			else
				--intNumber;
		}
		return intNumber;
	}

	static int MyFloor(float number)
	{
		int intNum = (int)number;
		if (intNum < 0)
		{
			--intNum;
		}
		return intNum;
	}

	static int MyCeil(float number)
	{
		if (abs(GetFraction(number)) > 0)
		{
			if (number > 0)
				return (int)number + 1;
			else
				return (int)number;
		}
		return (int)number;
	}

	static double MySqrt(double number)
	{
		return pow(number, 0.5);
	}

	static string numberToText(double number) {
		try {
			// Handle invalid input
			if (number < 0) {
				return "Negative numbers are not supported";
			}
			if (number > MAX_SUPPORTED_NUMBER) {
				return "Number is too large to convert";
			}

			// Handle zero
			if (number == 0) {
				return "Zero";
			}

			string result;
			long long intPart = (long long)(number);

			// Handle decimal part
			string cents;
			double decimalPart = number - intPart;
			if (decimalPart > 0) {
				int centsPart = (int)(round(decimalPart * 100));
				if (centsPart > 0) {
					cents = " and " + to_string(centsPart) + "/100";
				}
			}

			// Process groups of three digits
			int scaleIndex = 0;
			while (intPart > 0) {
				int group = intPart % 1000;
				if (group > 0) {
					string groupText = convertGroup(group);
					if (!result.empty() && !groupText.empty()) {
						result = " " + result;
					}
					if (scaleIndex > 0 && !groupText.empty()) {
						groupText += " " + SCALES[scaleIndex];
						if (group > 1) {
							groupText += "s";
						}
					}
					result = groupText + result;
				}
				intPart /= 1000;
				scaleIndex++;
			}

			// Add cents if present
			result += cents;

			// Trim extra spaces
			while (result.find("  ") != string::npos) {
				result.replace(result.find("  "), 2, " ");
			}

			// Trim leading and trailing spaces
			if (!result.empty() && result[0] == ' ') {
				result.erase(0, 1);
			}
			if (!result.empty() && result[result.length() - 1] == ' ') {
				result.erase(result.length() - 1);
			}

			return result;
		}
		catch (...) {
			return "Error converting number";
		}
	}

	static string GetCurrentTimestamp()
	{
		time_t now = time(nullptr);
		char buffer[26]; 
		ctime_s(buffer, sizeof(buffer), &now); 
		std::string timestamp(buffer);
		timestamp.pop_back(); 
		return timestamp;
	}
};

// Static member initialization
const string clsUtil::ONES[] = {
	"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine"
};

const string clsUtil::TEENS[] = {
	"Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen",
	"Sixteen", "Seventeen", "Eighteen", "Nineteen"
};

const string clsUtil::TENS[] = {
	"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"
};

const string clsUtil::SCALES[] = {
	"", "Thousand", "Million", "Billion"
};

