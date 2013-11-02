#include <openfield/io/Node.h>

using openfield::io::Node;

Node::Node(): 
  mChildren(), mAttributes(), mChildrenReferenced(), mAttributesReferenced()
  {}

Node& Node::addChild() {
  mChildren.push_back(Node());
  return getChild(mChildren.size()-1);
}

void Node::markChild(Node::size_type i) const {
  if(i >= mChildren.size()) {
    throw IndexError(std::to_string(i));
  }
  mChildrenReferenced.insert(i);
}

void Node::markAttribute(const std::string& name) const {
  std::map<std::string, std::string>::const_iterator it = mAttributes.find(name);
  if(it == mAttributes.end()) {
    throw AttributeError(name);
  }
  mAttributesReferenced.insert(name);
}
