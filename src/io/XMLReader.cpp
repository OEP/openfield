#include <cassert>
#include "openfield/io/XMLReader.h"
#include "openfield/Exceptions.h"
#include "openfield/io/Node.h"

using openfield::io::XMLReader;
using openfield::io::Node;

XMLReader::XMLReader():
  mParser(XML_ParserCreate(NULL)), mNodeStack(), mDepth(0)
{
  XML_SetElementHandler(mParser,
                        XMLReader::startElementHandler,
                        XMLReader::endElementHandler);
  XML_SetUserData(mParser, this);
}

XMLReader::~XMLReader() {
  XML_ParserFree(mParser);
}

void XMLReader::read(std::istream& is, Node& root) const {
  std::string buffer;
  std::getline(is, buffer);
  int isFinal;
  mNodeStack.push_back(&root);
  do {
    isFinal = is.eof();
    if(0 == XML_Parse(mParser, buffer.c_str(), buffer.size(), isFinal)) {
      throw ParseError(XML_ErrorString(XML_GetErrorCode(mParser))
                       + std::string(": ")
                       + buffer);
    }
    std::getline(is, buffer);
  } while(!is.eof());
  assert(mDepth == 0);
  assert(mNodeStack.size() == 0);
}

void XMLReader::startElement(const std::string& name, const AttributeMap& attrs) const {
  Node *n = NULL;
  if(mDepth == 0) {
    // special case: we're defining the root
    n = mNodeStack.back();
    n->setName(name);
  }
  else {
    n = mNodeStack.back()->addChild(name);
    mNodeStack.push_back(n);
  }
  ++mDepth;

  for(const AttributeMap::value_type& pair : attrs) {
    n->add(pair.first, pair.second);
  }
}

void XMLReader::endElement(const std::string&) const {
  --mDepth;
  mNodeStack.pop_back();
}

void XMLReader::startElementHandler(void *userData, const XML_Char *name, const XML_Char **attrs) {
  XMLReader *reader = static_cast<XMLReader*>(userData);
  AttributeMap attributeMap;
  const XML_Char **tmp = attrs;
  while(tmp[0] != NULL) {
    attributeMap.insert(std::make_pair(std::string(tmp[0]),
                                       std::string(tmp[1])));
    tmp += 2;
  }
  reader->startElement(name, attributeMap);
}

void XMLReader::endElementHandler(void *userData, const XML_Char *name) {
  XMLReader *reader = static_cast<XMLReader*>(userData);
  reader->endElement(name);
}
