#include <cppunit/extensions/HelperMacros.h>
#include <openfield/io/XMLWriter.h>
#include <openfield/io/Node.h>
using openfield::io::XMLWriter;
using openfield::io::Node;

class IOTest : public CppUnit::TestCase {
  CPPUNIT_TEST_SUITE( IOTest );
  CPPUNIT_TEST( testXML );
  CPPUNIT_TEST_SUITE_END();

public:
  IOTest(): CppUnit::TestCase(),
    root("openfield") {}
  
  void setUp();
  void tearDown();

  std::string makeTemp() const;

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

std::string IOTest::makeTemp() const {
  char *env = getenv("TMPDIR");
  std::string temp = std::string(env? env : "/tmp");
  temp = temp + "/openfield-testXXXXXX";
  char *dup = strdup(temp.c_str());
  mkstemp(dup);
  temp = dup;
  free(dup);
  return temp;
}

void IOTest::testXML() {
  XMLWriter writer("  ");
  std::string path = makeTemp();
  std::ofstream os(path);
  writer.write(os, root);
  std::cout << path << std::endl;
}

CPPUNIT_TEST_SUITE_REGISTRATION(IOTest);