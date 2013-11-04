#pragma once
#include <exception>
namespace openfield {

class Exception : public std::exception {
public:
  virtual const char* what() const throw() {
    try {
      return mMessage.c_str();
    }
    catch(...) {
      return NULL;
    }
  }

  const std::string& getCause() const { return mCause; }

  virtual ~Exception() throw() {}
protected:
  Exception() throw(): mMessage(), mCause() {}
  Exception(const char *typeName, const std::string *cause = NULL) throw():
    mMessage(), mCause() {
    try {
      if(typeName) { 
        mMessage = typeName;
      }
      if(cause) {
        mMessage += ": " + (*cause);
        mCause = *cause;
      }
    }
    catch(...) {}
  }
private:
  std::string mMessage, mCause;
};

#define OPENFIELD_EXCEPTION(_typename) \
class _typename : public Exception { \
public: \
  _typename() throw(): Exception(#_typename) {} \
  explicit _typename(const std::string& m) throw(): Exception(#_typename, &m) {}\
};

OPENFIELD_EXCEPTION(AttributeError)
OPENFIELD_EXCEPTION(KeyError)
OPENFIELD_EXCEPTION(IndexError)
OPENFIELD_EXCEPTION(TypeError)
OPENFIELD_EXCEPTION(UnreferencedAttributeError)
OPENFIELD_EXCEPTION(UnreferencedNodeError)

#undef OPENFIELD_EXCEPTION


} // namespace openfield
