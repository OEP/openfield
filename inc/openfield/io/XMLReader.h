#pragma once
#include <map>
#include <list>
#include <expat.h>
#include "openfield/io/Reader.h"

namespace openfield {
namespace io {

class XMLReader {
public:
  XMLReader();
  virtual ~XMLReader();

  //! Read XML document from input stream into given node 
  virtual void read(std::istream&, Node&) const;
private:
  typedef std::map<std::string, std::string> AttributeMap;
  typedef std::list<Node*> NodeList;

  XMLReader(const XMLReader&);
  XMLReader& operator=(const XMLReader&);

  void startElement(const std::string&, const AttributeMap&) const;
  void endElement(const std::string&) const;

  static void startElementHandler(void*, const XML_Char*, const XML_Char**);
  static void endElementHandler(void*, const XML_Char*);

  XML_Parser mParser;
  mutable NodeList mNodeStack;
  mutable unsigned mDepth;
};

} // namespace io
} // namespace openfield
