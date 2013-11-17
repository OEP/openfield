#include "openfield/io/XMLWriter.h"
#include "openfield/io/Node.h"

using openfield::io::XMLWriter;
using openfield::io::Node;

XMLWriter::XMLWriter():
  mPretty(false), mIndent(), mDepth(0)
{ }

XMLWriter::XMLWriter(const std::string& indent):
  mPretty(true), mIndent(indent), mDepth(0)
{ }

const XMLWriter::EncodeMap& XMLWriter::getEncodeMap() {
  static EncodeMap sEncodeMap;
  static bool sInitialized = false;
  if(!sInitialized) {
    sEncodeMap['"'] = "&quot;";
    sEncodeMap['\''] = "&apos;";
    sEncodeMap['&'] = "&amp;";
    sEncodeMap['<'] = "&lt;";
    sEncodeMap['>'] = "&gt;";
  }
  return sEncodeMap;
}

const std::string& XMLWriter::getReservedChars() {
  static std::string sReservedChars;
  static bool sInitialized = false;
  if(!sInitialized) {
    const EncodeMap& emap = getEncodeMap();
    for(EncodeMap::value_type pair : emap) {
      sReservedChars += pair.first;
    }
  }
  return sReservedChars;
}

std::string XMLWriter::encode(const std::string& s) {
  std::string::size_type pos = 0;
  std::string out = s;
  const EncodeMap& emap = getEncodeMap();
  const std::string& reserved = getReservedChars();
  while(std::string::npos != (pos = out.find_first_of(reserved, pos))) {
    out.replace(pos, 1, emap.at(out[pos]));
    ++pos;
  }
  return out;
}

void XMLWriter::write(std::ostream& os, const Node& node) const {
  os << "<" << node.getName();
  for(const Node::AttributePair& pair : node.getAttributes()) {
    os << " " << pair.first << "=\"" << encode(pair.second) << "\"";
  }
  if(node.getChildrenCount() == 0) {
    os << " />";
    if(mPretty) {
      os << std::endl;
    }
    return;
  }

  os << ">";
  if(mPretty) {
    os << std::endl;
  }
  for(unsigned i = 0; i < node.getChildrenCount(); ++i) {
    if(mPretty) {
      ++mDepth;
      for(unsigned j = 0; j < mDepth; ++j) {
        os << mIndent;
      }
    }
    const Node *child = node.getChild(i);
    write(os, *child);
    if(mPretty) {
      --mDepth;
    }
  }
  os << "</" << node.getName() << ">";
  if(mPretty) {
    os << std::endl;
  }
}
