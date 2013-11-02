#include <openfield/fields/Field.h>

namespace openfield {
namespace fields {

class Sphere : public ScalarField {
public:
  static ScalarField::Ptr create(const Vec3f& center, float radius) {
    return ScalarField::Ptr(new Sphere(center, radius));
  }

  float eval(const Vec3f& p) const { return mRadius - norm2(p - mCenter); }
  Vec3f grad(const Vec3f& p) const { return unit(mCenter - p); }
private:
  Sphere();
  Sphere(const Vec3f& center, float radius):
    mCenter(center), mRadius(radius)
    {}

  Vec3f mCenter;
  float mRadius;
};

} // namespace fields
} // namespace openfield
