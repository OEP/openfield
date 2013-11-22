#include <openfield/openfield.h>
#include <openfield/fields/fields.h>
#include <openfield/io/Node.h>
#include "BaseTest.h"

using namespace openfield::fields;
using openfield::io::Node;
using openfield::math::Vec3f;

class FieldsTest : public BaseTest {
  CPPUNIT_TEST_SUITE( FieldsTest );
  CPPUNIT_TEST( testRegistry );
  CPPUNIT_TEST( testSphere );
  CPPUNIT_TEST_SUITE_END();

public:
  FieldsTest():
    BaseTest(), sphere(), registry(Registry::getInstance())
  { }
  
  void setUp();
  void tearDown();

  void testSphere();
  void testRegistry();

private:
  ScalarField::Ptr sphere;
  Registry& registry;
};

void FieldsTest::setUp() {
  openfield::initialize();
  sphere = Sphere::create({0, 0, 0}, 1);
}

void FieldsTest::tearDown() {
  openfield::uninitialize();
}

void FieldsTest::testRegistry() {
  CPPUNIT_ASSERT( registry.getName<Sphere>() == Sphere::getTag() );
  CPPUNIT_ASSERT_THROW( registry.getName<int>(), openfield::KeyError );
  CPPUNIT_ASSERT_THROW( registry.create(Node("Not_Registered")), openfield::KeyError );
}

void FieldsTest::testSphere() {
  CPPUNIT_ASSERT( sphere->eval({0,0,0}) == 1 );
  CPPUNIT_ASSERT( sphere->eval({1,0,0}) == 0 );
  CPPUNIT_ASSERT( sphere->eval({0,1,0}) == 0 );
  CPPUNIT_ASSERT( sphere->eval({0,0,1}) == 0 );
  CPPUNIT_ASSERT( sphere->eval({-1,0,0}) == 0 );
  CPPUNIT_ASSERT( sphere->eval({0,-1,0}) == 0 );
  CPPUNIT_ASSERT( sphere->eval({0,0,-1}) == 0 );

  Node n(Sphere::getTag());
  n.add<float>("radius", 1.0f);
  n.add<Vec3f>("center", {1, 0, 0});
  ScalarField::Ptr p = registry.get<ScalarField>(n);
}

CPPUNIT_TEST_SUITE_REGISTRATION(FieldsTest);
