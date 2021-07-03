#ifndef WRAPPER_H
#define WRAPPER_H

#include "database.h"
#include "account.h"
#include "mail.h"

// Limits the Loading of Mails
enum {MAIL_PER_PAGE=10};

// Error Class
class InputError
{
	std::string message;
public:
	InputError(const std::string& message);
	std::string getMessage() const;
};

class SigninError
{
	std::string message;
public:
	SigninError(const std::string& message);
	std::string getMessage() const;
};

// Wrapper Class (API) for the EMail Operations
class Wrapper
{
	// Member Variables
	Database d;
	Account *current;
	
	// Verification of Inputs
	void verifyUser(const std::string& user) const throw(InputError);
	void verifyPhone(const std::string& phone) const throw(InputError);
	void verifyDob(const std::string& dob) const throw(InputError);
	
public:
	// Constructor
	Wrapper();
	// Destructor
	~Wrapper();
	
	// Basic Operations
	Account getAccount() const;
	void registerAccount(const std::string& user, const std::string& pass, const std::string& name,
	                    const std::string& phone, const std::string& dob) const throw(InputError, AccountError);
	
	void signin(const std::string& user, const std::string& pass) throw(SigninError);
	void signout();
	
	// Change Details
	void changeName(const std::string& name) throw(InputError);
	void changePhone(const std::string& phone) throw(InputError);
	void changeDob(const std::string& dob) throw(InputError);
	void changePass(const std::string& oldPass, const std::string& newPass) throw(InputError, SigninError);
	
	// Mail Operations
	void writeMail(const std::string& sub, const std::string& to, const std::string& content) const;
	
	std::vector<Mail> readInbox(int page) const;
	std::vector<Mail> readOutbox(int page) const;
};

#endif

