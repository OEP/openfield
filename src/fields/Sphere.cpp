#include "openfield/fields/Sphere.h"
#include "openfield/io/Node.h"
#include "openfield/fields/Registry.h"

using openfield::fields::BaseField;
using openfield::fields::Sphere;
using openfield::fields::Registry;
using openfield::io::Node;

BaseField::Ptr Sphere::factory(const Node& n) {
  return Sphere::create(n.get<Vec3f>("center"), n.get<float>("radius"));
}

void Sphere::store(Node& n) const {
  Registry& registry = Registry::getInstance();
  n.setName(registry.getName<Sphere>());
  n.add("center", mCenter);
  n.add("radius", mRadius);
}
