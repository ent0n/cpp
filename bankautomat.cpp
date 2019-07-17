/*--------------------------------------------------*
|													|
|		    Autor:	Fabian Huber					|
|													|
|	      Sprache:	C++								|
|													|
|		    Datum:	17.07.2019 12:52				|
|													|
|    Beschreibung:	Bankautomat						|
|													|
|		   Mentor:	Michael Braumsperger			|
|													|
*--------------------------------------------------*/

#include <iostream>

#include <vector>

#include <string>

using namespace std;


// Menu-Header
string menu = R"(	
---------------------------------- 
__________                __     
\______   \_____    ____ |  | __ 
 |    |  _/\__  \  /    \|  |/ / 
 |    |   \ / __ \|   |  \    <  
 |______  /(____  /___|  /__|_ \
       \/      \/     \/     \/ 
---------------------------------- 
)";

// Variablen

string username;	// password
string password;	// username

int marker;			// ID for vectors

int opt;			// Options for Menus

bool loggedIn;		// Is the user logged in?



					// Inhalt der Menues
vector < string > login = {
	"LOGIN",
	"Einloggen",
	"Beenden"
};
vector < string > kontoverwaltung = {
	"KONTO",
	"Anzeigen",
	"Abheben",
	"Beenden"
};
vector < string > geldAbheben = {
	"ABHEBEN",
	"50EUR",
	"100EUR",
	"200EUR",
	"500EUR"
};
// structure
struct Daten {
	string username;
	string password;
	int kontostand;
};

// IDS
vector<int> = { 001,002,003,004,005 };
/* usernames und passwörter alt
vector < string > usernames = {
	"admin",
	"root"
};
vector < string > passwords = {
	"admin",
	"root"
};
vector < float > kontostaende = {
	1000,
	2000
};*/

// Prototypen
void startMenu();
void loggedInMenu();

int findUser(string);
bool logIn(string, string);

void drawMenu(string);

int viewbalance(int);
void abheben(int, int);

void reportError(string);
void paus();
void stopP();



int main() {
	// ERSTELLE KONTEN
	Daten 001 = {
		"admin",
		"admin", 
		1000
	}
	Daten 002 = {
		"boris",
		"123456",
		1000
	}
	Daten 003 = {
		"josef",
		"bmw",
		1000
	}
	Daten 004 = {
		"pp",
		"admin",
		1000
	}
	Daten 005 = {
		"tim",
		"myppveryhardxd",
		1000
	}
	// FERTIG
	system("@echo off");
	system("color 4a");
	system("mode con: cols=34 lines=40");
	startMenu();
	return 0;
}







// [ MENU ]			Menu before LogIn
void startMenu() {
	drawMenu("login"); // Zeige das Menu
	opt = 0;
	cout << "(1, 2) >> ";
	cin >> opt;
	if (opt == 1) {
		drawMenu("default");
		cout << "Gib deinen Nutzernamen ein!" << endl;
		cin >> username;
		drawMenu("default");
		cout << "Gib das Passwort für " << username << " ein!" << endl;
		cin >> password;
		bool b = logIn(username, password);
		if (b) {
			loggedInMenu();
		}
		else {
			startMenu();
		}
	}
	else if (opt == 2) {
		stopP();
	} //Beenden (Login bildschirm
}


// [ MENU ]			Menu after LogIn
void loggedInMenu() {
	marker = findUser(username);
	drawMenu("konto"); // Zeige das Menu
	opt = 0;
	cout << "(1, 2, 3) >> ";
	cin >> opt;
	if (opt == 1) {
		drawMenu("default");
		int balance = viewbalance(marker);
		cout << "Kontostand: " << balance << "€" << endl;
		paus();
		loggedInMenu();
	}
	else if (opt == 2) {
		drawMenu("abheben");
		opt = 0;
		cout << "(1, 2, 3, 4) >> ";
		cin >> opt;
		if (opt == 1) {
			abheben(marker, 50);
			loggedInMenu();
		}
		else if (opt == 2) {
			abheben(marker, 100);
			loggedInMenu();
		}
		else if (opt == 3) {
			abheben(marker, 200);
			loggedInMenu();
		}
		else if (opt == 4) {
			abheben(marker, 500);
			loggedInMenu();
		}
		loggedInMenu();
	}
	else if (opt == 3) {
		stopP();
	}

}





// [ LOGIN ]		FindUser
int findUser(string x) {
	int y = 0;
	for (int i = 0; i < usernames.size(); i++) {
		if (x == usernames[i]) {
			y = i;
			break;
		}
	}

	return y;
}


// [ LOGIN ]		Check Password
bool logIn(string u, string p) {
	int y;
	string pass;
	y = findUser(u);
	pass = passwords[y];
	if (pass == p) {
		loggedIn = true;
	}
	else {
		drawMenu("default");
		reportError("Passwort ist falsch!");
		loggedIn = false;
	}
	return loggedIn;
}




// [ BANK ]			Kontostand anzeigen
int viewbalance(int x) {
	int y;
	y = kontostaende[x];
	return y;
}


// [ BANK ]			Abheben
void abheben(int x, int value) {
	int current = viewbalance(x);
	int diff = current - value;
	if (diff >= 0) {
		kontostaende[x] = kontostaende[x] - value;
	}
	else {
		cout << "Dein Kontostand reicht nicht aus!";
		paus();
	}
}




// [ GRAPHICS ]		Zeige vorgegebenes Menu an 
void drawMenu(string x) {
	system("cls");																	// Resette den Bildschirm
	cout << menu << endl;															// Zeichne ASCII-Art
																					// Zeilenumbruch
	if (x == "default") {															// Default Menu
		
		cout << "----------------------------------" << endl;
		cout << endl;

	}
	else if (x == "login") {														// LogIn Menu
		
		cout << "------------- " << login[0] << " --------------" << endl;
		for (int i = 1; i < login.size(); i++) {

			cout << i << ". " << login[i] << endl;
		}
		cout << endl;
	}
	else if (x == "konto") {														// LogIn Menu
		
		cout << "------------- " << kontoverwaltung[0] << " --------------" << endl;
		for (int i = 1; i < kontoverwaltung.size(); i++) {

			cout << i << ". " << kontoverwaltung[i] << endl;
		}
		cout << endl;
	}
	else if (x == "abheben") {														// LogIn Menu
		
		cout << "----------- " << geldAbheben[0] << " -------------" << endl;
		for (int i = 1; i < geldAbheben.size(); i++) {

			cout << i << ". " << geldAbheben[i] << endl;
		}
		cout << endl;
	}
	
}


// [ INFO ]			Error Reporting
void reportError(string error) {
	cout << "Fehler! " << error << endl;
}


// [ FLOW/INFO ]	PAUSE
void paus() {
	system("pause > nul");
}


// [ FLOW ]			END
void stopP() {
	drawMenu("default");
	cout << endl;
	cout << "Danke dass du unseren" << endl;
	cout << "Service genutzt hast!" << endl;
	paus();
	system("exit");
}
