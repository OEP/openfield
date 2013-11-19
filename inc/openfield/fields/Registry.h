#pragma once
#include <openfield/fields/Field.h>
#include <openfield/io/Node.h>
#include <memory>

namespace openfield {
namespace fields {

class Registry {
private:
  typedef std::map<BaseField::Name, BaseField::Factory> Map;
  typedef std::map<std::string, BaseField::Name> ReverseMap;

public:
  //! Get an instance of the Registry singleton
  static Registry& getInstance();

  //! Register a new field type.
  template <typename FieldT>
  void registerField() {
    Registry::getInstance().registerField(FieldT::getTag(), typeid(FieldT).name(), FieldT::factory);
  }
  
  //! Unregister a previously registered field type.
  template <typename FieldT>
  void unregisterField() {
    Registry::getInstance().unregisterField(FieldT::getTag());
  }

  /*! Construct the field described by given node and cast.
   *
   * \throws KeyError if a field could not be looked up in the registry.
   * \throws TypeError if the result is not of the requested type.
   */
  template <typename FieldT>
  typename FieldT::Ptr get(const io::Node& n) const {
    typename FieldT::Ptr p = std::dynamic_pointer_cast<FieldT>(Registry::getInstance().create(n));
    if(!p.get()) {
      throw TypeError("node " + n.getName() + " is not of type " + typeid(FieldT).name());
    }
    return p;
  }

  /*! Get the name corresponding to the given type.
   *
   * \throws KeyError if the field type is not registered.
   */
  template <typename FieldT>
  std::string getName() const {
    ReverseMap::const_iterator it = mReverseMap.find(typeid(FieldT).name());
    if(it == mReverseMap.end()) {
      throw KeyError(std::string("Type ") + typeid(FieldT).name() + " not registered.");
    }
    return it->second;
  }

  /*! Create a field based on an io::Node.
   *
   * \throws KeyError if a field could not be looked up
   */
  BaseField::Ptr create(const io::Node&) const;

private:
  Registry();
  Registry(const Registry&);
  Registry& operator=(const Registry&);
  
  void registerField(const BaseField::Name&, const std::string&, BaseField::Factory);
  void unregisterField(const BaseField::Name&);

  Map mMap;
  ReverseMap mReverseMap;
};

} // namespace fields
} // namespace openfield
