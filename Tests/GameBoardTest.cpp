#include "GameBoardTest.h"
#include "../GameBoard.h"

using namespace std;

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION(GameBoardTest);

void GameBoardTest::setUp() {
	player1 = new User("adam", 'X');
	player2 = new User("aaron", 'O');
	gameboard = new GameBoard(player1, player2);
}

void GameBoardTest::testUpdate() {
	CPPUNIT_ASSERT(gameboard->update(1,1,player1) == 1);
	CPPUNIT_ASSERT(gameboard->update(1,2,player1) == 0);
	CPPUNIT_ASSERT(gameboard->update(5,0,player1) == -1);
	CPPUNIT_ASSERT(gameboard->update(1,7,player1) == -1);
}

void GameBoardTest::testCheckWinner() {
	gameboard->update(2,1,player2);
	gameboard->update(1,2,player1);
	gameboard->update(2,2,player2);
	gameboard->update(1,3,player1);
	CPPUNIT_ASSERT(gameboard->checkWinner() == player1.getNick());
}

void GameBoardTest::testGameOver() {
	CPPUNIT_ASSERT(over == true);
}

void GameBoardTest::tearDown() {
	delete gameboard;
	delete player1;
	delete player2;
}

void GameBoardTest::testConstructor() {
		
}
