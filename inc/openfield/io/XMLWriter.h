#pragma once
#include <ostream>
#include <map>
#include "openfield/io/Writer.h"

namespace openfield {
namespace io {

class XMLWriter : public Writer {
public:
  //! Character encoding map type
  typedef std::map<char, std::string> EncodeMap;

  //! Encode given string for storing inside quoted portion of an attribute
  static std::string encode(const std::string&);

  //! Get the character encoding map.
  static const EncodeMap& getEncodeMap();

  //! Get reserved characters for quoted portion of attribute
  static const std::string& getReservedChars();

  //! Write unformatted XML data.
  XMLWriter();

  //! Write formatted data using given string as indent
  XMLWriter(const std::string&);

  //! Write the node to the given output stream.
  virtual void write(std::ostream&, const Node&) const; 
private:
  bool mPretty;
  std::string mIndent;
  mutable unsigned mDepth;
};

} // namespace io
} // namespace openfield
