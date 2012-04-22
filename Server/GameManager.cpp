#include <stack>
#include <pthread.h>
#include <cstring>
#include "Game.h"
#include "GameManager.h"

pthread_mutex_t trackerinc = PTHREAD_MUTEX_INITIALIZER;

GameManager::GameManager() {
	tracker = 0;
	free = new stack<int>();
	memset(games, NULL, maxGameCount);
}

// Returns true if the game exists, otherwise false
bool GameManager::exists(int n) {
	if (games[n] != NULL) {
		return true;
	}
	return false;
}

// Adds a game to the Game Manager
// Checks to see if there are any free games left
// If there are then it returns the game number
// Otherwise it checks the stack to see if there are available
// games on there and if there is then it gives that gameid.
// On fail it returns -1 (no games left)
int GameManager::addGame(Game* g) {
	while (!pthread_mutex_trylock(&trackerinc)) {
		if (tracker <= maxGameCount) {
			if (free->empty()) {
				games[tracker] = g;
				tracker++;
				pthread_mutex_unlock(&trackerinc);
				cout << "game num: " << tracker << endl;
				return (tracker-1);
			}
		}
		else {
			if (!free->empty()) {
				int spot = free->top();
				game[spot] = g;
				pthread_mutex_unlock(&trackerinc);
				return spot;
			}
			else 
				return -1;
		}
	}
	return -1;
}

// Returns the game object n
Game* GameManager::getGame(int n) {
	if (games[n] != '\0')
		return games[n];
	return '\0';
}

// Removes the game from the game manager (deleting it) and pushes that 
// game number onto the stack so we can still giving out incremental
// id's. 
bool GameManager::removeGame(int n) {
	if (games[n] != NULL) {
		delete games[n];
		free->push(n);
		return true;
	}
	return false;
}

int GameManager::getLength() {
	return tracker;
}
