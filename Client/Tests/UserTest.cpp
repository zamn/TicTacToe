#include "UserTest.h"

using namespace std;

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION(UserTest); 

void UserTest::setUp() {
	nick = "adam";
	symbol = 'X';
	user = new User(nick, symbol);
}

void UserTest::testGetNick() {
	CPPUNIT_ASSERT_EQUAL(nick, user->getNick());
}

void UserTest::testGetSymbol() {
	CPPUNIT_ASSERT_EQUAL(symbol, user->getSymbol());
}

void UserTest::tearDown() {
	delete user;
}

void UserTest::testConstructor() {
	// Check
	CPPUNIT_ASSERT_EQUAL(nick, user->getNick());
	CPPUNIT_ASSERT_EQUAL(symbol, user->getSymbol());
}
