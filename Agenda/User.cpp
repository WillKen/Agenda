#include "User.hpp"

User::User(const std::string & t_userName, const std::string & t_userPassword, const std::string & t_userEmail, const std::string & t_userPhone)
{
	m_name = t_userName;
	m_password = t_userPassword;
	m_email = t_userEmail;
	m_phone = t_userPhone;
}

User::User(const User &t_user)
{
	m_name = t_user.getName();
	m_password = t_user.getPassword();
	m_email = t_user.getEmail();
	m_phone = t_user.getPhone();
}

std::string User::getName() const
{
	return m_name;
}

void User::setName(const std::string & t_name)
{
	m_name = t_name;
}

std::string User::getPassword() const
{
	return m_password;
}

void User::setPassword(const std::string & t_password)
{
	m_password = t_password;
}

std::string User::getEmail() const
{
	return m_email;
}

void User::setEmail(const std::string & t_email)
{
	m_email = t_email;
}

std::string User::getPhone() const
{
	return m_phone;
}

void User::setPhone(const std::string & t_phone)
{
	m_phone = t_phone;
}