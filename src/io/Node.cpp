#include <openfield/io/Node.h>

using openfield::io::Node;

Node::Node(): 
  mChildren(), mAttributes(), mChildrenReferenced(), mAttributesReferenced()
  {}

Node::Node(const Node& n):
  mChildren(), mAttributes(n.mAttributes),
  mChildrenReferenced(n.mChildrenReferenced),
  mAttributesReferenced(n.mAttributesReferenced) {
  for(size_type i = 0; i < n.getChildrenCount(); ++i) {
    mChildren.push_back(new Node(*n.getChild(i)));
  }
}

Node& Node::operator=(const Node& n) {
  if(this == &n) return *this;
  mAttributes = n.mAttributes;
  mChildrenReferenced = n.mChildrenReferenced;
  mAttributesReferenced = n.mAttributesReferenced;
  for(size_type i = 0; i < n.getChildrenCount(); ++i) {
    mChildren.push_back(new Node(*n.getChild(i)));
  }
  return *this;
}

Node::~Node() {
  for(size_type i = 0; i < getChildrenCount(); ++i) {
    delete mChildren[i];
  }
}

Node* Node::addChild() {
  mChildren.push_back(new Node());
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
