#include <iostream>
#include "menu.h"
using namespace std;

int main(int argc, char** argv)
{
	Menu menu;
	int ch;
	
	menu.splashScreen();
	do
	{
		ch = menu.menuScreen();
		
		if (ch == menu.SIGNIN) {
			bool login = menu.signinPage();
			
			// ----- Home page -----
			if (login)
			{
				int ch;
				do
				{
					ch = menu.homePage();
					
					if (ch == menu.INBOX || ch == menu.OUTBOX) {
						// ----- Mail page -----
						int r = 1;
						
						do
						{
							r = menu.mailboxPage(ch, r);
							
							if (r == 0)
								break;
						
						} while (true);
						// ----- Mail page -----
					}
					else if (ch == menu.MAIL) {
						menu.mailPage();
					}
					else if (ch == menu.SETTINGS) {
						menu.settingsPage();
					}
					else if (ch == menu.SIGNOUT) {
						menu.signoutPage();
						break;
					}
					else {
						// Invalid Choice
					}
					
				} while (true);
			}
			// ----- Home page -----
		}
		else if (ch == menu.REGISTER) {
			menu.registerPage();
		}
		else if (ch == menu.EXIT) {
			break;
		}
		else {
			// Invalid Choice
		}
		
	} while (true);
	
	menu.exitScreen();
	
	return 0;
}

