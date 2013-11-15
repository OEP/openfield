#include <cppunit/extensions/HelperMacros.h>
#include <openfield/openfield.h>
#include <openfield/fields/fields.h>
#include <openfield/io/Node.h>

using namespace openfield::fields;
using openfield::io::Node;
using openfield::math::Vec3f;

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
  ScalarField::Ptr sphere;
};

void FieldsTest::setUp() {
  openfield::initialize();
  sphere = Sphere::create({0, 0, 0}, 1);
}

void FieldsTest::tearDown() {
  openfield::uninitialize();
}

void FieldsTest::testSphere() {
  CPPUNIT_ASSERT( sphere->eval({0,0,0}) == 1 );
  CPPUNIT_ASSERT( sphere->eval({1,0,0}) == 0 );
  CPPUNIT_ASSERT( sphere->eval({0,1,0}) == 0 );
  CPPUNIT_ASSERT( sphere->eval({0,0,1}) == 0 );
  CPPUNIT_ASSERT( sphere->eval({-1,0,0}) == 0 );
  CPPUNIT_ASSERT( sphere->eval({0,-1,0}) == 0 );
  CPPUNIT_ASSERT( sphere->eval({0,0,-1}) == 0 );

  Registry &reg = Registry::getInstance();

  Node n(Sphere::getTag());
  n.add<float>("radius", 1.0f);
  n.add<Vec3f>("center", {1, 0, 0});
  ScalarField::Ptr p = reg.get<ScalarField>(n);

  CPPUNIT_ASSERT( reg.getName<Sphere>() == Sphere::getTag() );
}

CPPUNIT_TEST_SUITE_REGISTRATION(FieldsTest);
