#include <openfield/fields/Field.h>
#include <openfield/fields/Visitor.h>

using namespace openfield::fields;

void BaseField::dispatch(Visitor& v) {
  if(v.enter(*this)) {
    accept(v);
  }
  v.exit(*this); 
}
