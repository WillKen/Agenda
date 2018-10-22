#include"Storage.hpp"
#include"Path.hpp"
#include<fstream>
#include<algorithm>
#include<string>
#include<cstring>

std::shared_ptr<Storage> m_instance = nullptr;

std::string cut(std::string str) {
	str.erase(std::remove(str.begin(), str.end(), '\"'), str.end());
}

std::string add(std::string str) {
	std::string temp = "\"";
	temp += str;
	temp += "\"";
	return temp;
}

bool Storage::readFromFile(void)
{
	std::ifstream userFile(Path::userPath);
	if (!userFile.is_open())
		return false;
	while (!userFile.eof()) {
		std::string name, password, email, phone;
		getline(userFile, name, ',');
		getline(userFile, password, ',');
		getline(userFile, email, ',');
		getline(userFile, phone, '\n');
		m_userList.push_back(User(name, password, email, phone));
	}
	userFile.close();

	std::ifstream meetingFile(Path::meetingPath);
	if (!meetingFile.is_open())
		return false;
	while (!meetingFile.eof()) {
		std::string sponsor,participator, start, end, title;
		getline(meetingFile, sponsor, ',');
		sponsor = cut(sponsor);
		getline(meetingFile, participator, ',');
		participator = cut(participator);
		getline(meetingFile, start, ',');
		start = cut(start);
		getline(meetingFile, end, ',');
		end = cut(end);
		getline(meetingFile, title, '\n');
		title = cut(title);
		Date startDate(start);
		Date endDate(end);
		std::string temp;
		temp= participator.find("&");
		std::vector<std::string> participators;
		participators.push_back(participator);
		m_meetingList.push_back(Meeting(sponsor, participators,startDate, endDate, title));
	}
	meetingFile.close();
	return true;
}

bool Storage::writeToFile(void)
{
	std::ofstream userFile(Path::userPath);
	if (!userFile.is_open())
		return false;
	for (auto iter = m_userList.begin(); iter != m_userList.end(); iter++) {
		userFile << "\"" << iter->getName() << "\",";
		userFile << "\"" << iter->getPassword() << "\",";
		userFile << "\"" << iter->getEmail() << "\",";
		userFile << "\"" << iter->getPhone() << "\"\n";
	}
	userFile.close();
	std::ofstream meetingFile(Path::meetingPath);
	if (!meetingFile.is_open())
		return false;
	for (auto iter = m_meetingList.begin(); iter != m_meetingList.end(); iter++) {
		meetingFile << "\"" << iter->getSponsor() << "\",";
		meetingFile << "\"" <<"\",";
		meetingFile << "\"" << Date::dateToString(iter->getStartDate()) << "\",";
		meetingFile << "\"" << Date::dateToString(iter->getEndDate()) << "\",";
		meetingFile << "\"" << iter->getTitle() << "\"\n";
	}
	meetingFile.close();
	return true;
}

std::shared_ptr<Storage> Storage::getInstance(void)
{
	if (m_instance == nullptr) {
		 std::shared_ptr<Storage> temp(new Storage);
		 m_instance = temp;
	}
	return m_instance;
}

Storage::~Storage()
{
	sync();
}

void Storage::createUser(const User & t_user)
{
	m_userList.push_back(t_user);
}

std::list<User> Storage::queryUser(std::function<bool(const User&)> filter) const
{
	std::list<User> user;
	for (auto iter = m_userList.begin(); iter != m_userList.end(); iter++) {
		if (filter(*iter)) {
			user.push_back(*iter);
		}
	}
	return user;
}

int Storage::updateUser(std::function<bool(const User&)> filter, std::function<void(User&)> switcher)
{
	int count = 0;
	for (auto iter = m_userList.begin(); iter != m_userList.end(); iter++) {
		if (filter(*iter)) {
			switcher(*iter);
			count++;
		}
	}
	return count;
}

int Storage::deleteUser(std::function<bool(const User&)> filter)
{
	int count = 0;
	for (auto iter = m_userList.begin(); iter != m_userList.end(); ) {
		if (filter(*iter)) {
			iter = m_userList.erase(iter);
			count++;
		}
		else {
			iter++;
		}
	}
	return count;
}

void Storage::createMeeting(const Meeting & t_meeting)
{
	m_meetingList.push_back(t_meeting);
}

std::list<Meeting> Storage::queryMeeting(std::function<bool(const Meeting&)> filter) const
{
	std::list<Meeting> meeting;
	for (auto iter = m_meetingList.begin(); iter != m_meetingList.end(); iter++) {
		if (filter(*iter)) {
			meeting.push_back(*iter);
		}
	}
	return meeting;
}

int Storage::updateMeeting(std::function<bool(const Meeting&)> filter, std::function<void(Meeting&)> switcher)
{
	int count = 0;
	for (auto iter = m_meetingList.begin(); iter != m_meetingList.end(); iter++) {
		if (filter(*iter)) {
			switcher(*iter);
			count++;
		}
	}
	return count;
}

int Storage::deleteMeeting(std::function<bool(const Meeting&)> filter)
{
	int count = 0;
	for (auto iter = m_meetingList.begin(); iter != m_meetingList.end(); ) {
		if (filter(*iter)) {
			iter = m_meetingList.erase(iter);
			count++;
		}
		else {
			iter++;
		}
	}
	return count;
}

bool Storage::sync(void)
{
	return writeToFile();
}
