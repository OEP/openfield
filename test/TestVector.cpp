#include <cppunit/extensions/HelperMacros.h>
#include <openfield/Vec.h>

class VectorTest : public CppUnit::TestCase {
  CPPUNIT_TEST_SUITE( VectorTest );
  CPPUNIT_TEST( testConstructor );
  CPPUNIT_TEST_SUITE_END();

public:
  VectorTest(): CppUnit::TestCase(),
    x(), y(), z(), zero(), ones() {}

  void setUp();
  void tearDown();

  void testConstructor();

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


CPPUNIT_TEST_SUITE_REGISTRATION(VectorTest);
