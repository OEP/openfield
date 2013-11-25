#include <openfield/io/Node.h>
#include <openfield/math/Vec.h>
#include "BaseTest.h"

using openfield::io::Node;

class NodeTest : public BaseTest {
  CPPUNIT_TEST_SUITE( NodeTest );
  CPPUNIT_TEST( testAddChild );
  CPPUNIT_TEST( testErrors );
  CPPUNIT_TEST( testStandardForm );
  CPPUNIT_TEST( testAssignment );
  CPPUNIT_TEST( testAddVec3f );
  CPPUNIT_TEST_SUITE_END();

public:
  NodeTest():
    BaseTest(), root("Root")
  { }
  
  void setUp();
  void tearDown();

  void testAddChild();
  void testErrors();
  void testStandardForm();
  void testAssignment();
  void testAddVec3f();

private:
  NodeTest(const NodeTest&);
  NodeTest& operator=(const NodeTest&);
  
  openfield::io::Node root;

  static void assertSetUp(const Node* n);
};

void NodeTest::setUp() {
  root = openfield::io::Node("Root");
  Node *a = root.addChild("A");
  Node *b = root.addChild("B");
  a->addChild("C");
  a->addChild("D");
  b->addChild("E");
  b->addChild("F");
}

void NodeTest::tearDown() {
}

void NodeTest::assertSetUp(const Node* n) {
  CPPUNIT_ASSERT(n->getChildrenCount() == 2);

  const Node *a = n->getChild(0), *b = n->getChild(1);
  CPPUNIT_ASSERT(a->getChildrenCount() == 2);
  CPPUNIT_ASSERT(b->getChildrenCount() == 2);

  const Node
    *c = a->getChild(0),
    *d = a->getChild(1),
    *e = b->getChild(0),
    *f = b->getChild(1);
  CPPUNIT_ASSERT(c->getChildrenCount() == 0);
  CPPUNIT_ASSERT(d->getChildrenCount() == 0);
  CPPUNIT_ASSERT(e->getChildrenCount() == 0);
  CPPUNIT_ASSERT(f->getChildrenCount() == 0);
}

void NodeTest::testAddChild() {
  NodeTest::assertSetUp(&root);
}

void NodeTest::testStandardForm() {
  Node a = root;
  Node b("B");
  b = root;

  NodeTest::assertSetUp(&a);
  NodeTest::assertSetUp(&b);
}

void NodeTest::testErrors() {
  // root node gets constructed as referenced
  Node t("t");
  CPPUNIT_ASSERT_NO_THROW(t.assertFullyReferenced());

  // unmarking has no effect on root node
  t.unmark();
  CPPUNIT_ASSERT_NO_THROW(t.assertFullyReferenced());

  // child nodes get constructed as unreferenced
  t.addChild("tchild");
  CPPUNIT_ASSERT_THROW(t.assertFullyReferenced(), openfield::UnreferencedNodeError);

  // getChild() causes child to become referenced
  t.getChild(0);
  CPPUNIT_ASSERT_NO_THROW(t.assertFullyReferenced());

  // test safe and unsafe interfaces of get()
  CPPUNIT_ASSERT_NO_THROW(t.get<int>("test", 1));
  CPPUNIT_ASSERT_THROW(t.get<int>("test"), openfield::AttributeError);

  // adding attributes twices throws AttributeError
  CPPUNIT_ASSERT_NO_THROW(t.add<int>("test", 0));
  CPPUNIT_ASSERT_THROW(t.add<int>("test", 0), openfield::AttributeError);

  // attributes don't get added as referenced
  CPPUNIT_ASSERT_THROW(t.assertFullyReferenced(), openfield::UnreferencedAttributeError);

  // get() causes attributes to become referenced
  CPPUNIT_ASSERT_NO_THROW(t.get<int>("test"));
  CPPUNIT_ASSERT_NO_THROW(t.assertFullyReferenced());
  CPPUNIT_ASSERT_NO_THROW(t.get<int>("test", 1));
  CPPUNIT_ASSERT_NO_THROW(t.assertFullyReferenced());
}

void NodeTest::testAssignment() {
  Node t, s;
  t.addChild(""); // check if child gets cleaned up after assignment
  t = s;
  CPPUNIT_ASSERT(s == t);
}

void NodeTest::testAddVec3f() {
  using openfield::math::Vec3f;

  Node node;
  Vec3f value({1, 2, 3});
  Vec3f out;
  CPPUNIT_ASSERT_NO_THROW( node.add("vector", value) );
  CPPUNIT_ASSERT_NO_THROW( out = node.get<Vec3f>("vector") );
  CPPUNIT_ASSERT( norm2(out - value) < 1e-6 );
}

CPPUNIT_TEST_SUITE_REGISTRATION(NodeTest);
