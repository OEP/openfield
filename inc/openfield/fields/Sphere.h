#include <openfield/fields/Field.h>
#include <openfield/io/Node.h>

namespace openfield {
namespace fields {

class Sphere : public ScalarField {
public:
  //! Return the tag for a Sphere.
  static std::string getTag() { return "Sphere"; }

  //! Factory function to create a sphere from io::Node
  static BaseField::Ptr factory(const io::Node& n) {
    return Sphere::create(n.get<Vec3f>("center"), n.get<float>("radius"));
  }

  //! Create new instance of a sphere.
  static ScalarField::Ptr create(const Vec3f& center, float radius) {
    return ScalarField::Ptr(new Sphere(center, radius));
  }

  //! Evaluate the sphere at the given point.
  float eval(const Vec3f& p) const { return mRadius - norm2(p - mCenter); }

  //! Evaluate the gradient of the sphere at the given point.
  Vec3f grad(const Vec3f& p) const { return unit(mCenter - p); }

  //! Store a Sphere into a node.
  void store(io::Node& n) const { n.add("center", mCenter); n.add("radius", mRadius); }
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
