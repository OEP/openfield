#include "openfield/openfield.h"
#include "openfield/fields/fields.h"

void openfield::initialize() {
  using namespace openfield::fields;
  Registry &reg = Registry::getInstance();

  reg.registerField<Sphere>();
}

void openfield::uninitialize() {
  using namespace openfield::fields;
  Registry &reg = Registry::getInstance();
  
  reg.unregisterField<Sphere>();
}
