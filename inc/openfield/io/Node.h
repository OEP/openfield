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

  //! Construct a node with given name.
  Node(const std::string&);

  //! Copy constructor
  Node(const Node&);

  //! Overloaded assignment
  Node& operator=(const Node&);

  //! Destructor
  ~Node();

  //! Add a child.
  Node* addChild(const std::string&);

  //! Const access to child
  const Node* getChild(size_type i) const { markChild(i); return mChildren[i]; }

  //! Non-const access to child
        Node* getChild(size_type i)       { markChild(i); return mChildren[i]; }

  //! Retrieve an attribute, throwing openfield::AttributeError if none is found.
  template <typename T>
  T get(const std::string& name) const {
    std::map<std::string, std::string>::const_iterator it = mAttributes.find(name);
    if(it != mAttributes.end()) {
      markAttribute(name);
      return boost::lexical_cast<T>(it->second);
    }
    throw AttributeError(name);
  }
  
  //! Retrieve an attribute.
  template <typename T>
  T get(const std::string& name, const T& def) const {
    try {
      return get<T>(name);
    }
    catch(const AttributeError&) {
      return def;
    }
  }
       
  //! Returns count of children.
  size_type getChildrenCount() const { return mChildren.size(); }

  //! Unmark all nodes and node attributes as referenced (excepting the root)
  void unmark() const;
  
  //! Assert that all nodes and attributes are referenced.
  void assertFullyReferenced() const;

private:
  Node(); // disabled

  //! Private child node constructor
  Node(const std::string&, bool);

  std::string mName;
  std::vector<Node*> mChildren;
  std::map<std::string, std::string> mAttributes;
  bool mRoot;
  mutable bool mReferenced;
  mutable std::set<std::string> mAttributesReferenced;

  void markChild(size_type) const;
  void markAttribute(const std::string&) const;
  void assertAttributeReferenced(const std::string&) const;

};

} // namespace io
} // namespace openfield
