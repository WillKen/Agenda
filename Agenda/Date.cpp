#include <iostream>
#include "Date.hpp"

using namespace std;

Date::Date()
{

}


Date::Date(int t_year, int t_month, int t_day, int t_hour, int t_minute)
{
    m_year=t_year;
    m_month=t_month;
    m_day=t_day;
    m_hour=t_hour;
    m_minute=t_minute;
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
void Date::setYear(const int t_year) {

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
    m_month=t_month;
}

int Date::getDay(void) const
{
    return m_day;
}

void Date::setDay(const int t_day)
{
    m_day=t_day;
}

int Date::getHour(void) const
{
    return m_hour;
}

void Date::setHour(const int t_hour)
{
    m_hour=t_hour;
}

int Date::getMinute(void) const
{
    return m_minute;
}

void Date::setMinute(const int t_minute)
{
    m_minute=t_minute;
}

bool Date::isValid(const Date t_date)
{

}
  /**
  * @brief convert a string to date, if the format is not correct return
  * 0000-00-00/00:00
  * @return a date
  */
Date Date::stringToDate(const std::string t_dateString)
{

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
