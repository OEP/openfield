#pragma once
#include <openfield/Types.h>
#include <memory>
#include <map>

namespace openfield {
namespace io { class Node; }
namespace fields {

class Visitor;

class BaseField {
public:
  //! Type used for field names in registry.
  typedef std::string Name;

  //! Dynamic pointer type for BaseField
  typedef std::shared_ptr<BaseField> Ptr;

  //! Function pointer which generates a field from a io::Node
  typedef BaseField::Ptr(*Factory)(const io::Node&);

  virtual ~BaseField() {}

  //! Dispatch a visitor on this field
  void dispatch(Visitor&);

private:
  //! Accept a visitor.
  virtual void accept(Visitor&) = 0;

};

template <typename EvalT, typename GradT>
class Field : public BaseField {
public:
  //! Dynamic field type for template instantiated type.
  typedef std::shared_ptr<Field<EvalT, GradT> > Ptr;

  //! Evaluate the field at the given point.
  virtual EvalT eval(const Vec3f&) const = 0;

  //! Evaluate the gradient of the field at the given point.
  virtual GradT grad(const Vec3f&) const = 0;
private:
};

typedef Field<float, Vec3f> ScalarField;
} // namespace fields
} // namespace openfield
