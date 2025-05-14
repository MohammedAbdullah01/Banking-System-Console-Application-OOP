#pragma once

#include <iostream>
#include <iomanip>
#include <sstream>
#include <chrono>
#include <ctime>
#include <vector>
#include <string>
#include "clsString.h"

using namespace std;

class clsDate
{
private:
	short _Year = 1900, _Month = 1, _Day = 0;

public:

	clsDate()
	{
		SystemDate();
	}

	clsDate(string date)
	{
		convertDateFromDateStringToDateObject(date);

		if (!validateDate())
		{
			throw invalid_argument("is a Not Valid Date (dd/mm/yyy) : (" + date + ")");
		}
	}

	clsDate(short day, short month, short year)
	{
		_Day = day;
		_Month = month;
		_Year = year;

		if (!validateDate())
		{
			throw invalid_argument("is a Not Valid Date (dd/mm/yyy) : (" + to_string(day) + "/" + to_string(month) + "/" + to_string(year) + ")");
		}
	}

	clsDate(short addingDays, short year)
	{
		if (year < 1900 || addingDays < 1) {
			throw std::invalid_argument("Invalid arguments: Year must be >= 1900 and totalDay >= 1");
		}

		_Year = year;
		convertFromTotalDaysToDate(addingDays);
	}

