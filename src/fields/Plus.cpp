#include "openfield/fields/Plus.h"
#include "openfield/fields/Visitor.h"

namespace openfield {
namespace fields {

template <typename EvalT, typename GradT>
Plus(
  OPENFIELD_PTR(EvalT, GradT) lhs,
  OPENFIELD_PTR(EvalT, GradT) rhs
):
  mLhs(lhs), mRhs(rhs)
{ }

template <typename EvalT, typename GradT>
OPENFIELD_PTR(EvalT, GradT)
Plus<EvalT, GradT>::create(
  OPENFIELD_PTR(EvalT, GradT) lhs,
  OPENFIELD_PTR(EvalT, GradT) rhs
) {
  return typename Field<EvalT, GradT>::Ptr(new Plus<EvalT, GradT>(lhs, rhs));
}

template <typename EvalT, typename GradT>
EvalT
Plus<EvalT, GradT>::eval(
  const Vec3f& pos
) const {
  return mLhs->eval(pos) + mRhs->eval(pos);
}

template <typename EvalT, typename GradT>
GradT
Plus<EvalT, GradT>::grad(
  const Vec3f& pos
) const {
  return mLhs->grad(pos) + mRhs->grad(pos);
}

template <>
void
Plus<float, Vec3f>::accept(
  Visitor& visitor
) {
  visitor.visitScalarPlus(*this);
}

template class Plus<float, Vec3f>;

} // namespace fields
} // namespace openfield
