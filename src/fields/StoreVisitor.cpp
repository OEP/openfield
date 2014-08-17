#include <openfield/fields/StoreVisitor.h>
#include <openfield/fields/Definitions.h>
#include <iostream>
#include <openfield/fields/Registry.h>

using namespace openfield::fields;

const unsigned StoreVisitor::VERSION = 1;

StoreVisitor::StoreVisitor(): 
  mRoot("openfield"), mStack()
{
  mRoot.add("version", StoreVisitor::VERSION);
  mStack.push_back(&mRoot);
}

bool StoreVisitor::enter(BaseField&) {
  mStack.push_back(top().addChild());
  return true;
}

void StoreVisitor::exit(BaseField&) {
  mStack.pop_back();
}

void StoreVisitor::visitSphere(Sphere& s) {
  Registry& registry = Registry::getInstance();
  top().setName(registry.getName<Sphere>());
  top().add("radius", s.getRadius());
  top().add("center", s.getCenter());
}

void StoreVisitor::visitScalarPlus(ScalarPlus& s) {
  Registry& registry = Registry::getInstance();
  top().setName(registry.getName<ScalarPlus>());
  s.getLhs()->dispatch(*this);
  s.getRhs()->dispatch(*this);
}
