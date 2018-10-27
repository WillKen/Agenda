#include <iostream>
#include "Date.hpp"
#include<algorithm>

using namespace std;

bool isStringValid(const string& dateString);
bool isNum(char ele);

std::string cut(Date date) {
	std::string ele = Date::dateToString(date);
	ele.erase(std::remove(ele.begin(), ele.end(), '-'), ele.end());
	ele.erase(std::remove(ele.begin(), ele.end(), '/'), ele.end());
	ele.erase(std::remove(ele.begin(), ele.end(), ':'), ele.end());
	return ele;
}

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

Date::Date(const std::string & dateString)
{
	if (!isStringValid(dateString)) {
		m_minute = m_hour = m_day = m_month = m_year = 0;
		return;
	}
	else {
		*this = stringToDate(dateString);
	}
}

int Date::getYear(void) const
{
	return m_year;
}

void Date::setYear(const int t_year)
{
	m_year = t_year;
}

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
	if (t_minute >= 0 && t_minute <= 60)
		m_minute = t_minute;
}

bool Date::isValid(const Date & t_date)
{
	int year = t_date.getYear();
	int month = t_date.getMonth();
	int day = t_date.getDay();
	int hour = t_date.getHour();
	int minute = t_date.getMinute();
	if (year < 1000 || year > 9999 || day <= 0 || hour < 0 || hour >= 24 || minute < 0 || minute >= 60)
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
		else
			return true;
		break;
	case 4:
	case 6:
	case 9:
	case 11:
		if (day > 30)
			return false;
		else
			return true;
		break;
	case 2:
		if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
			if (day > 29)
				return false;
			else
				return true;
		}
		else {
			if (day > 28)
				return false;
			else
				return true;
		}
		break;
	default:
		return false;
		break;
	}
	return true;
}

Date Date::stringToDate(const std::string & t_dateString)
{
	Date notValid;
	Date Valid;
	if (!isStringValid(t_dateString))
		return Valid;
	int data = 0;
	try {
		for (int i = 0; i < 4; i++) {
			data += (t_dateString[i] - '0');
			data *= 10;
		}
		data /= 10;
		Valid.setYear(data);
		data = 0;
		for (int i = 5; i < 7; i++) {
			data += (t_dateString[i] - '0');
			data *= 10;
		}
		data /= 10;
		Valid.setMonth(data);
		data = 0;
		for (int i = 8; i < 10; i++) {
			data += (t_dateString[i] - '0');
			data *= 10;
		}
		data /= 10;
		Valid.setDay(data);
		data = 0;
		for (int i = 11; i < 13; i++) {
			data += (t_dateString[i] - '0');
			data *= 10;
		}
		data /= 10;
		Valid.setHour(data);
		data = 0;
		for (int i = 14; i < 16; i++) {
			data += (t_dateString[i] - '0');
			data *= 10;
		}
		data /= 10;
		Valid.setMinute(data);
		if (isValid(Valid))
			return Valid;
		else
			return notValid;
	}
	catch (exception) {
		return notValid;
	}
}

std::string Date::dateToString(const Date & t_date)
{
	int ele;
	std::string date = "";
	if (!isValid(t_date)) {
		date = "0000-00-00/00:00";
		return date;
	}
	date += std::to_string(t_date.getYear());
	date += "-";
	ele = t_date.getMonth();
	if (ele < 10)
		date += "0";
	date += std::to_string(ele);
	date += "-";
	ele = t_date.getDay();
	if (ele < 10)
		date += "0";
	date += std::to_string(ele);
	date += "/";
	ele = t_date.getHour();
	if (ele < 10)
		date += "0";
	date += std::to_string(ele);
	date += ":";
	ele = t_date.getMinute();
	if (ele < 10)
		date += "0";
	date += std::to_string(ele);
	return date;
}

Date & Date::operator=(const Date & t_date)
{
	this->setYear(t_date.getYear());
	this->setMonth(t_date.getMonth());
	this->setDay(t_date.getDay());
	this->setHour(t_date.getHour());
	this->setMinute(t_date.getMinute());
	return *this;
}

bool Date::operator==(const Date & t_date) const
{
	string date1 = cut(*this);
	string date2 = cut(t_date);
	if (date1 == date2)
		return true;
	else
		return false;
}

bool Date::operator>(const Date & t_date) const
{
	string date1 = cut(*this);
	string date2 = cut(t_date);
	if (date1 > date2)
		return true;
	else
		return false;
}

bool Date::operator<(const Date & t_date) const
{
	string date1 = cut(*this);
	string date2 = cut(t_date);
	if (date1 < date2)
		return true;
	else
		return false;
}

bool Date::operator>=(const Date & t_date) const
{
	string date1 = cut(*this);
	string date2 = cut(t_date);
	if (date1 >= date2)
		return true;
	else
		return false;
}

bool Date::operator<=(const Date & t_date) const
{
	string date1 = cut(*this);
	string date2 = cut(t_date);
	if (date1 <= date2)
		return true;
	else
		return false;
}

bool isStringValid(const string& dateString)
{
	if (dateString.length() != 16)return false;
	if (!isNum(dateString[0])) return false;
	if (!isNum(dateString[1])) return false;
	if (!isNum(dateString[2])) return false;
	if (!isNum(dateString[3])) return false;
	if (dateString[4] != '-') return false;
	if (!isNum(dateString[5])) return false;
	if (!isNum(dateString[6])) return false;
	if (dateString[7] != '-') return false;
	if (!isNum(dateString[8])) return false;
	if (!isNum(dateString[9])) return false;
	if (dateString[10] != '/') return false;
	if (!isNum(dateString[11])) return false;
	if (!isNum(dateString[12])) return false;
	if (dateString[13] != ':') return false;
	if (!isNum(dateString[14])) return false;
	if (!isNum(dateString[15])) return false;
	return true;
}
bool isNum(char ele) {
	if (ele <= '9' && ele >= '0') 
		return true;
	else
		return false;
}