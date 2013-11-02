#pragma once
#include <openfield/math/Vec.h>

namespace openfield {
  // Vec3 types
  typedef math::Vec3f Vec3f;
} // namespace openfield

#include <openfield/fields/fields.h>
namespace openfield {
  // Basic field types
  typedef fields::BaseField BaseField;
  template <typename EvalT, typename GradT>
  using Field = fields::Field<EvalT, GradT>;
  typedef fields::ScalarField ScalarField;

  // ScalarField types
  typedef fields::Sphere Sphere;
}
