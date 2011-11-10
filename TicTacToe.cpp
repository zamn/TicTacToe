#include <iostream>
#include "GameBoard.h"

using namespace std;

int main(void) {
	string name;
	string symbol;
	string temp;
	string x, y;
	cout << "Enter your name: " << endl;
	cin.getline(name, 256);
	cout << "Enter a symbol: " << endl;
	cin.getline(symbol, 256);
	User player(name, symbol);
	GameBoard gameboard;
	gameboard.draw();
	cout << "Enter a coordinate (x,y) to put " << symbol << ":" << endl;
	cin.getline(temp, 256);
	x = atoi(remove(temp.substr(0, temp.find_first_of(","))));
	y = atoi(remove(temp.substr(temp.find_first_of(",")+1, temp.length())));
	if ((x > 0) && (x < 4) && (y > 0) && (y < 4)) {
		gameboard.upate(x, y, player);
	}
	
}
