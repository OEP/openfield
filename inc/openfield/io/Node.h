#pragma once
#include <vector>
#include <map>
#include <set>
#include <string>
#include <openfield/Exceptions.h>
#include <boost/lexical_cast.hpp>

namespace openfield {
namespace io {

class Node {
public:
  typedef unsigned long long size_type;
  Node();

  Node& addChild();

  const Node& getChild(size_type i) const { markChild(i); return mChildren[i]; }
        Node& getChild(size_type i)       { markChild(i); return mChildren[i]; }

  template <typename T>
  T get(const std::string& name) const {
    std::map<std::string, std::string>::const_iterator it = mAttributes.find(name);
    if(it != mAttributes.end()) {
      markAttribute(name);
      return boost::lexical_cast<T>(it->second);
    }
    throw AttributeError(name);
  }
  
  template <typename T>
  T get(const std::string& name, const T& def) const {
    try {
      return get<T>(name);
    }
    catch(const AttributeError&) {
      return def;
    }
  }
        
  size_type getChildrenCount() const { return mChildren.size(); }

private:
  std::vector<Node> mChildren;
  std::map<std::string, std::string> mAttributes;
  mutable std::set<size_type> mChildrenReferenced;
  mutable std::set<std::string> mAttributesReferenced;

  void markChild(size_type) const;
  void markAttribute(const std::string&) const;
};

} // namespace io
} // namespace openfield
