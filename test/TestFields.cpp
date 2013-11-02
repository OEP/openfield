#include <cppunit/extensions/HelperMacros.h>
#include <openfield/Types.h>

class FieldsTest : public CppUnit::TestCase {
  CPPUNIT_TEST_SUITE( FieldsTest );
  CPPUNIT_TEST( testSphere );
  CPPUNIT_TEST_SUITE_END();

public:
  FieldsTest(): CppUnit::TestCase(), sphere() {}
  
  void setUp();
  void tearDown();

  void testSphere();

private:
  openfield::ScalarField::Ptr sphere;
};

void FieldsTest::setUp() {
  using namespace openfield;
  sphere = Sphere::create({0, 0, 0}, 1);
}

void FieldsTest::tearDown() {
}

void FieldsTest::testSphere() {
  using namespace openfield;
  CPPUNIT_ASSERT( sphere->eval({0,0,0}) == 1 );
  CPPUNIT_ASSERT( sphere->eval({1,0,0}) == 0 );
  CPPUNIT_ASSERT( sphere->eval({0,1,0}) == 0 );
  CPPUNIT_ASSERT( sphere->eval({0,0,1}) == 0 );
  CPPUNIT_ASSERT( sphere->eval({-1,0,0}) == 0 );
  CPPUNIT_ASSERT( sphere->eval({0,-1,0}) == 0 );
  CPPUNIT_ASSERT( sphere->eval({0,0,-1}) == 0 );
}

CPPUNIT_TEST_SUITE_REGISTRATION(FieldsTest);