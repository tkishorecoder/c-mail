#include "mail.h"

#include <iomanip>
#include <string>
#include <sstream>
#include <ctime>

// Date and Time functionalities
std::string Mail::getCurrentDateTime() const
{
	time_t now = time(NULL);
	struct tm *t = localtime(&now);
	
	std::ostringstream res;
	
	res << std::setfill('0') << std::setw(2) << (t->tm_mday) << '-'
	    << std::setfill('0') << std::setw(2) << (1+t->tm_mon) << '-'
		<< std::setfill('0') << std::setw(4) << (1900+t->tm_year) << ' '
		<< std::setfill('0') << std::setw(2) << (t->tm_hour) << ':'
		<< std::setfill('0') << std::setw(2) << (t->tm_min);
	
	return res.str();
}

// Constructor
Mail::Mail(const std::string& sub, const std::string& from, const std::string& to,
           const std::string& content)
{
	this->sub = sub;
	this->from = from;
	this->to = to;
	this->content = content;
	this->when = getCurrentDateTime();	
}
Mail::Mail(const std::string& sub, const std::string& from, const std::string& to,
           const std::string& content, const std::string& when)
{
	this->sub = sub;
	this->from = from;
	this->to = to;
	this->content = content;
	this->when = when;
}

// Getters
std::string Mail::getSub() const {
	return this->sub;
}
std::string Mail::getFrom() const {
	return this->from;
}
std::string Mail::getTo() const {
	return this->to;
}
std::string Mail::getContent() const {
	return this->content;
}
std::string Mail::getWhen() const {
	return this->when;
}

