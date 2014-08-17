#include <openfield/fields/Field.h>

namespace openfield {
namespace fields {

template <typename EvalT, typename GradT>
class Plus : public Field<EvalT, GradT> {
private:
  typedef OPENFIELD_PTR(EvalT, GradT) FieldPtrT;

public:
  static FieldPtrT create(FieldPtrT lhs, FieldPtrT rhs);

  EvalT eval(const Vec3f&) const;
  GradT grad(const Vec3f&) const;
  void accept(Visitor&);

  const FieldPtrT& getLhs() const { return mLhs; }
        FieldPtrT& getLhs()       { return mLhs; }

  const FieldPtrT& getRhs() const { return mRhs; }
        FieldPtrT& getRhs()       { return mRhs; }
private:
  FieldPtrT mLhs, mRhs;
  Plus(FieldPtrT, FieldPtrT);
};

template <typename EvalT, typename GradT>
OPENFIELD_PTR(EvalT, GradT)
operator+(
  OPENFIELD_PTR(EvalT, GradT) lhs,
  OPENFIELD_PTR(EvalT, GradT) rhs
) {
  return Plus<EvalT, GradT>::create(lhs, rhs);
}

template class Plus<float, Vec3f>;

} // namespace fields
} // namespace openfield
