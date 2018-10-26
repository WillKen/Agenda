#include "AgendaService.hpp"
#include<set>

AgendaService::AgendaService()
{
	startAgenda();
}

AgendaService::~AgendaService()
{
	quitAgenda();
}

bool AgendaService::userLogIn(const std::string & userName, const std::string & password)
{
	std::list<User> check = m_storage->queryUser([userName, password](const User &user)->bool {
		if (user.getName() == userName && user.getPassword() == password)
			return true;
		else
			return false;
	});
	if (check.size() == 1)
		return true;
	else
		return false;
}

bool AgendaService::userRegister(const std::string & userName, const std::string & password, const std::string & email, const std::string & phone)
{
	std::list<User> regist = m_storage->queryUser([userName](const User &user)->bool {
		if (user.getName() == userName)
			return true;
		else
			return false;
	});
	if (regist.size() != 0)
		return false;
	else {
		m_storage->createUser(User(userName, password, email, phone));
		return true;
	}
}

bool AgendaService::deleteUser(const std::string & userName, const std::string & password)
{
	std::list<User> dele = m_storage->queryUser([userName, password](const User& user)->bool {
		if (user.getName() == userName && user.getPassword() == password)
			return true;
		else
			return false;
	});
	if (dele.size() == 0)
		return false;
	else {
		bool quit;
		bool dele;
		std::vector<std::string> title;
		deleteAllMeetings(userName);
		m_storage->updateMeeting([userName, &quit](const Meeting&meeting)->bool {
			if (meeting.isParticipator(userName)) {
				quit = true;
				return true;
			}
			else
				return false;
		}, [userName, &dele, &title](Meeting &meeting)->void {
			meeting.removeParticipator(userName);
			if (meeting.getParticipator().size() == 0) {
				dele = true;
				title.push_back(meeting.getTitle());
			}
		});
		if (dele == true) {
			for (auto iter = title.begin(); iter != title.end(); iter++) {
				m_storage->deleteMeeting([&iter](const Meeting &meeting)->bool {
					if (meeting.getTitle() == *iter)
						return true;
					else
						return false;
				});
			}
		}
	}
	return true;
}

std::list<User> AgendaService::listAllUsers(void) const
{
	std::list<User> all = m_storage->queryUser([](const User &user)->bool {
		return true;
	});
	return all;
}

bool AgendaService::createMeeting(const std::string & userName, const std::string & title, const std::string & startDate, const std::string & endDate, const std::vector<std::string>& participator)
{
	if (!Date::isValid(Date::stringToDate(startDate)) || !Date::isValid(Date::stringToDate(endDate)))
		return false;
	if (startDate == endDate)
		return false;
	if (participator.size() == 0)
		return false;
	std::list<Meeting> titleCheck = m_storage->queryMeeting([title](const Meeting &meeting)->bool {
		if (meeting.getTitle() == title)
			return true;
		else
			return false;
	});
	if (titleCheck.size() != 0)
		return false;
	std::set<std::string> repeat;
	std::list<Meeting> userCheck = m_storage->queryMeeting([userName, startDate, endDate](const Meeting &meeting)->bool {
		if (((meeting.getSponsor() == userName) || meeting.isParticipator(userName))
			&& ((meeting.getStartDate() <= startDate && meeting.getEndDate() >= endDate)
				|| (meeting.getStartDate() > startDate && meeting.getStartDate() < endDate)
				|| meeting.getEndDate() > startDate && meeting.getEndDate() < endDate))
			return true;
		else
			return false;
	});
	if (userCheck.size() != 0)
		return false;
	repeat.insert(userName);
	for (auto iter = participator.begin(); iter != participator.end(); iter++) {
		std::list<User> user = m_storage->queryUser([&iter](const User &user)->bool {
			if (user.getName() == *iter)
				return true;
			else
				return false;
		});
		if (user.size() == 0) 
			return false;
		repeat.insert(*iter);
		std::list<Meeting> overLap = m_storage->queryMeeting([&iter, startDate, endDate](const Meeting &meeting)->bool {
			if (((meeting.getSponsor() == *iter) || meeting.isParticipator(*iter))
				&& ((meeting.getStartDate() <= startDate && meeting.getEndDate() >= endDate)
					|| (meeting.getStartDate() > startDate && meeting.getStartDate() < endDate)
					|| meeting.getEndDate() > startDate && meeting.getEndDate() < endDate))
				return true;
			else
				return false;
		});
		if (overLap.size() != 0)
			return false;
	}
	if (repeat.size() != (participator.size()+1))
		return false;
	Meeting newMeeting(userName, participator, startDate, endDate, title);
	m_storage->createMeeting(newMeeting);
	return true;
}

