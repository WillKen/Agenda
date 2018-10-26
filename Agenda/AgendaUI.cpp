#include "AgendaUI.hpp"

using std::cout;
using std::cin;
using std::string;

AgendaUI::AgendaUI()
{
	m_userName = m_userPassword = "";
	startAgenda();
}

void AgendaUI::OperationLoop(void)
{
	while (true) {
		std::string cmd;
		cout << "\n----------------------- Agenda -------------------------------\n";
		cout << "Action :\n";
		cout << "l\t- log in by username and password.\n";
		cout << "r\t- regist a user.\n";
		cout << "q\t- quit agenda.\n";
		cout << "--------------------------------------------------------------\n";
		cout << "\nAgenda £º ~$ ";
		cin >> cmd;
		if (cmd == "q") break;
		else if (cmd == "l") 
			userLogIn();
		else if (cmd== "r") 
			userRegister();
		else { cout << "illegal command!\n"; }
	}
}

void AgendaUI::startAgenda(void)
{
	m_agendaService = AgendaService();
}

std::string AgendaUI::getOperation()
{
	std::string cmd;
	cout << "\n----------------------- Agenda -------------------------------\n"
		<< "Action :\n"
		<< "o\t- log out Agenda\n"
		<< "dc\t- delete Agenda account\n"
		<< "lu\t- list all Agenda users\n"
		<< "cm\t- create a meeting\n"
		<< "la\t- list all meetings\n"
		<< "las\t- list all sponsor meetings\n"
		<< "lap\t- list all particpator meetings\n"
		<< "qm\t- query meeting by title\n"
		<< "qt\t- query meeting by time interval\n"
		<< "dm\t- delete meeting by title\n"
		<< "da\t- delete all meetings\n"
		<< "--------------------------------------------------------------\n"
		<< "\nAgenda@" << m_userName << " : # ";
	std::cin >> cmd;
	return cmd;
}

bool AgendaUI::executeOperation(std::string t_operation)
{
	if (t_operation == "o") {
		return false;
	}
	else if (t_operation == "dc") {
		deleteUser();
		return false;
	}
	else if (t_operation == "lu") {
		listAllUsers();
		return true;
	}
	else if (t_operation == "cm") {
		createMeeting();
		return true;
	}
	else if (t_operation == "la") {
		listAllMeetings();
		return true;
	}
	else if (t_operation == "las") {
		listAllSponsorMeetings();
		return true;
	}
	else if (t_operation == "lap") {
		listAllParticipateMeetings();
		return true;
	}
	else if (t_operation == "qm") {
		queryMeetingByTitle();
		return true;
	}
	else if (t_operation == "qt") {
		queryMeetingByTimeInterval();
		return true;
	}
	else if (t_operation == "dm") {
		deleteMeetingByTitle();
		return true;
	}
	else if (t_operation == "da") {
		deleteAllMeetings();
		return true;
	}
	else {
		cout << "illegal command!\n";
		return true;
	}
}

void AgendaUI::userLogIn(void)
{
	string userName, userPassword;
	cout << "[log in] [username] [password]\n";
	cout << "[log in] ";
	cin >> userName >> userPassword;
	if (m_agendaService.userLogIn(userName, m_userPassword)) {
		m_userName = userName;
		m_userPassword = userPassword;
		cout << "[log in] succeed!\n";
		while (executeOperation(getOperation()));
	}
	else {
		cout << "[log in] log in fail!\n";
	}
}

void AgendaUI::userRegister(void)
{
	string userName, userPassword, email, phone;
	cout << "[register] [user name] [password] [email] [phone]\n";
	cout << "[register] ";
	cin >> userName >> userPassword >> email >> phone;
	if (m_agendaService.userRegister(userName, userPassword, email, phone)) {
		cout << "[user register] succeed!\n";
	}
	else {
		cout << "[register] register fail!\n";
	}
}

void AgendaUI::userLogOut(void)
{
	cout<< "[log out] succeed!\n";
	m_userName = m_userPassword = "";
}

void AgendaUI::quitAgenda(void)
{
	cout << "[quit] succeed!\n";
}

void AgendaUI::deleteUser(void)
{
	if (m_agendaService.deleteUser(m_userName, m_userPassword)){
		cout << "[delete agenda account] succeed!\n";
		m_userName = m_userPassword = "";
	}
	else {
		cout << "[delete agenda account] fail!\n";
	}
}

