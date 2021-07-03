#include "wrapper.h"

#include <cstdlib>

// Error Class
InputError::InputError(const std::string& message) {
	this->message = message;
}
std::string InputError::getMessage() const {
	return this->message;
}

SigninError::SigninError(const std::string& message) {
	this->message = message;
}
std::string SigninError::getMessage() const {
	return this->message;
}

// Constructor
Wrapper::Wrapper()
{
	this->d = Database();
	this->current = NULL;
}
// Destructor
Wrapper::~Wrapper()
{
	if (this->current != NULL)
		delete this->current;
	
	this->current = NULL;
}

// Basic Operations
Account Wrapper::getAccount() const
{
	return Account(*current);
}

void Wrapper::registerAccount(const std::string& user, const std::string& pass, const std::string& name,
	                          const std::string& phone, const std::string& dob) const throw(InputError, AccountError)
{
	// Verify the Inputs
	if (user.length() == 0 || pass.length() == 0 || name.length() == 0 || phone.length() == 0 || dob.length() == 0)
		throw InputError("Please provide all the information mentioned above");
	
	verifyUser(user);
	verifyPhone(phone);
	verifyDob(dob);
	
	Account reg = Account(user, pass, name, phone, dob);
	
	try {
		d.writeAccount(reg);
	}
	catch(const AccountError& err) {
		throw AccountError(err.getMessage());
	}
}

void Wrapper::signin(const std::string& user, const std::string& pass) throw(SigninError)
{
	try
	{
		this->current = new Account(d.readAccount(user, pass));
	}
	catch(const AccountError& err)
	{
		throw SigninError(err.getMessage());
	}
}

void Wrapper::signout()
{
	if (this->current != NULL)
		delete this->current;
	
	this->current = NULL;
}

// Verification of Inputs
void Wrapper::verifyUser(const std::string& user) const throw(InputError)
{
	if (user.length() == 0)
		throw InputError("Please provide the information mentioned above");
	
	for(int i=0; i<user.length(); i++)
	{
		if (!(islower(user[i]) || isdigit(user[i])))
			throw InputError("Username should contain only lowercase letters or numbers");
	}
	
	if (user.compare("noreply") == 0)
		throw InputError("Please choose another username");
}

void Wrapper::verifyPhone(const std::string& phone) const throw(InputError)
{
	if (phone.length() == 0)
		throw InputError("Please provide the information mentioned above");
	
	for(int i=0; i<phone.length(); i++)
	{
		if (!isdigit(phone[i]))
			throw InputError("Phone Number should contain only numbers");
	}
}

void Wrapper::verifyDob(const std::string& dob) const throw(InputError)
{
	if (dob.length() == 0)
		throw InputError("Please provide the information mentioned above");
	
	bool res = true;
	
	// Check Length
	if (dob.length() == 10)
		res = true;
	else
		res = false;
	
	// Check format
	if (dob[2] == '-' && dob[5] == '-')
		res = true;
	else
		res = false;
	
	for(int i=0; i<dob.length(); i++)
	{
		if (i == 2 || i == 5)
			continue;
		
		if (!isdigit(dob[i]))
		{
			res = false;
			break;
		}
	}

    if (res == false)
    	throw InputError("The Date should be correct and in dd-mm-yyyy format");
    
	// Extract
    int Y = atoi(dob.substr(6).c_str());
    int M = atoi(dob.substr(3, 2).c_str());
    int D = atoi(dob.substr(0, 2).c_str());
    
	// Check Year
    if (Y >= 1900 && Y <= 9999)
    {
        // Check Month
        if (M >= 1 && M <= 12)
        {
            // Check Days
            if ((D >= 1 && D <= 31) && (M == 1 || M == 3 || M == 5 || M == 7 || M == 8 || M == 10 || M == 12)) {
                res = true;
            }
            else if ((D >= 1 && D <= 30) && (M == 4 || M == 6 || M == 9 || M == 11)) {
                res = true;
            }
            else if ((D >= 1 && D <= 28) && (M == 2)) {
				res = true;
            }
            else if (D == 29 && M == 2 && (Y % 400 == 0 || (Y % 4 == 0 && Y % 100 != 0))) {
				res = true;
            }
            else {
				res = false;
            }
        }
        else {
			res = false;
        }
    }
    else {
        res = false;
    }

    if (res == false)
    	throw InputError("The Date should be correct and in dd-mm-yyyy format");
}

// Change Details
void Wrapper::changeName(const std::string& name) throw(InputError)
{
	if (name.length() == 0)
		throw InputError("Please provide the information mentioned above");
	
	current->setName(name);
	d.updateAccount(*current);
}
void Wrapper::changePhone(const std::string& phone) throw(InputError)
{
	verifyPhone(phone);
	
	current->setPhone(phone);
	d.updateAccount(*current);
}
void Wrapper::changeDob(const std::string& dob) throw(InputError)
{
	verifyDob(dob);
	
	current->setDob(dob);
	d.updateAccount(*current);
}
void Wrapper::changePass(const std::string& oldPass, const std::string& newPass) throw(InputError, SigninError)
{
	if (newPass.length() == 0)
		throw InputError("Please provide the information mentioned above");
	
	try
	{
		current->setPass(oldPass, newPass);
	}
	catch(...)
	{
		throw SigninError("Wrong Password");
	}
	d.updateAccount(*current);
}

// Mail Operations
void Wrapper::writeMail(const std::string& sub, const std::string& to, const std::string& content) const
{
	Mail mail = Mail(sub, current->getUser(), to, content);
	d.writeMail(mail);
}

std::vector<Mail> Wrapper::readInbox(int page) const
{
	int start, end;
	
	start = ((MAIL_PER_PAGE) * (page - 1)) + 1;
	end   = (MAIL_PER_PAGE) * page;
	
	return d.readInbox(current->getUser(), start, end);
}

std::vector<Mail> Wrapper::readOutbox(int page) const
{
	int start, end;
	
	start = ((MAIL_PER_PAGE) * (page - 1)) + 1;
	end   = (MAIL_PER_PAGE) * page;
	
	return d.readOutbox(current->getUser(), start, end);
}