	static bool isLeapYear(short year)
	{
		return ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0);
	}

	bool isLeapYear()
	{
		return isLeapYear(_Year);
	}

	static short howManyDaysInYear(short year)
	{
		return isLeapYear(year) ? 366 : 365;
	}

	short howManyDaysInYear()
	{
		return howManyDaysInYear(_Year);
	}

	enum enNumberOfDaysPerMonth
	{
		January = 1, February, March, April, May, June, July, August, September,
		October, November, December
	};

	static short howManyDaysInMonth(short year, enNumberOfDaysPerMonth month)
	{
		switch (month)
		{
		case January:
		case March:
		case May:
		case July:
		case August:
		case October:
		case December:
			return 31;

		case February:
			return isLeapYear(year) ? 29 : 28;

		case April:
		case June:
		case September:
		case November:
			return 30;

		default:
			return 0;
		}
	}

	short howManyDaysInMonth()
	{
			return howManyDaysInMonth(isLeapYear() , (enNumberOfDaysPerMonth)_Month);
	}

	static clsDate GetSystemDate()
	{
		time_t t = time(0);
		tm now;

		short day, month, year;
		localtime_s(&now, &t);

		year = now.tm_year + 1900;
		month = now.tm_mon + 1;
		day = now.tm_mday;

		return clsDate(day , month , year);
	}

	 void SystemDate()
	{
		 *this = GetSystemDate();
	}

	 static string GetCurrentTimestamp()
	 {
		 auto now = chrono::system_clock::now();
		 time_t now_c = chrono::system_clock::to_time_t(now);
		 tm tm;
		 localtime_s(&tm, &now_c);

		 ostringstream oss;
		 oss << put_time(&tm, "%Y-%m-%d - %H:%M:%S");
		 return oss.str();
	 }

	 static bool validateDate(clsDate date) {
		 if (date._Month < 1 || date._Month > 12 || date._Day < 1 || date._Day > 31) {
			 return false;
		 }
		 short daysInMonth = howManyDaysInMonth(date._Year, (enNumberOfDaysPerMonth)date._Month);
		 return date._Day <= daysInMonth;
	 }

	 bool validateDate()
	 {
		 return validateDate(*this);
	 }

	 void convertDateFromDateStringToDateObject(string dateString, string separator = "/")
	 {
		 vector <string> vDate = clsString::SplitEachWordInVector(dateString, separator);

		 _Day = stoi(vDate.at(0));
		 _Month = stoi(vDate.at(1));
		 _Year = stoi(vDate.at(2));
	 }

	 static bool IsLastDayInMonth(clsDate date)
	 {
		 return date._Day == howManyDaysInMonth(date._Year, (enNumberOfDaysPerMonth)date._Month);
	 }

	 bool IsLastDayInMonth()
	 {
		 return _Day == howManyDaysInMonth(_Year, (enNumberOfDaysPerMonth)_Month);
	 }

	 static bool IsLastMonthInYear(short month)
	 {
		 return month == 12;
	 }

	 bool IsLastMonthInYear()
	 {
		 return IsLastMonthInYear(_Month);
	 }

	 static clsDate increaseDateByOneDay(clsDate date)
	 {
		 if (IsLastDayInMonth(date))
		 {
			 if (IsLastMonthInYear(date._Month))
			 {
				 date._Year++;
				 date._Day = 1;
				 date._Month = 1;
			 }
			 else
			 {
				 date._Day = 1;
				 date._Month++;
			 }
		 }
		 else
		 {
			 date._Day++;
		 }
		 return date;
	 }

	 void increaseDateByOneDay()
	 {
		 *this = increaseDateByOneDay(*this);
	 }

	 static clsDate IncreaseDateByXDays(clsDate date, short addingDays)
	 {
		 while (addingDays > 0) {
			 date = increaseDateByOneDay(date);
			 addingDays--;
		 }
		 return date;
	 }

	 void IncreaseDateByXDays(short addingDays)
	 {
		 *this = IncreaseDateByXDays(*this , addingDays);
	 }

	 static clsDate convertFromTotalDaysToDate(short totalDay, short year)
	 {
		 short daysInMonth;
		 clsDate date;

		 date._Year = year;

		 for (short i = 1; i <= 12; i++)
		 {
			 daysInMonth = howManyDaysInMonth(year, (enNumberOfDaysPerMonth)i);

			 if (daysInMonth >= totalDay)
			 {
				date._Month = i;
				 date._Day = totalDay;
				 break;
			 }
			 totalDay -= daysInMonth;
		 }
		 return date;
	 }

	 void convertFromTotalDaysToDate(short totalDay)
	 {
		 *this = convertFromTotalDaysToDate(totalDay , _Year);
	 }

	static void DisplayDate(clsDate date , char separator = '/')
	{
		cout << (date._Day < 10 ? "0" : "") << to_string(date._Day) << separator
			<< (date._Month < 10 ? "0" : "") << to_string(date._Month) << separator
			<< to_string(date._Year) << endl;
	}

	void DisplayDate(char separator = '/')
	{
		DisplayDate(*this, separator);
	}

	static string FormatDate(clsDate date, string format = "dd/mm/yyyy")
	{
		string formaDate = "";
		formaDate = clsString::replaceWordInString(format, "dd", to_string(date._Day));
		formaDate = clsString::replaceWordInString(formaDate, "mm", to_string(date._Month));
		formaDate = clsString::replaceWordInString(formaDate, "yyyy", to_string(date._Year));
		return formaDate;

	}

	string FormatDate(string format = "dd/mm/yyy")
	{
		return FormatDate(*this , format);
	}

	static short dayOfWeekOrder(short year, short month, short day)
	{
		short
			a = (14 - month) / 12,
			y = year - a,
			m = month + (12 * a) - 2,
			d = day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12);

		return (d % 7) + 1;

	}

	static short dayOfWeekOrder(clsDate date)
	{
		return dayOfWeekOrder(date._Year, date._Month, date._Day);
	}

	short dayOfWeekOrder()
	{
		return dayOfWeekOrder(*this);
	}

	static string getMonthName(enNumberOfDaysPerMonth monthNumber)
	{
		switch (monthNumber)
		{
		case January:	return "Jan";
		case February:	return "Feb";
		case March:		return "Mar";
		case April:		return "Apr";
		case May:		return "May";
		case June:		return "Jun";
		case July:		return "Jul";
		case August:	return "Aug";
		case September:	return "Sep";
		case October:	return "Oct";
		case November:	return "Nov";
		case December:	return "Dec";
		default:		return "Not Found Month";
		}
	}

	static short getTotalDaysFromBeginOfYear(short year, short month, short day)
	{
		short sumDay = day;
		for (short i = 1; i < month; i++)
		{
			sumDay += howManyDaysInMonth(year, (enNumberOfDaysPerMonth)i);
		}
		return sumDay;
	}

	static short getTotalDaysFromBeginOfYear(clsDate date)
	{
		return getTotalDaysFromBeginOfYear(date._Year, date._Month, date._Day);
	}

	short getTotalDaysFromBeginOfYear()
	{
		return getTotalDaysFromBeginOfYear(_Year, _Month, _Day);
	}

	static bool IsDate1BeforeDate2(clsDate date1, clsDate date2)
	{
		if (date1._Year < date2._Year)
			return true;
		else if (date1._Year > date2._Year)
			return false;

		if (date1._Month < date2._Month)
			return true;
		else if (date1._Month > date2._Month)
			return false;

		return date1._Day < date2._Day;
	}

	bool IsDate1BeforeDate2(clsDate date)
	{
		return IsDate1BeforeDate2(*this, date);
	}

	static bool IsDate1EqualDate2(clsDate date1, clsDate date2)
	{
		return date1._Year == date2._Year && 
				date1._Month == date2._Month && 
				date1._Day == date2._Day;
	}

	bool IsDate1EqualDate2(clsDate date2)
	{
		return  IsDate1EqualDate2(*this, date2);
	}

	static void swapDates(clsDate& date, clsDate& date2)
	{
		clsDate temp = date;
		date = date2;
		date2 = temp;
	}

	static int calculateDifferenceInDays(clsDate date1, clsDate date2, bool IncludingEndDay = false)
	{
		int days = 0;
		short swapFlagValue = 1;

		if (IsDate1EqualDate2(date1, date2))
			return ++days;

		if (!IsDate1BeforeDate2(date1, date2))
		{
			swapDates(date1, date2);
			swapFlagValue = -1;
		}

		while (IsDate1BeforeDate2(date1, date2))
		{
			days++;
			date1 = increaseDateByOneDay(date1);
		}

		return IncludingEndDay ? ++days * swapFlagValue : days * swapFlagValue;
	}

	int calculateDifferenceInDays(clsDate Newdate, bool IncludingEndDay = false)
	{
		return calculateDifferenceInDays(*this, Newdate, IncludingEndDay);
	}

	static clsDate IncreaseDateByOneWeek(clsDate date)
	{
		return IncreaseDateByXDays(date, 7);
	}

	void IncreaseDateByOneWeek()
	{
		*this =  IncreaseDateByXDays(*this, 7);
	}

	static clsDate IncreaseDateByXWeek(clsDate date, short addingWeeks)
	{
		return IncreaseDateByXDays(date, addingWeeks * 7);
	}

	void IncreaseDateByXWeek(short addingWeeks)
	{
		*this =  IncreaseDateByXDays(*this, addingWeeks);
	}

	static clsDate IncreaseDateByOneMonth(clsDate date)
	{
		if (date._Month == 12)
		{
			date._Month = 1;
			date._Year++;
		}
		else
		{
			date._Month++;
		}

		short numberOfDaysInMonthCurrent = howManyDaysInMonth(date._Year, (enNumberOfDaysPerMonth)date._Month);

		if (date._Day > numberOfDaysInMonthCurrent)
		{
			date._Day = numberOfDaysInMonthCurrent;
		}
		return date;
	}

	void IncreaseDateByOneMonth()
	{
		*this = IncreaseDateByOneMonth(*this);
	}

	static clsDate IncreaseDateByXMonth(clsDate date, short addingMonths)
	{
		for (short i = 1; i <= addingMonths; i++)
		{
			date = IncreaseDateByOneMonth(date);
		}
		return date;
	}

	void IncreaseDateByXMonth(short addingMonths)
	{
		*this = IncreaseDateByXMonth(*this , addingMonths);
	}

	static clsDate IncreaseDateByOneYear(clsDate date)
	{
		date._Year++;
		short numberOfDaysInMonthCurrent = howManyDaysInMonth(date._Year, (enNumberOfDaysPerMonth)date._Month);

		if (date._Day > numberOfDaysInMonthCurrent)
			date._Day = numberOfDaysInMonthCurrent;

		return date;
	}

	void IncreaseDateByOneYear()
	{
		*this = IncreaseDateByOneYear(*this);
	}

	static clsDate IncreaseDateByXYears(clsDate date, short addingYears)
	{
		for (short i = 1; i <= addingYears; i++)
		{
			date = IncreaseDateByOneYear(date);
		}
		return date;
	}

	void IncreaseDateByXYears(short addingYears)
	{
		*this = IncreaseDateByXYears(*this , addingYears);
	}

	static clsDate IncreaseDateByXYearsFaster(clsDate date, short addingYears)
	{
		date._Year += addingYears;
		short numberOfDaysInMonthCurrent = howManyDaysInMonth(date._Year, (enNumberOfDaysPerMonth)date._Month);

		if (date._Day > numberOfDaysInMonthCurrent)
			date._Day = numberOfDaysInMonthCurrent;

		return date;
	}

	void IncreaseDateByXYearsFaster(short addingYears)
	{
		*this = IncreaseDateByXYearsFaster(*this , addingYears);
	}

	static clsDate IncreaseDateByOneDecade(clsDate date)
	{
		return IncreaseDateByXYearsFaster(date, 10);
	}

	void IncreaseDateByOneDecade()
	{
		*this = IncreaseDateByOneDecade(*this);
	}

	static clsDate IncreaseDateByXDecades(clsDate date, short addingDecades)
	{
		for (short i = 1; i <= addingDecades; i++)
		{
			date = IncreaseDateByXYearsFaster(date, 10);
		}
		return date;
	}

	void IncreaseDateByXDecades(short addingDecades)
	{
		*this = IncreaseDateByXDecades(*this , addingDecades);
	}

	static clsDate IncreaseDateByXDecadesFaster(clsDate date, short addingDecades)
	{
		return IncreaseDateByXYearsFaster(date, 10 * addingDecades);
	}

	void IncreaseDateByXDecadesFaster(short addingDecades)
	{
		*this = IncreaseDateByXDecadesFaster(*this ,addingDecades);
	}

	static clsDate IncreaseDateByOneCentury(clsDate date)
	{
		return IncreaseDateByXYearsFaster(date, 100);
	}

	void IncreaseDateByOneCentury()
	{
		*this = IncreaseDateByOneCentury(*this);
	}

	static clsDate IncreaseDateByOneMillennium(clsDate date)
	{
		return IncreaseDateByXYearsFaster(date, 1000);
	}

	void IncreaseDateByOneMillennium()
	{
		*this = IncreaseDateByOneMillennium(*this);
	}

	static clsDate decreaseDateByOneDay(clsDate date)
	{
		if (date._Day == 1 && date._Month == 1)
		{
			date._Year--;
			date._Day = 31;
			date._Month = 12;
		}
		else if (date._Month <= 12 && date._Day == 1)
		{
			date._Month--;
			date._Day = howManyDaysInMonth(date._Year, (enNumberOfDaysPerMonth)date._Month);
		}
		else
		{
			date._Day--;
		}

		return date;
	}

	void decreaseDateByOneDay()
	{
		*this = decreaseDateByOneDay(*this);
	}

	static clsDate decreaseDateByXDays(clsDate date, short subtractDays)
	{
		while (subtractDays > 0)
		{
			date = decreaseDateByOneDay(date);
			subtractDays--;
		}
		return date;
	}

	void decreaseDateByXDays(short subtractDays)
	{
		*this = decreaseDateByXDays(*this , subtractDays);
	}

	static clsDate decreaseDateByOneWeek(clsDate date)
	{
		return decreaseDateByXDays(date, 7);
	}

	void decreaseDateByOneWeek()
	{
		*this = decreaseDateByOneWeek(*this);
	}

	static clsDate decreaseDateByXWeeks(clsDate date, short subtractWeeks)
	{
		return decreaseDateByXDays(date, subtractWeeks * 7);
	}

	void decreaseDateByXWeeks(short subtractWeeks)
	{
		*this = decreaseDateByXWeeks(*this , subtractWeeks);
	}

	static clsDate decreaseDateByOneMonth(clsDate date)
	{
		if (date._Month == 1)
		{
			date._Month = 12;
			date._Year--;
		}
		else
		{
			date._Month--;
		}

		short numberDaysInMonthCurrent = howManyDaysInMonth(date._Year, (enNumberOfDaysPerMonth)date._Month);
		if (date._Day > numberDaysInMonthCurrent)
		{
			date._Day = numberDaysInMonthCurrent;
		}
		return date;
	}

	void decreaseDateByOneMonth()
	{
		*this = decreaseDateByOneMonth(*this);
	}

	static clsDate decreaseDateByXMonths(clsDate date, short subtractMonths)
	{
		while (subtractMonths > 0)
		{
			date = decreaseDateByOneMonth(date);
			subtractMonths--;
		}
		return date;
	}

	void decreaseDateByXMonths(short subtractMonths)
	{
		*this = decreaseDateByXMonths(*this , subtractMonths);
	}

	static clsDate decreaseDateByOneYear(clsDate date)
	{
		date._Year--;
		short daysInMonth = howManyDaysInMonth(date._Year, (enNumberOfDaysPerMonth)date._Month);

		if (date._Day > daysInMonth)
		{
			date._Day = daysInMonth;
		}
		return date;
	}

	void decreaseDateByOneYear()
	{
		*this = decreaseDateByOneYear(*this);
	}

	static clsDate decreaseDateByXYears(clsDate date, short subtractYears)
	{
		while (subtractYears > 0)
		{
			date = decreaseDateByOneYear(date);
			subtractYears--;
		}
		return date;
	}

	void decreaseDateByXYears(short subtractYears)
	{
		*this = decreaseDateByXYears(*this, subtractYears);
	}

	static clsDate decreaseDateByXYearsFaster(clsDate date, short subtractYears)
	{
		date._Year -= subtractYears;
		short daysInMonth = howManyDaysInMonth(date._Year, (enNumberOfDaysPerMonth)date._Month);

		if (date._Day > daysInMonth)
		{
			date._Day = daysInMonth;
		}
		return date;
	}

	void decreaseDateByXYearsFaster(short subtractYears)
	{
		*this = decreaseDateByXYearsFaster(*this, subtractYears);
	}

	static clsDate decreaseDateByOneDecade(clsDate date)
	{
		return decreaseDateByXYearsFaster(date, 10);
	} 

	void decreaseDateByOneDecade()
	{
		*this = decreaseDateByOneDecade(*this);
	}

	static clsDate decreaseDateByXDecades(clsDate date, short subtractDecades)
	{
		while (subtractDecades > 0)
		{
			date = decreaseDateByXYearsFaster(date, 10);
			subtractDecades--;
		}
		return date;
	}

	void decreaseDateByXDecades(short subtractDecades)
	{
		*this = decreaseDateByXDecades(*this , subtractDecades);
	}

	static clsDate decreaseDateByXDecadesFaster(clsDate date, short subtractDecades)
	{
		return decreaseDateByXYearsFaster(date, subtractDecades * 10);
	}

	void decreaseDateByXDecadesFaster(short subtractDecades)
	{
		*this = decreaseDateByXDecadesFaster(*this , subtractDecades);
	}

	static clsDate decreaseDateByOneCentury(clsDate date)
	{
		return decreaseDateByXYearsFaster(date, 100);
	}

	void decreaseDateByOneCentury()
	{
		*this = decreaseDateByOneCentury(*this);
	}

	static clsDate decreaseDateByOneMillennium(clsDate date)
	{
		return decreaseDateByXYearsFaster(date, 1000);
	}

	void decreaseDateByOneMillennium()
	{
		*this = decreaseDateByOneMillennium(*this);
	}

	static bool IsEndOfWeek(clsDate date)
	{
		return dayOfWeekOrder(date) == 7;
	}

	bool IsEndOfWeek()
	{
		return IsEndOfWeek(*this);
	}

	static bool IsWeekEnd(clsDate date)
	{
		return IsEndOfWeek(date) || dayOfWeekOrder(date) == 6;
	}

	bool IsWeekEnd()
	{
		return IsWeekEnd(*this);
	}

	static bool IsBusinessDay(clsDate date)
	{
		return !IsWeekEnd(date);
	}

	bool IsBusinessDay()
	{
		return IsBusinessDay(*this);
	}

	static short DaysUntilTheEndOfWeek(clsDate date)
	{
		return 7 - dayOfWeekOrder(date);
	}

	short DaysUntilTheEndOfWeek()
	{
		return DaysUntilTheEndOfWeek(*this);
	}

	static short DaysUntilTheEndOfMonth(clsDate date)
	{
		return howManyDaysInMonth(date._Year, (enNumberOfDaysPerMonth)date._Month) - date._Day;
	}

	short DaysUntilTheEndOfMonth()
	{
		return DaysUntilTheEndOfMonth(*this);
	}

	static short DaysUntilTheEndOfYear(clsDate date)
	{
		return IsLastMonthInYear(date._Month) ? DaysUntilTheEndOfMonth(date) :
			howManyDaysInYear(date._Year) - getTotalDaysFromBeginOfYear(date);
	}

	short DaysUntilTheEndOfYear( )
	{
		return DaysUntilTheEndOfYear(*this);
	}

	static short howManyTheActualVacationDaysFromDate1ToDate2(clsDate dateFrom, clsDate dateTo)
	{
		short ActualVacation = 0;
		while (IsDate1BeforeDate2(dateFrom, dateTo))
		{
			if (!IsWeekEnd(dateFrom))
			{
				ActualVacation++;
			}

			dateFrom = increaseDateByOneDay(dateFrom);
		}

		return ActualVacation;
	}

	short howManyTheActualVacationDaysFromDate1ToDate2(clsDate dateTo)
	{
		return howManyTheActualVacationDaysFromDate1ToDate2(*this , dateTo);
	}

	static clsDate vacationReturnDate(clsDate dateFrom, short vacationDays)
	{
		if (!validateDate(dateFrom))
			throw invalid_argument("Invalid start date provided.");

		clsDate returnDate = dateFrom;
		while (vacationDays > 0 || IsWeekEnd(returnDate))
		{
			if (IsBusinessDay(returnDate))
				vacationDays--;

			returnDate = increaseDateByOneDay(returnDate);
		}

		if (!validateDate(returnDate))
			throw runtime_error("Resulting date is invalid.");

		return returnDate;
	}

	clsDate vacationReturnDate(short vacationDays)
	{
		return vacationReturnDate(*this, vacationDays);
	}

	static bool IsDate1AfterDate2(clsDate date1, clsDate date2)
	{
		return (!IsDate1BeforeDate2(date1, date2) && !IsDate1EqualDate2(date1, date2));
	}

	bool IsDate1AfterDate2(clsDate date)
	{
		return IsDate1AfterDate2(*this, date);
	}

	static short calculateBusinessDates(clsDate dateFrom ,clsDate dateTo)
	{
		if (!validateDate(dateFrom) || !validateDate(dateTo))
			throw invalid_argument("Invalid Date Provided.");

		short diffDays = calculateDifferenceInDays(dateFrom , dateTo);

		short totalBusinessDays = 0;

		while (diffDays > 0)
		{
			if (IsBusinessDay(dateFrom))
			{
				totalBusinessDays++;
			}
			dateFrom = increaseDateByOneDay(dateFrom);
			diffDays--;
		}
		return totalBusinessDays;
	}

	short calculateBusinessDates(clsDate dateTo)
	{
		return calculateBusinessDates(*this , dateTo);
	}

	short calculateBusinessFromDateToNowDate()
	{
		return calculateBusinessDates(GetSystemDate());
	}

	enum enDateCompare
	{
		Before = -1, Equal, After
	};

	static enDateCompare CompareDates(clsDate date1, clsDate date2)
	{
		return IsDate1BeforeDate2(date1, date2) ? enDateCompare::Before
			: IsDate1AfterDate2(date1, date2) ? enDateCompare::After
			: enDateCompare::Equal;
	}

	enDateCompare CompareDates(clsDate date)
	{
		return CompareDates(*this, date);
	}

	static short howManyHoursInYear(short year)
	{
		return howManyDaysInYear(year) * 24;
	}

	short howManyHoursInYear()
	{
		return howManyHoursInYear(_Year);
	}

	static int howManyMinutesInYear(short year)
	{
		return howManyHoursInYear(year) * 60;
	}

	int howManyMinutesInYear()
	{
		return howManyMinutesInYear(_Year);
	}

	static int howManySecondsInYear(short year)
	{
		return howManyMinutesInYear(year) * 60;
	}

	int howManySecondsInYear()
	{
		return howManyMinutesInYear(_Year);
	}

	static short howManyHoursInMonth(short year, enNumberOfDaysPerMonth month)
	{
		return howManyDaysInMonth(year, month) * 24;
	}

	short howManyHoursInMonth()
	{
		return howManyHoursInMonth(_Year , (enNumberOfDaysPerMonth) _Month);
	}

	static int howManyMinutesInMonth(short year, enNumberOfDaysPerMonth month)
	{
		return howManyHoursInMonth(year, month) * 60;
	}

	short howManyMinutesInMonth()
	{
		return howManyMinutesInMonth(_Year, (enNumberOfDaysPerMonth)_Month);
	}

	static int howManySecondsInMonth(short year, enNumberOfDaysPerMonth month)
	{
		return howManyMinutesInMonth(year, month) * 60;
	}

	short howManySecondsInMonth()
	{
		return howManySecondsInMonth(_Year, (enNumberOfDaysPerMonth)_Month);
	}

	enum enDaysNameInWeek
	{
		Sunday = 1, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday
	};

	static string getDayName(enDaysNameInWeek dayNumber)
	{
		switch (dayNumber)
		{
		case Sunday:	return "Sunday";
		case Monday:	return "Monday";
		case Tuesday:	return "Tuesday";
		case Wednesday:	return "Wednesday";
		case Thursday:	return "Thursday";
		case Friday:	return "Friday";
		case Saturday:	return "Saturday";
		default:		return "Not Found Day";
		}
	}

	static string getDayNameInYear(short day , short month , short year)
	{
		return getDayName((enDaysNameInWeek)dayOfWeekOrder(year, month, day));
	}

	string getDayNameInYear()
	{
		return getDayName((enDaysNameInWeek)dayOfWeekOrder());
	}

	static short claculateMyAgeInDays(clsDate dateOfBirth)
	{
		return calculateDifferenceInDays(dateOfBirth, GetSystemDate() , true);
	}

	short claculateMyAgeInDays()
	{
		return claculateMyAgeInDays(*this);
	}

	static void printMonthCalendar(short year, short month)
	{
		cout << "\n ___________________________"
			<< getMonthName((enNumberOfDaysPerMonth)month)
			<< "___________________________\n\n";

		cout << setw(8) << "Sun" << setw(8) << "Mon" << setw(8) << "Tue"
				<< setw(8) << "Wed" << setw(8) << "Thu" << setw(8) << "Fri"
				<< setw(8) << "Sat" << setw(8) << "\n\n";

		short daysInMonth = howManyDaysInMonth(year, (enNumberOfDaysPerMonth)month);
		short firstDay = dayOfWeekOrder(year, month, 1);

		for (short i = 1; i < firstDay; ++i) {
			cout << setw(8) << "";
		}


		for (short day = 1; day <= daysInMonth; ++day)
		{
			cout << setw(8) << day;

			if ((firstDay + day - 1) % 7 == 0 && (day != daysInMonth)) {
				cout << endl << endl;
			}
		}
		cout << "\n _________________________________________________________\n";
	}

	void printMonthCalendar()
	{
		printMonthCalendar(_Year, _Month);
	}

	static void printYearCalendar(short year)
	{
		cout << "\n__________________________________________________________\n"
			<< "\n\t\t\tCalemdar - " << year << "\n"
			<< "__________________________________________________________\n";
		for (short i = 1; i <= 12; i++)
		{
			printMonthCalendar(year, i);
		}
	}

	void printYearCalendar()
	{
		printYearCalendar(_Year);
	}

	short getDay()
	{
		return _Day;
	}

	short getMonth()
	{
		return _Month;
	}

	short getYear()
	{
		return _Year;
	}

	short setDay(short Day)
	{
		_Day = Day;
	}

	short setMonth(short Month)
	{
		_Month = Month;
	}

	short setYear(short Year)
	{
		_Year = Year;
	}

	__declspec(property(get = getDay,	put = setDay))	 short year;
	__declspec(property(get = getMonth, put = setMonth)) short month;
	__declspec(property(get = getYear,	put = setYear))	 short day;

};

