#include "openfield/fields/Sphere.h"
#include "openfield/io/Node.h"
#include "openfield/fields/Visitor.h"

using openfield::fields::BaseField;
using openfield::fields::Sphere;
using openfield::fields::Visitor;
using openfield::io::Node;

BaseField::Ptr Sphere::factory(const Node& n) {
  return Sphere::create(n.get<Vec3f>("center"), n.get<float>("radius"));
}

void Sphere::accept(Visitor& v) {
  v.visitSphere(*this);
}
