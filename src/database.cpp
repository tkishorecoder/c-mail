#include "database.h"

#include <sys/stat.h>
#include <direct.h>
#include <fstream>
#include <string>
#include <vector>

// Error Class
AccountError::AccountError(const std::string& message) {
	this->message = message;
}
std::string AccountError::getMessage() const {
	return this->message;
}

MailError::MailError(const std::string& message) {
	this->message = message;
}
std::string MailError::getMessage() const {
	return this->message;
}

// Check for the Existence of Path
bool Database::IsPathExist(const std::string &s) const
{
	struct stat buffer;
	return (stat (s.c_str(), &buffer) == 0);
}

// Cryptology
int Database::hashOf(const std::string& s) const
{
	const int MOD = 1000000;
	const int PRIME = 31;
	
	int res = 0;
	
	for(int i=0; i<s.length(); ++i)
		res = (PRIME * s[i] + res) % MOD;
	
	return res;
}

std::string Database::crypt(const std::string& msg, const int& hashValue) const
{
	const int MAX_SIZE = CONTENT;
	
	char s[MAX_SIZE];
	strncpy(s, msg.c_str(), MAX_SIZE);
	
	for(int i=0; i<strlen(s); ++i)
		s[i] ^= hashValue;
	
	return std::string(s);
}

// Constructor
Database::Database()
{
	// Default Names
	const std::string defaultPath = "C:\\Database";
	const std::string pathFileName = "path.cfg";
	
	// Additional Names
	this->basic = "basic.bin";
	this->inbox = "inbox.bin";
	this->outbox = "outbox.bin";

	// Path File
	std::fstream fPath;
	
	// Check if the file exists
	bool pathFileExist = IsPathExist(pathFileName.c_str());
	
	if (pathFileExist)
	{
		// No Problem
	}
	else
	{
		// Create Path File
		fPath.open(pathFileName.c_str(), std::ios::out | std::ios::trunc);
		fPath << defaultPath;
		fPath.close();
	}
	
	// Store the Path
	fPath.open(pathFileName.c_str(), std::ios::in);
	getline(fPath, this->datapath);
	fPath.close();
	
	// Create the folder
	mkdir(datapath.c_str());
	
	return;
}

// File Operations based on Account
Account Database::readAccount(const std::string& log_user, const std::string& log_pass) const throw(AccountError)
{
	// Get the Path
	const std::string folderPath = datapath + "\\" + log_user;
	const std::string basicPath = folderPath + "\\" + basic;
	
	// File Operations
	std::ifstream f;
	
	f.open(basicPath.c_str(), std::ios::in | std::ios::binary);
	
	if (!f.good())
		throw AccountError("Username does not exist");
	
	std::string user, pass, name, phone, dob, regdate;
	char buf[ACCOUNT];
	
	f.read(buf, ACCOUNT); user    = crypt(buf, HASH);
	f.read(buf, ACCOUNT); pass    = crypt(buf, HASH);
	f.read(buf, ACCOUNT); name    = crypt(buf, HASH);
	f.read(buf, ACCOUNT); phone   = crypt(buf, HASH);
	f.read(buf, ACCOUNT); dob     = crypt(buf, HASH);
	f.read(buf, ACCOUNT); regdate = crypt(buf, HASH);
	
	f.close();
	
	if (pass.compare(log_pass) != 0)
		throw AccountError("Wrong Password");
	
	return Account(user, pass, name, phone, dob, regdate);
}

void Database::updateAccount(const Account& account) const
{
	// Get the Path
	const std::string folderPath = datapath + "\\" + account.getUser();
	const std::string basicPath = folderPath + "\\" + basic;
	
	// File Operations
	std::ofstream f;
	
	// Basic
	f.open(basicPath.c_str(), std::ios::out | std::ios::trunc | std::ios::binary);
	
	std::string tmp;
	
	tmp = crypt(account.getUser(),    HASH); tmp.resize(ACCOUNT); f.write(tmp.c_str(), ACCOUNT);
	tmp = crypt(account.getPass(),    HASH); tmp.resize(ACCOUNT); f.write(tmp.c_str(), ACCOUNT);
	tmp = crypt(account.getName(),    HASH); tmp.resize(ACCOUNT); f.write(tmp.c_str(), ACCOUNT);
	tmp = crypt(account.getPhone(),   HASH); tmp.resize(ACCOUNT); f.write(tmp.c_str(), ACCOUNT);
	tmp = crypt(account.getDob(),     HASH); tmp.resize(ACCOUNT); f.write(tmp.c_str(), ACCOUNT);
	tmp = crypt(account.getRegdate(), HASH); tmp.resize(ACCOUNT); f.write(tmp.c_str(), ACCOUNT);
	
	f.close();
	
	return;
}

