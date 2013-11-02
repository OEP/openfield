#include <openfield/io/Node.h>

using openfield::io::Node;

Node::Node(const std::string& n): 
  mName(n), mChildren(), mAttributes(), mRoot(true), mReferenced(true), mAttributesReferenced()
  {}

Node::Node(const std::string& n, bool b): 
  mName(n), mChildren(), mAttributes(), mRoot(false), mReferenced(b), mAttributesReferenced()
  {}

Node::Node(const Node& n):
  mName(n.mName), mChildren(), mAttributes(n.mAttributes),
  mRoot(n.mRoot), mReferenced(n.mReferenced),
  mAttributesReferenced(n.mAttributesReferenced) {
  for(size_type i = 0; i < n.getChildrenCount(); ++i) {
    mChildren.push_back(new Node(*n.getChild(i)));
  }
}

Node& Node::operator=(const Node& n) {
  if(this == &n) return *this;
  mName = n.mName;
  mAttributes = n.mAttributes;
  mReferenced = n.mReferenced;
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

Node* Node::addChild(const std::string& n) {
  mChildren.push_back(new Node(n, false));
  return mChildren[mChildren.size()-1];
}

void Node::assertFullyReferenced() const {
  using std::map;
  using std::string;

  if(!mReferenced) {
    throw UnreferencedNodeError(mName);
  }

  for(size_type i = 0; i < getChildrenCount(); ++i) {
    mChildren[i]->assertFullyReferenced();
  }
  map<string, string>::const_iterator it = mAttributes.begin();
  while(it != mAttributes.end()) {
    assertAttributeReferenced(it->first);
    ++it;
  }
}

void Node::unmark() const {
  // root should always be considered referenced, except for its attributes
  mReferenced = mRoot;
  mAttributesReferenced.clear();
  for(size_type i = 0; i < getChildrenCount(); ++i) {
    mChildren[i]->unmark();
  }
}

void Node::assertAttributeReferenced(const std::string& n) const {
  if(mAttributesReferenced.count(n) == 0) {
    throw UnreferencedAttributeError(n);
  }
}

void Node::markChild(Node::size_type i) const {
  if(i >= mChildren.size()) {
    throw IndexError(std::to_string(i));
  }
  mChildren[i]->mReferenced = true;
}

void Node::markAttribute(const std::string& name) const {
  std::map<std::string, std::string>::const_iterator it = mAttributes.find(name);
  if(it == mAttributes.end()) {
    throw AttributeError(name);
  }
  mAttributesReferenced.insert(name);
}
