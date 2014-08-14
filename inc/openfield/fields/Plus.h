#include <openfield/fields/Field.h>

namespace openfield {
namespace fields {

template <typename EvalT, typename GradT>
typename Field<EvalT, GradT>::Ptr
operator+(
  const std::shared_ptr<Field<EvalT, GradT> >,
  const std::shared_ptr<Field<EvalT, GradT> >
) {
  return std::shared_ptr<Field<EvalT, GradT> >();
}

} // namespace fields
} // namespace openfield
