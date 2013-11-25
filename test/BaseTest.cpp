#include "BaseTest.h"
#include <cstring>

std::string BaseTest::makeTemp() const {
  char *env = getenv("TMPDIR");
  std::string temp = std::string(env? env : "/tmp");
  temp = temp + "/openfield-testXXXXXX";
  char *dup = strdup(temp.c_str());
  mkstemp(dup);
  temp = dup;
  free(dup);
  return temp;
}
