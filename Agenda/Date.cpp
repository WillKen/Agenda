#include <iostream>
#include "Date.hpp"

using namespace std;

Date::Date()
{

}


Date(int t_year, int t_month, int t_day, int t_hour, int t_minute)
{
    m_year=t_year;
    m_month=t_month;
    m_day=t_day;
    m_hour=t_hour;
    m_minute=t_minute;
}

Date(std::string dateString)
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
  void setYear(const int t_year);

  /**
  * @brief return the month of a Date
  * @return   a integer indicate the month of a date
  */
int Meeting::getMonth(void) const
{
    return m_month;
}

void Meeting::setMonth(const int t_month)
{
    m_month=t_month;
}

int Meeting::getDay(void) const
{
    return m_day;
}

void setDay(const int t_day)
{
    m_day=t_day;
}

int Meeting::getHour(void) const
{
    return m_hour;
}

void Meeting::setHour(const int t_hour)
{
    m_hour=t_hour;
}

int Meeting::getMinute(void) const
{
    return m_minute;
}

void Meeting::setMinute(const int t_minute)
{
    m_minute=t_minute;
}

static bool Meeting::isValid(const Date t_date)
{

}
  /**
  * @brief convert a string to date, if the format is not correct return
  * 0000-00-00/00:00
  * @return a date
  */
  static Date stringToDate(const std::string t_dateString);

  /**
  * @brief convert a date to string, if the format is not correct return
  * 0000-00-00/00:00
  */
  static std::string dateToString(Date t_date);

  /**
  *  @brief overload the assign operator
  */
  Date &operator=(const Date &t_date);

  /**
  * @brief check whether the CurrentDate is equal to the t_date
  */
  bool operator==(const Date &t_date) const;

  /**
  * @brief check whether the CurrentDate is  greater than the t_date
  */
  bool operator>(const Date &t_date) const;

  /**
  * @brief check whether the CurrentDate is  less than the t_date
  */
  bool operator<(const Date &t_date) const;

  /**
  * @brief check whether the CurrentDate is  greater or equal than the t_date
  */
  bool operator>=(const Date &t_date) const;

  /**
  * @brief check whether the CurrentDate is  less than or equal to the t_date
  */
  bool operator<=(const Date &t_date) const;
/*
private:
  int m_year;
  int m_month;
  int m_day;
  int m_hour;
  int m_minute;*/
