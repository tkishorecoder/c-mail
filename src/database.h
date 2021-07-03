#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <vector>
#include "account.h"
#include "mail.h"

// Memory Size for Binary File Operations
enum {ACCOUNT=50};
enum {SUB=200, FROM=50, TO=50, CONTENT=10000, WHEN=50};

// Hash Value
enum {HASH=30997};

// Error Class
class AccountError
{
	std::string message;
public:
	AccountError(const std::string& message);
	std::string getMessage() const;
};

class MailError
{
	std::string message;
public:
	MailError(const std::string& message);
	std::string getMessage() const;
};

// Class for Working with Binary Files
class Database
{
	// Member variables
	std::string datapath;
	std::string basic;
	std::string inbox;
	std::string outbox;
	
	// Check for the Existence of Path
	bool IsPathExist(const std::string &s) const;
	
	// Cryptology
	int hashOf(const std::string& s) const;
	std::string crypt(const std::string& msg, const int& hashValue) const;

	// Repetitive Functions
	void writeMailRep(std::ofstream& f, const Mail& mail) const;
	std::vector<Mail> readMailboxRep(const std::string& user, int s, int e, const std::string& box) const throw(MailError);
	
public:
	// Constructor
	Database();
	
	// File Operations based on Account
	Account readAccount(const std::string& log_user, const std::string& log_pass) const throw(AccountError);
	void updateAccount(const Account& account) const;
	void writeAccount(const Account& account) const throw(AccountError);
	
	// File Operations based on Mail
	void writeMail(const Mail& mail) const;
	
	std::vector<Mail> readInbox(const std::string& user, int s, int e) const;
	std::vector<Mail> readOutbox(const std::string& user, int s, int e) const;
};

#endif

