#include "menu.h"

#include <iostream>
#include <iomanip>
#include <cstdlib>

#include <string>
#include <sstream>
#include <vector>
#include <iterator>

void Menu::clearScreen()
{
	system("cls");
}

void Menu::pauseScreen()
{
	system("pause");
}

template <typename Out>
void split(const std::string &s, char delim, Out result) {
    std::istringstream iss(s);
    std::string item;
    while (std::getline(iss, item, delim)) {
        *result++ = item;
    }
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

void Menu::splashScreen()
{
	clearScreen();
	
	std::cout << "\n\n";
	std::cout << "\n\t\tCMail App";
	std::cout << "\n\t\t\t- using C++";
	std::cout << "\n\t\t\t- by Kishore";
	std::cout << "\n\n";
	
	pauseScreen();
}

int Menu::menuScreen()
{
	int ch;
	clearScreen();
	
	std::cout << "\n ----- MENU -----";
	std::cout << "\n1. Sign-in";
	std::cout << "\n2. Register";
	std::cout << "\n3. Exit";
	std::cout << "\n\nEnter the choice : ";
	std::cin >> ch;
	std::cin.ignore();
	std::cout << "\n";
	
	pauseScreen();
	return ch;
}

void Menu::exitScreen()
{
	clearScreen();
	
	std::cout << "\n";
	std::cout << "\nThank You!";
	std::cout << "\nCome Again!!";
	std::cout << "\n\n";
	
	pauseScreen();
}

void Menu::registerPage()
{
	clearScreen();
	
	std::string user, pass, name, phone, dob;
	
	std::cout << "\n ----- REGISTER ----- \n";
	std::cout << "Enter your name : ";
	getline(std::cin, name);
	std::cout << "Enter your phone number : ";
	getline(std::cin, phone);
	std::cout << "Enter your date of birth (dd-mm-yyyy) : ";
	getline(std::cin, dob);
	std::cout << "Enter the username you want : ";
	getline(std::cin, user);
	std::cout << "Enter the password : ";
	getline(std::cin, pass);
	
	std::cout << "\n";
	try {
		api.registerAccount(user, pass, name, phone, dob);
		std::cout << "\nRegistration Success!";
	}
	catch(const InputError& err) {
		std::cout << err.getMessage();
		std::cout << "\nRegistration Failed!";
	}
	catch(const AccountError& err) {
		std::cout << err.getMessage();
		std::cout << "\nRegistration Failed!";
	}
	std::cout << "\n\n";
	
	pauseScreen();	
}

bool Menu::signinPage()
{
	bool res;
	clearScreen();
	
	std::cout << "\n ----- SIGN-IN ----- \n";
	
	std::string user, pass;
	std::cout << "Enter the username : ";
	getline(std::cin, user);
	std::cout << "Enter the password : ";
	getline(std::cin, pass);
	
	try {
		api.signin(user, pass);
		res = true;
	}
	catch(const SigninError& err) {
		std::cout << "\nInvalid Login Information";
		std::cout << "\nLogin Failed";
		res = false;
	}
	std::cout << "\n\n";
	
	pauseScreen();
	return res;
}

int Menu::homePage()
{
	int ch;
	clearScreen();
	
	std::cout << "\n ----- HOME PAGE ----- ";
	std::cout << "\n1. Go to Inbox";
	std::cout << "\n2. Go to Outbox";
	std::cout << "\n3. Write a Mail";
	std::cout << "\n4. Change Account Information";
	std::cout << "\n5. Sign-out";
	std::cout << "\n\nEnter the choice : ";
	std::cin >> ch;
	std::cin.ignore();
	std::cout << "\n";
	
	pauseScreen();
	return ch;
}

void Menu::signoutPage()
{
	api.signout();
}

void Menu::mailPage()
{
	clearScreen();
	
	std::cout << "\n ----- NEW MAIL ----- \n";
	
	std::string sub, to, content;
	std::cout << "Enter the Subject : ";
	getline(std::cin, sub);
	std::cout << "Enter the Address : ";
	getline(std::cin, to);
	std::cout << "Enter the Content : \n";
	getline(std::cin, content);
	std::cout << "\n";
	
	api.writeMail(sub, to, content);
	
	pauseScreen();
}

void Menu::settingsPage()
{
	clearScreen();
	
	int ch;
	std::cout << "\n ----- SETTINGS PAGE ----- ";
	
	Account acc = api.getAccount();
	std::cout << "\nUsername      : " << acc.getUser();
	std::cout << "\nName          : " << acc.getName();
	std::cout << "\nPhone         : " << acc.getPhone();
	std::cout << "\nDate of Birth : " << acc.getDob();
	std::cout << "\nRegister Dage : " << acc.getRegdate();
	std::cout << "\n";
	
	std::cout << "\n1. Change Name";
	std::cout << "\n2. Change Phone";
	std::cout << "\n3. Change Date of Birth";
	std::cout << "\n4. Change Password";
	std::cout << "\n\nEnter the choice : ";
	std::cin >> ch;
	std::cin.ignore();
	std::cout << "\n";
	
	if (ch == 1)
	{
		std::string name;
		
		std::cout << "Enter the name : ";
		getline(std::cin, name);
		std::cout << "\n";
		
		try {
			api.changeName(name);
		}
		catch(const InputError& err) {
			std::cout << err.getMessage();
		}
	}
	else if (ch == 2)
	{
		std::string phone;
		
		std::cout << "Enter the phone number : ";
		getline(std::cin, phone);
		std::cout << "\n";
		
		try {
			api.changePhone(phone);
		}
		catch(const InputError& err) {
			std::cout << err.getMessage();
		}
	}
	else if (ch == 3)
	{
		std::string dob;
		
		std::cout << "Enter the date of birth (dd-mm-yyyy): ";
		getline(std::cin, dob);
		std::cout << "\n";
		
		try {
			api.changeDob(dob);
		}
		catch(const InputError& err) {
			std::cout << err.getMessage();
		}
	}
	else if (ch == 4)
	{
		std::string oldPass, newPass;
		
		std::cout << "Enter the Old Password : ";
		getline(std::cin, oldPass);
		std::cout << "Enter the New Password : ";
		getline(std::cin, newPass);
		std::cout << "\n";
		
		try {
			api.changePass(oldPass, newPass);
		}
		catch(const InputError& err) {
			std::cout << err.getMessage();
		}
		catch(const SigninError& err) {
			std::cout << err.getMessage();
		}
	}
	std::cout << "\n\n";
	
	pauseScreen();
}

int Menu::mailboxPage(int box, int page)
{
	std::vector<Mail> mails;
	
	if (box == INBOX)
		mails = api.readInbox(page);
	else
		mails = api.readOutbox(page);
	
	top:
	clearScreen();
	
	std::cout << "\n ------------------------- MAILBOX - " << (box == INBOX? "INBOX": "OUTBOX") << " - PAGE " << std::setw(2) << page <<" ------------------------- \n\n";
	for(int i=0; i<mails.size(); i++)
	{
		std::cout << std::setw( 5) << std::right << i + 1              << "  ";
		if (box == INBOX)
			std::cout << std::setw(20) << std::left  << mails[i].getFrom() << "  ";
		else
			std::cout << std::setw(20) << std::left  << mails[i].getTo() << "  ";
		std::cout << std::setw(50) << std::left  << mails[i].getSub()  << "  ";
		
		std::cout << "\n";
	}
	
	std::cout << "\n -----------------------------------------------------------------------------";
	if (box == OUTBOX) std::cout << "-";
	std::cout << "\n";
	
	std::cout << "\n AVAILABLE COMMANDS : ";
	std::cout << "\npage <int> - Switch Pages";
	std::cout << "\nselect <int> - View Email";
	std::cout << "\nexit - Go to Home Page";
	
	std::string s;
	std::cout << "\n\nEnter the Command : ";
	getline(std::cin, s);
	
	// Parse the String
	std::vector<std::string> p = split(s, ' ');
	
	int d;
	if (p.size() == 1 && p[0].compare("exit") == 0)
	{
		d = 0; // Exit
	}
	else if (p.size() == 2 && p[0].compare("page") == 0)
	{
		d = atoi(p[1].c_str());
		
		if (d <= 0)
			d = -1;
	}
	else if (p.size() == 2 && p[0].compare("select") == 0)
	{
		d = atoi(p[1].c_str());
		
		if (d < 1 || d > mails.size())
			d = -1;
	}
	else
	{
		d = -1; // Invalid
	}
	
	if (d == -1)
		std::cout << "\nInvalid Command!\n";
	
	std::cout << "\n";
	pauseScreen();
	
	if (d == -1)
		goto top;
	
	if (p[0].compare("select") == 0)
	{
		viewMail(mails[d-1]);
		goto top;
	}
	
	return d;
}

void Menu::viewMail(const Mail& m)
{
	clearScreen();
	std::cout << "\n";
	
	std::cout << "SUBJECT : " << m.getSub() << '\n';
	std::cout << "\nFROM : " << m.getFrom() << '\n';
	std::cout << "TO : " << m.getTo() << '\n';
	std::cout << "DATE AND TIME : " << m.getWhen() << '\n';
	std::cout << "\nCONTENT : \n" << m.getContent() << '\n';
	
	std::cout << "\n";
	pauseScreen();
}

