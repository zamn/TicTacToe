#ifndef _USER_H
#define _USER_H
#include <iostream>

using namespace std;

class User {
	public:
		User(string, char);
		string getNick();
		char getSymbol();
		void setNick(string);
		void setSymbol(char);
		bool isTurn();
		void setTurn(bool);

	private:
		string nick;
		char symbol;
		bool turn;
};
#endif