void AgendaUI::listAllUsers(void)
{
	std::list<User> all = m_agendaService.listAllUsers();
	cout << "[list all users]\n";
	cout << "\nname\temail\tphone\n";
	for (auto iter = all.begin(); iter != all.end(); iter++) {
		cout << (*iter).getName() << "\t";
		cout << (*iter).getEmail() << "\t";
		cout << (*iter).getPhone() << "\n";
	}
}

void AgendaUI::createMeeting(void)
{
	int num;
	std::vector<string> participators;
	string title,start,end, participatorName;
	cout << "[create meeting] [the number of participators]\n";
	cout << "[create meeting] ";
	cin >> num;
	for (int i = 1; i <= num; i++) {
		cout << "[create meeting] [please enter the participator " << i << " ]\n";
		cout << "[create meeting] ";
		cin >> participatorName;
		participators.push_back(participatorName);
	}
	cout << "[create meeting] [title] [start time(yyyy - mm - dd / hh:mm)] [end time(yyyy - mm - dd / hh:mm)]\n";
	cout << "[create meeting] ";
	cin >> title >> start >> end;
	if (m_agendaService.createMeeting(m_userName, title, start, end, participators)) {
		cout << "[create meeting] succeed!\n";
	}
	else {
		cout << "[create meeting] fail!\n";
	}
}

void AgendaUI::listAllMeetings(void)
{
	cout << "[list all meetings]\n";
	std::list<Meeting> all = m_agendaService.listAllMeetings(m_userName);
	printMeetings(all);
}

void AgendaUI::listAllSponsorMeetings(void)
{
	cout << "[list all sponsor meetings]\n\n";
	std::list<Meeting> all = m_agendaService.listAllSponsorMeetings(m_userName);
	printMeetings(all);
}

void AgendaUI::listAllParticipateMeetings(void)
{
	cout << "[list all particpator meetings]\n\n";
	std::list<Meeting> all = m_agendaService.listAllParticipateMeetings(m_userName);
	printMeetings(all);
}

void AgendaUI::queryMeetingByTitle(void)
{
	std::string title;
	cout << "[query meeting] [title]\n";
	cout<< "[query meeting] ";
	cin >> title;
	std::list<Meeting> queryTitle = m_agendaService.meetingQuery(m_userName, title);
	printMeetings(queryTitle);
}

void AgendaUI::queryMeetingByTimeInterval(void)
{
	std::string start, end;
	cout << "[query meeting] [start time(yyyy-mm-dd/hh:mm)] [end time(yyyy-mm-dd/hh:mm)]\n";
	cout<< "[query meeting] ";
	cin >> start >> end;
	std::list<Meeting> queryTime = m_agendaService.meetingQuery(m_userName, start,end);
	printMeetings(queryTime);
}

void AgendaUI::deleteMeetingByTitle(void)
{
	std::string title;
	cout << "[delete meeting] [title]\n";
	cout<< "[delete meeting] ";
	cin >> title;
	if (m_agendaService.deleteMeeting(m_userName, title)) {
		cout << "[delete meeting] succeed!\n";
	}
	else {
		cout << "[delete meeting] fail!\n";
	}
}

void AgendaUI::deleteAllMeetings(void)
{
	if (m_agendaService.deleteAllMeetings(m_userName))
		cout << "[delete meeting] succeed!\n";
	else
		cout << "[delete meeting] fail!\n";
}

void AgendaUI::printMeetings(std::list<Meeting> t_meetings)
{
	cout << "title\t\tsponsor\tstart time\t\tend time\t\tparticipators\n";
	for (auto iter = t_meetings.begin(); iter != t_meetings.end();iter++) {
		cout << (*iter).getTitle() << '\t';
		cout << (*iter).getSponsor() << '\t';
		cout << Date::dateToString((*iter).getStartDate()) << '\t';
		cout << Date::dateToString((*iter).getEndDate()) << '\t';
		std::vector<std::string> t_partic = (*iter).getParticipator();
		cout << *t_partic.begin();
		for (auto partic = t_partic.begin() + 1; partic != t_partic.end(); partic++) {
			cout << ',' << *partic;
		}
		cout << std::endl;
	}
	cout << std::endl;
}
