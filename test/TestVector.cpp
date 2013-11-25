#include <openfield/Types.h>
#include "BaseTest.h"

class VectorTest : public BaseTest {
  CPPUNIT_TEST_SUITE( VectorTest );
  CPPUNIT_TEST( testConstructor );
  CPPUNIT_TEST( testStream );
  CPPUNIT_TEST_SUITE_END();

public:
  VectorTest(): BaseTest(),
    x(), y(), z(), zero(), ones() {}

  void setUp();
  void tearDown();

  void testConstructor();
  void testStream();

private:
  openfield::Vec3f x, y, z, zero, ones;
};

void VectorTest::setUp() {
  using openfield::Vec3f;
  x = {1, 0, 0};
  y = {0, 1, 0};
  z = {0, 0, 1};
  zero = Vec3f(0);
  ones = Vec3f(1);
}

void VectorTest::tearDown() {
}

void VectorTest::testConstructor() {
  using openfield::Vec3f;
 
  CPPUNIT_ASSERT(x[0] == 1); CPPUNIT_ASSERT(x[1] == 0); CPPUNIT_ASSERT(x[2] == 0); 
  CPPUNIT_ASSERT(y[0] == 0); CPPUNIT_ASSERT(y[1] == 1); CPPUNIT_ASSERT(y[2] == 0); 
  CPPUNIT_ASSERT(z[0] == 0); CPPUNIT_ASSERT(z[1] == 0); CPPUNIT_ASSERT(z[2] == 1); 
}

void VectorTest::testStream() {
  using openfield::Vec3f;
  
  Vec3f in = {1, 2, 3}, out;
  std::stringstream ss;
  ss << in;
  ss >> out;
  CPPUNIT_ASSERT( norm2(in-out) < 1e-6 );
}

CPPUNIT_TEST_SUITE_REGISTRATION(VectorTest);