bool AgendaService::addMeetingParticipator(const std::string & userName, const std::string & title, const std::string & participator)
{
	std::list<Meeting> addM = m_storage->queryMeeting([userName, title, participator](const Meeting &meeting)->bool {
		if (meeting.getSponsor() == userName && meeting.getTitle() == title && (!meeting.isParticipator(participator)))
			return true;
		else
			return false;
	});
	if (addM.size() != 1)
		return false;
	Date start = addM.begin()->getStartDate();
	Date end = addM.begin()->getEndDate();
	
	std::list<User> addP = m_storage->queryUser([participator](const User &user)->bool {
		if (user.getName() == participator)
			return true;
		else
			return false;
	});
	if (addP.size() == 0)
		return false;

	std::list<Meeting> date = m_storage->queryMeeting([participator](const Meeting &meeting)->bool {
		if (meeting.getSponsor() == participator || meeting.isParticipator(participator))
			return true;
		else
			return false;
	});
	std::string startDate = Date::dateToString(start);
	std::string endDate = Date::dateToString(end);
	std::list<Meeting> overLap = m_storage->queryMeeting([participator, startDate, endDate](const Meeting &meeting)->bool {
		if (((meeting.getSponsor() == participator) || meeting.isParticipator(participator))
			&& ((meeting.getStartDate() <= startDate && meeting.getEndDate() >= endDate)
				|| (meeting.getStartDate() > startDate && meeting.getStartDate() < endDate)
				|| meeting.getEndDate() > startDate && meeting.getEndDate() < endDate))
			return true;
		else
			return false;
	});
	if (overLap.size()!=0)
		return false;
	else {
		m_storage->updateMeeting([title](const Meeting &meeting)->bool {
			if (meeting.getTitle() == title)
				return true;
			else
				return false;
		}, [participator](Meeting &meeting)->void {
			meeting.addParticipator(participator);
		});
		return true;
	}
}

bool AgendaService::removeMeetingParticipator(const std::string & userName, const std::string & title, const std::string & participator)
{
	bool remove = false;
	bool dele = false;
	m_storage->updateMeeting([userName, title, participator, &remove](const Meeting &meeting)->bool {
		if (meeting.getSponsor() == userName && meeting.getTitle() == title && meeting.isParticipator(participator)) {
			remove = true;
			return true;
		}
		else
			return false;
	}, [participator, &dele](Meeting &meeting)->void {
		meeting.removeParticipator(participator);
		if (meeting.getParticipator().size() == 0)
			dele = true;
	});
	if (dele == true) {
		m_storage->deleteMeeting([title](const Meeting &meeting)->bool {
			if (meeting.getTitle() == title)
				return true;
			else
				return false;
		});
	}
	return remove;
}

bool AgendaService::quitMeeting(const std::string & userName, const std::string & title)
{
	bool quit = false;
	bool dele = false;
	m_storage->updateMeeting([userName, title, &quit](const Meeting&meeting)->bool {
		if (meeting.getTitle() == title && meeting.isParticipator(userName)) {
			quit = true;
			return true;
		}
		else
			return false;
	}, [userName, title, &dele](Meeting &meeting)->void {
		meeting.removeParticipator(userName);
		if (meeting.getParticipator().size() == 0) {
			dele = true;
		}
	});
	if (dele == true) {
		m_storage->deleteMeeting([title](const Meeting &meeting)->bool {
			if (meeting.getTitle() == title)
				return true;
			else
				return false;
		});
	}
	return remove;
}

std::list<Meeting> AgendaService::meetingQuery(const std::string & userName, const std::string & title) const
{
	std::list<Meeting> query = m_storage->queryMeeting([userName, title](const Meeting &meeting)->bool {
		if ((meeting.getSponsor() == userName || meeting.isParticipator(userName)) && meeting.getTitle() == title)
			return true;
		else
			return false;
	});
	return query;
}

std::list<Meeting> AgendaService::meetingQuery(const std::string & userName, const std::string & startDate, const std::string & endDate) const
{
	std::list<Meeting> query = m_storage->queryMeeting([userName, startDate, endDate](const Meeting &meeting)->bool {
		if (((meeting.getSponsor() == userName) || meeting.isParticipator(userName))
			&& ((meeting.getStartDate() <= startDate && meeting.getEndDate() >= endDate)
				|| (meeting.getStartDate() >= startDate && meeting.getStartDate() <= endDate)
				|| meeting.getEndDate() >= startDate && meeting.getEndDate() <= endDate))
			return true;
		else
			return false;
	});
	return query;
}

std::list<Meeting> AgendaService::listAllMeetings(const std::string & userName) const
{
	std::list<Meeting> all = m_storage->queryMeeting([userName](const Meeting &meeting)->bool {
		if (meeting.getSponsor() == userName || meeting.isParticipator(userName))
			return true;
		else
			return false;
	});
	return all;
}

std::list<Meeting> AgendaService::listAllSponsorMeetings(const std::string & userName) const
{
	std::list<Meeting> all = m_storage->queryMeeting([userName](const Meeting &meeting)->bool {
		if (meeting.getSponsor() == userName)
			return true;
		else
			return false;
	});
	return all;
}

std::list<Meeting> AgendaService::listAllParticipateMeetings(const std::string & userName) const
{
	std::list<Meeting> all = m_storage->queryMeeting([userName](const Meeting &meeting)->bool {
		return (meeting.isParticipator(userName));
	});
	return all;
}

bool AgendaService::deleteMeeting(const std::string & userName, const std::string & title)
{
	int dele = m_storage->deleteMeeting([userName, title](const Meeting &meeting)->bool {
		if (meeting.getSponsor() == userName && meeting.getTitle() == title)
			return true;
		else
			return false;
	});
	return dele;
}

bool AgendaService::deleteAllMeetings(const std::string & userName)
{
	int dele = m_storage->deleteMeeting([userName](const Meeting &meeting)->bool {
		if (meeting.getSponsor() == userName)
			return true;
		else
			return false;
	});
	return dele;
}

void AgendaService::startAgenda(void)
{
	m_storage = Storage::getInstance();
}

void AgendaService::quitAgenda(void)
{
	m_storage->sync();
}