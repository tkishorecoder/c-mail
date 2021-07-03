#ifndef MENU_H
#define MENU_H

#include "wrapper.h"

// Class for displaying information on Console
class Menu
{
	Wrapper api;
	void clearScreen();
	void pauseScreen();

	void viewMail(const Mail& m);
	
public:
	const int SIGNIN;
	const int REGISTER;
	const int EXIT;
	
	const int INBOX;
	const int OUTBOX;
	const int MAIL;
	const int SETTINGS;
	const int SIGNOUT;
	
	Menu() : SIGNIN(1), REGISTER(2), EXIT(3), INBOX(1), OUTBOX(2), MAIL(3), SETTINGS(4), SIGNOUT(5) {}
	
	void splashScreen();
	int menuScreen();
	void exitScreen();
	
	bool signinPage();
	void registerPage();
	int homePage();
	void signoutPage();
	
	void mailPage();
	void settingsPage();
	
	int mailboxPage(int box, int page);
};

#endif

