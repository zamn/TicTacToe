#ifndef USERTEST_H
#define USERTEST_H

#include <cppunit/extensions/HelperMacros.h>
#include "../User.h"

using namespace std;

class UserTest : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(UserTest);
	CPPUNIT_TEST(testConstructor);
	CPPUNIT_TEST(testGetNick);
	CPPUNIT_TEST(testGetSymbol);
	CPPUNIT_TEST_SUITE_END();

public:
	void testGetNick();
	void testGetSymbol();
	void tearDown();
	void setUp();
	void testConstructor();

private:
	string nick;
	char symbol;
	User *user;
};
#endif // USERTEST_H
