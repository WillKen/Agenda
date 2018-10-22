#include "Meeting.hpp"
#include "Date.hpp"
#include <algorithm>

Meeting::Meeting(const std::string & t_sponsor, const std::vector<std::string>& t_participator, const Date & t_startTime, const Date & t_endTime, const std::string & t_title)
{
	m_sponsor = t_sponsor;
	m_participators = t_participator;
	m_startDate = t_startTime;
	m_endDate = t_endTime;
	m_title = t_title;
}

Meeting::Meeting(const Meeting &t_meeting)
{
	m_sponsor = t_meeting.getSponsor();
	m_participators = t_meeting.getParticipator();
	m_startDate = t_meeting.getStartDate();
	m_endDate = t_meeting.getEndDate();
	m_title = t_meeting.getTitle();
}

std::string Meeting::getSponsor(void) const
{
	return m_sponsor;
}

void Meeting::setSponsor(const std::string & t_sponsor)
{
	m_sponsor = t_sponsor;
}

std::vector<std::string>  Meeting::getParticipator(void) const
{
	return m_participators;
}

void Meeting::setParticipator(const std::vector<std::string>& t_participators)
{
	m_participators = t_participators;
}

void Meeting::addParticipator(const std::string & t_participator)
{
	for (auto iter = m_participators.begin(); iter != m_participators.end(); iter++) {
		if (*iter == t_participator)
			return;
	}
	m_participators.push_back(t_participator);
}

void Meeting::removeParticipator(const std::string & t_participator)
{
	for (auto iter = m_participators.begin(); iter != m_participators.end(); iter++) {
		if (*iter == t_participator) {
			m_participators.erase(iter);
			return;
		}
	}
}


Date Meeting::getStartDate(void) const
{
	return m_startDate;
}

void Meeting::setStartDate(const Date & t_startTime)
{
	m_startDate = t_startTime;
}

Date Meeting::getEndDate(void) const
{
	return m_endDate;
}

void Meeting::setEndDate(const Date & t_endTime)
{
	m_endDate = t_endTime;
}

std::string Meeting::getTitle(void) const
{
	return m_title;
}

void Meeting::setTitle(const std::string & t_title)
{
	m_title = t_title;
}

bool Meeting::isParticipator(const std::string & t_username) const
{
	auto obj = std::find(m_participators.begin(), m_participators.end(), t_username);
	return (obj != m_participators.end());
}