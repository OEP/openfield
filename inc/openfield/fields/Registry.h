#pragma once
#include <openfield/fields/Field.h>
#include <openfield/io/Node.h>
#include <memory>

namespace openfield {
namespace fields {

class Registry {
public:
  typedef std::map<BaseField::Name, BaseField::Factory> Map;

  static Registry& getInstance() {
    static Registry instance;
    return instance;
  }

  template <typename FieldT>
  static void registerField() {
    Registry::getInstance().registerField(FieldT::getTag(), FieldT::factory);
  }
  
  template <typename FieldT>
  static void unregisterField() {
    Registry::getInstance().unregisterField(FieldT::getTag());
  }

  void registerField(const BaseField::Name&, BaseField::Factory);
  void unregisterField(const BaseField::Name&);

  BaseField::Ptr create(const io::Node&) const;

  template <typename FieldT>
  static typename FieldT::Ptr get(const io::Node& n) {
    typename FieldT::Ptr p = std::dynamic_pointer_cast<FieldT>(Registry::getInstance().create(n));
    if(!p.get()) {
      throw TypeError("node " + n.getName() + " is not of type " + typeid(FieldT).name());
    }
    return p;
  }
private:
  Registry(): mMap() {}
  Registry(const Registry&);
  Registry& operator=(const Registry&);

  Map mMap;
};

} // namespace fields
} // namespace openfield
