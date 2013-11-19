#pragma once
#include <exception>
namespace openfield {

class Exception : public std::exception {
public:
  //! Get a character array describing what caused the exception.
  virtual const char* what() const throw() {
    try {
      return mMessage.c_str();
    }
    catch(...) {
      return NULL;
    }
  }

  //! Similar to what(), but strip the type name from the message.
  const std::string& getCause() const { return mCause; }

  virtual ~Exception() throw() {}
protected:
  //! Initialize exception with no message
  Exception() throw(): mMessage(), mCause() {}

  //! Initialize exception with typename and a string describing the cause
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

//! @cond Doxygen.Suppress
OPENFIELD_EXCEPTION(AttributeError)
OPENFIELD_EXCEPTION(KeyError)
OPENFIELD_EXCEPTION(ParseError)
OPENFIELD_EXCEPTION(IndexError)
OPENFIELD_EXCEPTION(TypeError)
OPENFIELD_EXCEPTION(UnreferencedAttributeError)
OPENFIELD_EXCEPTION(UnreferencedNodeError)
//! @endcond Doxygen.Suppress

#undef OPENFIELD_EXCEPTION


} // namespace openfield
