#include <iostream>
#include "Date.hpp"

using namespace std;

Date::Date()
{
	m_year = m_month = m_day = m_hour = m_minute = 0;
}

Date::Date(int t_year, int t_month, int t_day, int t_hour, int t_minute)
{
	m_year = t_year;
	m_month = t_month;
	m_day = t_day;
	m_hour = t_hour;
	m_minute = t_minute;
}

Date::Date(std::string dateString)
{

}

int Date::getYear(void) const
{
	return m_year;
}

/**
* @brief set the year of a date
* @param a integer indicate the new year of a date
*/
void Date::setYear(const int t_year)
{
	m_year = t_year;
}

/**
* @brief return the month of a Date
* @return   a integer indicate the month of a date
*/
int Date::getMonth(void) const
{
	return m_month;
}

void Date::setMonth(const int t_month)
{
	m_month = t_month;
}

int Date::getDay(void) const
{
	return m_day;
}

void Date::setDay(const int t_day)
{
	m_day = t_day;
}

int Date::getHour(void) const
{
	return m_hour;
}

void Date::setHour(const int t_hour)
{
	m_hour = t_hour;
}

int Date::getMinute(void) const
{
	return m_minute;
}

void Date::setMinute(const int t_minute)
{
	m_minute = t_minute;
}

bool Date::isValid(const Date t_date)
{
	int year = t_date.getYear();
	int month = t_date.getMonth();
	int day = t_date.getDay();
	int hour = t_date.getHour();
	int minute = t_date.getMinute();
	if (year < 1000 || year > 9999 || day < 0 || hour < 0 || hour > 24 || minute < 0 || minute > 60)
		return false;
	switch (month) {
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		if (day > 31)
			return false;
		break;
	case 4:
	case 6:
	case 9:
	case 11:
		if (day > 31)
			return false;
		break;
	case 2:
		if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
			if (day > 29)
				return false;
		}
		else {
			if (day > 28)
				return false;
		}
		break;
	default:
		return false;
		break;
	}
	return true;
}

Date Date::stringToDate(const std::string t_dateString)
{
	Date notValid;
	Date Valid;
	int data=0;
	for (int i = 0; i < 4; i++) {
		data += t_dateString[i];
		data *= 10;
	}
	data /= 10;
	Valid.setYear(data);
	for (int i = 5; i < 7; i++) {
		data += t_dateString[i];
		data * 10;
	}
	data /= 10;
	Valid.setMonth(data);
	for (int i = 8; i < 10; i++) {
		data += t_dateString[i];
		data * 10;
	}
	data /= 10;
	Valid.setDay(data);


}

/**
* @brief convert a date to string, if the format is not correct return
* 0000-00-00/00:00
*/
std::string Date::dateToString(Date t_date)
{

}



/**
*  @brief overload the assign operator
*/
Date & Date::operator=(const Date & t_date)
{
	// TODO: 在此处插入 return 语句
}

bool Date::operator==(const Date & t_date) const
{
	return false;
}

bool Date::operator>(const Date & t_date) const
{
	return false;
}

bool Date::operator<(const Date & t_date) const
{
	return false;
}

bool Date::operator>=(const Date & t_date) const
{
	return false;
}

bool Date::operator<=(const Date & t_date) const
{
	return false;
}
