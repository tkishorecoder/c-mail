#include "account.h"

#include <iomanip>
#include <string>
#include <sstream>
#include <ctime>

// Date and Time functionalities
std::string Account::getCurrentDate() const
{
	time_t now = time(NULL);
	struct tm *t = localtime(&now);
	
	std::ostringstream res;
	
	res << std::setfill('0') << std::setw(2) << (t->tm_mday) << '-'
	    << std::setfill('0') << std::setw(2) << (1+t->tm_mon) << '-'
		<< std::setfill('0') << std::setw(4) << (1900+t->tm_year);
	
	return res.str();
}

// Constructor
Account::Account(const std::string& user, const std::string& pass, const std::string& name,
        const std::string& phone, const std::string& dob)
{
	this->user = user;
	this->pass = pass;
	this->name = name;
	this->phone = phone;
	this->dob = dob;
	this->regdate = getCurrentDate();
}
Account::Account(const std::string& user, const std::string& pass, const std::string& name,
        const std::string& phone, const std::string& dob, const std::string& regdate)
{
	this->user = user;
	this->pass = pass;
	this->name = name;
	this->phone = phone;
	this->dob = dob;
	this->regdate = regdate;
}

// Setters
void Account::setPass(const std::string& oldPass, const std::string& newPass) throw(PassError) {
	if (pass.compare(oldPass) == 0)
		this->pass = newPass;
	else
		throw PassError();
}
void Account::setName(const std::string& name) {
	this->name = name;
}
void Account::setPhone(const std::string& phone) {
	this->phone = phone;
}
void Account::setDob(const std::string& dob) {
	this->dob = dob;
}

// Getters
std::string Account::getUser() const {
	return this->user;
}
std::string Account::getPass() const {
	return this->pass;
}
std::string Account::getName() const {
	return this->name;
}
std::string Account::getPhone() const {
	return this->phone;
}
std::string Account::getDob() const {
	return this->dob;
}
std::string Account::getRegdate() const {
	return this->regdate;
}

