#pragma once
#include <openfield/Types.h>
#include <memory>
#include <map>

namespace openfield {
namespace io { class Node; }
namespace fields {

class BaseField {
public:
  typedef std::string Name;
  typedef std::shared_ptr<BaseField> Ptr;
  typedef BaseField::Ptr(*Factory)(const io::Node&);

  virtual ~BaseField() {}
private:
};

template <typename EvalT, typename GradT>
class Field : public BaseField {
public:
  typedef std::shared_ptr<Field<EvalT, GradT> > Ptr;
  virtual EvalT eval(const Vec3f&) const = 0;
  virtual GradT grad(const Vec3f&) const = 0;
private:
};

typedef Field<float, Vec3f> ScalarField;
} // namespace fields
} // namespace openfield
