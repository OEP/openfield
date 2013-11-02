#include <cppunit/extensions/HelperMacros.h>
#include <openfield/io/Node.h>

class NodeTest : public CppUnit::TestCase {
  CPPUNIT_TEST_SUITE( NodeTest );
  CPPUNIT_TEST( testAddChild );
  CPPUNIT_TEST_SUITE_END();

public:
  NodeTest(): CppUnit::TestCase(),
    root(), a(NULL), b(NULL), c(NULL), d(NULL), e(NULL), f(NULL) {}
  
  void setUp();
  void tearDown();

  void testAddChild();

private:
  NodeTest(const NodeTest&);
  NodeTest& operator=(const NodeTest&);
  
  openfield::io::Node root, *a, *b, *c, *d, *e, *f;
};

void NodeTest::setUp() {
  root = openfield::io::Node();
  a = &(root.addChild());
  b = &(root.addChild());
  CPPUNIT_ASSERT(a == &(root.getChild(1)) || a == &(root.getChild(0)));
  //c = &(a->addChild());
  //d = &a->addChild();
  //e = &b->addChild();
  //f = &b->addChild();
}

void NodeTest::tearDown() {
  a = NULL;
  b = NULL;
}

void NodeTest::testAddChild() {
  CPPUNIT_ASSERT(root.getChildrenCount() == 2);
}

CPPUNIT_TEST_SUITE_REGISTRATION(NodeTest);
