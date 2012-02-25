#include <stack>
#include <pthread.h>
#include <cstring>
#include "Game.h"
#include "GameManager.h"

pthread_mutex_t trackerinc = PTHREAD_MUTEX_INITIALIZER;

GameManager::GameManager() {
	tracker = 0;
	free = new stack<int>();
	memset(games, '\0', maxGameCount);
}

bool GameManager::exists(int n) {
	if (games[n] != '\0') {
		return true;
	}
	return false;
}

int GameManager::addGame(Game* g) {
	while (!pthread_mutex_trylock(&trackerinc)) {
		if (tracker <= maxGameCount) {
			if (free->empty()) {
				games[tracker] = g;
				tracker++;
				pthread_mutex_unlock(&trackerinc);
				return (tracker-1);
			}
			else {
				int spot = free->top();
				games[spot] = g;
				tracker++;
				pthread_mutex_unlock(&trackerinc);
				return spot;
			}
		}
		else
			return -1;
	}
}

Game* GameManager::getGame(int n) {
	if (games[n] != '\0')
		return games[n];
	else
		return '\0';
}
