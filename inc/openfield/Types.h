#pragma once
#include <openfield/math/Vec.h>

#define OPENFIELD_PTR(E,G) ::std::shared_ptr<::openfield::fields::Field<E, G> >

namespace openfield {
  // Vec3 types
  typedef math::Vec3f Vec3f;
} // namespace openfield
