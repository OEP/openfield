#include <cppunit/extensions/HelperMacros.h>
#include <openfield/io/XMLWriter.h>
#include <openfield/io/XMLReader.h>
#include <openfield/io/Node.h>
#include "BaseTest.h"

using openfield::io::XMLWriter;
using openfield::io::XMLReader;
using openfield::io::Node;

class IOTest : public BaseTest {
  CPPUNIT_TEST_SUITE( IOTest );
  CPPUNIT_TEST( testXML );
  CPPUNIT_TEST_SUITE_END();

public:
  IOTest(): BaseTest(),
    root("openfield")
  { }
  
  void setUp();
  void tearDown();

  void testXML();

private:
  IOTest(const IOTest&);
  IOTest& operator=(const IOTest&);

  Node root;
};

void IOTest::setUp() {
  root.add("version", "test");
  root.add("author", "test");
  Node *c1 = root.addChild("child1");
  root.addChild("child2");
  c1->add("num", 1);
  c1->add("str", "'\"<>&<!--CDATA-->");
}

void IOTest::tearDown() {
}

void IOTest::testXML() {
  XMLWriter writer("  ");
  std::string path = makeTemp();
  std::ofstream os(path);
  writer.write(os, root);
  os.close();

  std::ifstream is(path);
  XMLReader reader;
  Node in("root");
  reader.read(is, in);
  CPPUNIT_ASSERT(in == root);
}

CPPUNIT_TEST_SUITE_REGISTRATION(IOTest);
