#ifndef MAIL_H
#define MAIL_H

#include <string>

// Data Structure (Class) for Mails
class Mail
{
	// Member variables
	std::string sub;
	std::string from;
	std::string to;
	std::string content;
	std::string when;
	
	// Date and Time functionalities
	std::string getCurrentDateTime() const;

public:
	// Constructor
	Mail(const std::string& sub, const std::string& from, const std::string& to,
	     const std::string& content);
	Mail(const std::string& sub, const std::string& from, const std::string& to,
	    const std::string& content, const std::string& when);
	
	// Getters
	std::string getSub() const;
	std::string getFrom() const;
	std::string getTo() const;
	std::string getContent() const;
	std::string getWhen() const;
};

#endif

