#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>

// Data Structure (Class) for Accounts
class Account
{
	// Member variables
	std::string user;
	std::string pass;
	std::string name;
	std::string phone;
	std::string dob;
	std::string regdate;
	
	// Date and Time functionalities
	std::string getCurrentDate() const;
	
	// Error Class
	class PassError { };
	
public:
	// Constructor
	Account(const std::string& user, const std::string& pass, const std::string& name,
	        const std::string& phone, const std::string& dob);
	Account(const std::string& user, const std::string& pass, const std::string& name,
	        const std::string& phone, const std::string& dob, const std::string& regdate);
	
	// Setters
	void setPass(const std::string& oldPass, const std::string& newPass) throw(PassError);
	void setName(const std::string& name);
	void setPhone(const std::string& phone);
	void setDob(const std::string& dob);
	
	// Getters
	std::string getUser() const;
	std::string getPass() const;
	std::string getName() const;
	std::string getPhone() const;
	std::string getDob() const;
	std::string getRegdate() const;
};

#endif

