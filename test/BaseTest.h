#include <cppunit/extensions/HelperMacros.h>

class BaseTest : public CppUnit::TestCase {
public:
  BaseTest():
    CppUnit::TestCase()
  { }
  
  //! Return a path to a new temporary file
  std::string makeTemp() const;
};
