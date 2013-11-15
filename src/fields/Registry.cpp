#include <openfield/fields/Registry.h>
#include <openfield/io/Node.h>
#include <openfield/Exceptions.h>

using openfield::fields::Registry;
using openfield::fields::BaseField;

Registry::Registry():
  mMap(), mReverseMap()
{ }

Registry& Registry::getInstance() {
  static Registry sInstance;
  return sInstance;
}

void Registry::registerField(const BaseField::Name& n, const std::string& typeid_name, const BaseField::Factory f) {
  if(mMap.count(n) == 1) {
    throw KeyError(n + ": already registered");
  }
  mMap[n] = f;
  mReverseMap[typeid_name] = n;
}

void Registry::unregisterField(const BaseField::Name& n) {
  mMap.erase(n);
}

BaseField::Ptr Registry::create(const io::Node& node) const {
  Map::const_iterator it = mMap.find(node.getName());
  if(it == mMap.end()) {
    throw KeyError(node.getName() + ": not a registered field type");
  }
  return it->second(node);
}
