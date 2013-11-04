#include "openfield/openfield.h"
#include "openfield/fields/fields.h"

void openfield::initialize() {
  using namespace openfield::fields;

  Registry::registerField<Sphere>();
}
