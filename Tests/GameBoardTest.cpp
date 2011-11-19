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

/* This is testing GameBoard's update function verifying
 * all of the return types are returned
 */

void GameBoardTest::testUpdate() {
	CPPUNIT_ASSERT(gameboard->update(1,*player1) == 1);
	CPPUNIT_ASSERT(gameboard->update(2,*player1) == 0);
	CPPUNIT_ASSERT(gameboard->update(11,*player2) == -1);
	CPPUNIT_ASSERT(gameboard->update(7,*player2) == 1);
	CPPUNIT_ASSERT(gameboard->update(30,*player1) == -1);
	CPPUNIT_ASSERT(gameboard->update(9, *player1) == 1);
}

void GameBoardTest::testCheckWinner() {
	cout << "Checking Row Winning" << endl;
	CPPUNIT_ASSERT(gameboard->update(1,*player1) == 1);
	CPPUNIT_ASSERT(gameboard->update(7,*player2) == 1);
	CPPUNIT_ASSERT(gameboard->update(2,*player1) == 1);
	CPPUNIT_ASSERT(gameboard->update(6,*player2) == 1);
	CPPUNIT_ASSERT(gameboard->update(3,*player1) == 1);
	CPPUNIT_ASSERT(gameboard->checkWinner() == player1->getNick());
	gameboard->reset();
	cout << "Checking Forward Diagnol Winning" << endl;
	CPPUNIT_ASSERT(gameboard->update(1, *player1) == 0);
	CPPUNIT_ASSERT(gameboard->update(2, *player2) == 1);
	CPPUNIT_ASSERT(gameboard->update(5, *player1) == 1);
	CPPUNIT_ASSERT(gameboard->update(3, *player2) == 1);
	CPPUNIT_ASSERT(gameboard->update(9, *player1) == 1);
	CPPUNIT_ASSERT(gameboard->checkWinner() == player1->getNick());
	gameboard->reset();
}

void GameBoardTest::testGameOver() {
	CPPUNIT_ASSERT(gameboard->gameOver("asdf") == true);
}

void GameBoardTest::tearDown() {
	delete gameboard;
	delete player1;
	delete player2;
}

void GameBoardTest::testConstructor() {
		
}
