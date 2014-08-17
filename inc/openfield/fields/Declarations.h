#pragma once

#include <openfield/Types.h>

/*
 * Forward declarations for field types.
 */

namespace openfield {
namespace fields {

class BaseField;
class Sphere;

template <typename EvalT, typename GradT> class Plus;

typedef Plus<float, openfield::Vec3f> ScalarPlus;

} // namespace fields
} // namespace openfield
