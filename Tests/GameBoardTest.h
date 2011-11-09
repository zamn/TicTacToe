#ifndef GAMEBOARDTEST_H
#define GAMEBOARDTEST_H

#include <cppunit/extensions/HelperMacros.h>
#include "../User.h"
#include "../GameBoard.h"

class UserTest : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(GameBoardTest);
	CPPUNIT_TEST(testConstructor);
	CPPUNIT_TEST_SUITE_END();

public:
	bool testCheckWinner();
	bool testGameOver();	
	int testUpdate();
	void tearDown();
	void setUp();
	void testConstructor();
private:
	User *player1;
	User *player2;
	GameBoard *gameboard;
};
#endif // GAMEBOARDTEST_H