void Database::writeAccount(const Account& account) const throw(AccountError)
{
	// Create the Folder
	const std::string folderPath = datapath + "\\" + account.getUser();
	
	if (IsPathExist(folderPath))
		throw AccountError("Username already exist");
	
	mkdir(folderPath.c_str());
	
	const std::string basicPath = folderPath + "\\" + basic;
	const std::string inboxPath = folderPath + "\\" + inbox;
	const std::string outboxPath = folderPath + "\\" + outbox;
	
	// File Operations
	std::ofstream f;
	
	// Basic
	f.open(basicPath.c_str(), std::ios::out | std::ios::trunc | std::ios::binary);
	
	std::string tmp;
	
	tmp = crypt(account.getUser(),    HASH); tmp.resize(ACCOUNT); f.write(tmp.c_str(), ACCOUNT);
	tmp = crypt(account.getPass(),    HASH); tmp.resize(ACCOUNT); f.write(tmp.c_str(), ACCOUNT);
	tmp = crypt(account.getName(),    HASH); tmp.resize(ACCOUNT); f.write(tmp.c_str(), ACCOUNT);
	tmp = crypt(account.getPhone(),   HASH); tmp.resize(ACCOUNT); f.write(tmp.c_str(), ACCOUNT);
	tmp = crypt(account.getDob(),     HASH); tmp.resize(ACCOUNT); f.write(tmp.c_str(), ACCOUNT);
	tmp = crypt(account.getRegdate(), HASH); tmp.resize(ACCOUNT); f.write(tmp.c_str(), ACCOUNT);
	
	f.close();
	
	// Inbox
	f.open(inboxPath.c_str(), std::ios::out | std::ios::trunc | std::ios::binary);
	f.close();
	
	// Outbox
	f.open(outboxPath.c_str(), std::ios::out | std::ios::trunc | std::ios::binary);
	f.close();
	
	return;
}

// Repetitive Functions
void Database::writeMailRep(std::ofstream& f, const Mail& mail) const
{
	std::string tmp;
	
	tmp = crypt(mail.getSub(), HASH);
	tmp.resize(SUB);
	f.write(tmp.c_str(), SUB);
	
	tmp = crypt(mail.getFrom(), HASH);
	tmp.resize(FROM);
	f.write(tmp.c_str(), FROM);
	
	tmp = crypt(mail.getTo(), HASH);
	tmp.resize(TO);
	f.write(tmp.c_str(), TO);
	
	tmp = crypt(mail.getWhen(), HASH);
	tmp.resize(WHEN);
	f.write(tmp.c_str(), WHEN);
	
	tmp = crypt(mail.getContent(), HASH);
	tmp.resize(CONTENT);
	f.write(tmp.c_str(), CONTENT);
}

std::vector<Mail> Database::readMailboxRep(const std::string& user, int s, int e, const std::string& box) const throw(MailError)
{
	std::vector<Mail> res;
	const int SHIFT = SUB + FROM + TO + WHEN + CONTENT;
	
	if (s < 1 || e < 1 || s > e)
		throw MailError("Invalid Index");
	
	// Get the Path
	const std::string mailboxPath = datapath + "\\" + user + "\\" + box;
	
	std::ifstream f;
	f.open(mailboxPath.c_str(), std::ios::in | std::ios::binary);
	
	f.seekg(0, std::ios::end);
	int cur_pos = f.tellg();
	f.seekg(0, std::ios::beg);
	
	cur_pos -= SHIFT * (s - 1);
	
	while (true)
	{
		cur_pos -= SHIFT;
		if (cur_pos < 0)
			break;
		
		f.seekg(cur_pos);
		
		std::string sub, from, to, when, content;
		char buf[CONTENT];
		
		f.read(buf, SUB);     sub     = crypt(buf, HASH);
		f.read(buf, FROM);    from    = crypt(buf, HASH);
		f.read(buf, TO);      to      = crypt(buf, HASH);
		f.read(buf, WHEN);    when    = crypt(buf, HASH);
		f.read(buf, CONTENT); content = crypt(buf, HASH);
		
		res.push_back(Mail(sub, from, to, content, when));
		
		if (s == e)
			break;
		s++;
	}
	f.close();
	
	return res;
}

// File Operations based on Mail
void Database::writeMail(const Mail& mail) const
{	
	// Get the Paths
	const std::string folderPathFrom = datapath + "\\" + mail.getFrom();
	const std::string folderPathTo   = datapath + "\\" + mail.getTo();
	std::string outboxPath = folderPathFrom + "\\" + outbox;
	std::string inboxPath  = folderPathTo + "\\" + inbox;
	
	// Mailbox File
	std::ofstream mailbox;
	
	// Update the Outbox
	mailbox.open(outboxPath.c_str(), std::ios::out | std::ios::app | std::ios::binary);
	writeMailRep(mailbox, mail);
	mailbox.close();
	
	// Check the To Address
	bool toUserExist = IsPathExist(inboxPath);
	
	// Update the Inbox
	if (toUserExist)
	{
		// To Address Found
		mailbox.open(inboxPath.c_str(), std::ios::out | std::ios::app | std::ios::binary);
		writeMailRep(mailbox, mail);
		mailbox.close();
	}
	else
	{
		// To Address not Found
		std::string sub, from, to, content;
		
		sub = "Error - Username \'" + mail.getTo() + "\' not found";
		from = "noreply";
		to = mail.getFrom();
		content = "The username \'" + mail.getTo() + "\' was not found in our Database.";
		
		inboxPath = folderPathFrom + "\\" + inbox;
		const Mail& errorMail = Mail(sub, from, to, content);
		
		mailbox.open(inboxPath.c_str(), std::ios::out | std::ios::app | std::ios::binary);
		writeMailRep(mailbox, errorMail);
		mailbox.close();
	}
	
	return;
}

std::vector<Mail> Database::readInbox(const std::string& user, int s, int e) const 
{
	return readMailboxRep(user, s, e, inbox);
}
std::vector<Mail> Database::readOutbox(const std::string& user, int s, int e) const 
{
	return readMailboxRep(user, s, e, outbox);
}

