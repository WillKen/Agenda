#include "User.hpp"

User::User()
{

}

User::User(std::string t_userName, std::string t_userPassword,std::string t_userEmail, std::string t_userPhone)
{
    m_name=t_userName;
    m_password=t_userPassword;
    m_email=t_userEmail;
    m_phone=t_userPhone;
}

User::User(const User &t_user)
{
    m_name=t_user.getName();
    m_password=t_user.getPassword();
    m_email=t_user.getEmail();
    m_phone=t_user.getPhone();_
}

std::string User::getName() const
{
    return m_name;
}

void setName(std::string t_name)
{
    m_name=t_name;
}

std::string User::getPassword() const
{
    return m_password;
}

void setPassword (std::string t_password)
{
    m_password=t_password;
}

std::string User::getEmail() const
{
    return m_email;
}

void setEmail(std::string t_email)
{
    m_email=t_email;
}

std::string User::getPhone() const
{
    return m_phone;
}

void setPhone(std::string t_phone)
{
    m_phone=t_phone;
}
