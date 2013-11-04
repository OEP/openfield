#pragma once
#include <openfield/fields/Field.h>

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

  void registerField(const BaseField::Name&, BaseField::Factory);
  void unregisterField(const BaseField::Name&);

  BaseField::Ptr create(const io::Node&) const;
private:
  Registry(): mMap() {}
  Registry(const Registry&);
  Registry& operator=(const Registry&);

  Map mMap;
};

} // namespace fields
} // namespace openfield
