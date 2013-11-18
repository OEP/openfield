#include "openfield/io/XMLReader.h"
#include "openfield/Exceptions.h"

using openfield::io::XMLReader;
using openfield::io::Node;

XMLReader::XMLReader():
  mParser(XML_ParserCreate(NULL))
{
  XML_SetElementHandler(mParser,
                        XMLReader::startElementHandler,
                        XMLReader::endElementHandler);
}

XMLReader::~XMLReader() {
  XML_ParserFree(mParser);
}

void XMLReader::read(std::istream& is, Node&) const {
  std::string buffer;
  std::getline(is, buffer);
  int isFinal;
  do {
    isFinal = is.eof();
    if(0 == XML_Parse(mParser, buffer.c_str(), buffer.size(), isFinal)) {
      throw ParseError(XML_ErrorString(XML_GetErrorCode(mParser))
                       + std::string(": ")
                       + buffer);
    }
    std::getline(is, buffer);
  } while(!is.eof());
}

void XMLReader::startElement(const std::string& name, const AttributeMap&) const {
}

void XMLReader::endElement(const std::string&) const {
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
