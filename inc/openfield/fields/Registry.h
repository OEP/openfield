#pragma once
#include <openfield/fields/Field.h>
#include <openfield/io/Node.h>
#include <memory>

namespace openfield {
namespace fields {

class Registry {
public:
  //! Registry::Map maps field names to their factory functions
  typedef std::map<BaseField::Name, BaseField::Factory> Map;

  //! Registry::ReverseMap maps C++ names to field names.
  typedef std::map<std::string, BaseField::Name> ReverseMap;

  static Registry& getInstance();

  template <typename FieldT>
  void registerField() {
    Registry::getInstance().registerField(FieldT::getTag(), FieldT::factory);
  }
  
  template <typename FieldT>
  void unregisterField() {
    Registry::getInstance().unregisterField(FieldT::getTag());
  }

  template <typename FieldT>
  typename FieldT::Ptr get(const io::Node& n) {
    typename FieldT::Ptr p = std::dynamic_pointer_cast<FieldT>(Registry::getInstance().create(n));
    if(!p.get()) {
      throw TypeError("node " + n.getName() + " is not of type " + typeid(FieldT).name());
    }
    return p;
  }
  
  BaseField::Ptr create(const io::Node&) const;

private:
  Registry();
  Registry(const Registry&);
  Registry& operator=(const Registry&);
  
  void registerField(const BaseField::Name&, BaseField::Factory);
  void unregisterField(const BaseField::Name&);

  Map mMap;
  ReverseMap mReverseMap;
};

} // namespace fields
} // namespace openfield
