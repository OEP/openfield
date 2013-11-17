#pragma once
#include <ostream>
#include <map>
#include "openfield/io/Writer.h"

namespace openfield {
namespace io {

class XMLWriter : public Writer {
public:
  typedef std::map<char, std::string> EncodeMap;

  static std::string encode(const std::string&);
  static const EncodeMap& getEncodeMap();
  static const std::string& getReservedChars();

  //! Write unformatted XML data.
  XMLWriter();

  //! Write formatted data using given string as indent
  XMLWriter(const std::string&);

  virtual void write(std::ostream&, const Node&) const; 
private:
  bool mPretty;
  std::string mIndent;
  mutable unsigned mDepth;
};

} // namespace io
} // namespace openfield
