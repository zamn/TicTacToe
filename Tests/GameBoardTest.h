#ifndef GAMEBOARDTEST_H
#define GAMEBOARDTEST_H

#include <cppunit/extensions/HelperMacros.h>
#include "../User.h"
#include "../GameBoard.h"

class GameBoardTest : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(GameBoardTest);
	CPPUNIT_TEST(testConstructor);
	CPPUNIT_TEST(testUpdate);
	CPPUNIT_TEST(testCheckWinner);
	CPPUNIT_TEST_SUITE_END();

public:
	void testCheckWinner();
	void testGameOver();	
	void testUpdate();
	void tearDown();
	void setUp();
	void testConstructor();
private:
	User *player1;
	User *player2;
	GameBoard *gameboard;
};
#endif // GAMEBOARDTEST_H
