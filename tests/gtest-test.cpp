#include "gtest/gtest.h"
#include <iostream>

class test_fixture : public testing::Test
{
public:
  test_fixture() : a(10)
  {}
  int a;
};

TEST( ggtest, test )
{
  std::cout << "gtest::test\n";
  int a = 10;
  EXPECT_EQ( a, 10 );
}

TEST( ptest, test1 )
{
  std::cout << "gtest::test\n";
  int a = 10;
  EXPECT_EQ( a, 10 );
}

TEST( itest, test2 )
{
  std::cout << "gtest::test\n";
  int a = 10;
  EXPECT_EQ( a, 10 );
}

TEST( mtest, test3 )
{
  std::cout << "gtest::test\n";
  int a = 10;
  EXPECT_EQ( a, 10 );
}

TEST_F( test_fixture, fixture_test )
{
  std::cout << "test_fixture::fixture_test\n";
  EXPECT_EQ( a, 10 );
}

TEST_F( test_fixture, one )
{
}

TEST_F( test_fixture, two )
{
}