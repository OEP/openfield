#pragma once

#include <list>
#include <openfield/io/Node.h>
#include <openfield/fields/Visitor.h>

namespace openfield {
namespace fields {

class StoreVisitor : public Visitor {
public:
  static const unsigned VERSION;

  StoreVisitor();

  const io::Node& getRoot() const { return mRoot; }

  virtual bool enter(BaseField&);
  virtual void exit(BaseField&);

  void visitSphere(Sphere&);

private:
  io::Node mRoot;
  std::list<io::Node*> mStack;

  const io::Node& top() const { return *mStack.back(); }
        io::Node& top()       { return *mStack.back(); }

};

} // namespace fields
} // namespace openfield
