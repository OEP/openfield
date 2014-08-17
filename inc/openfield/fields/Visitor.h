#pragma once
#include <openfield/fields/Declarations.h>

namespace openfield {
namespace fields {

//! A field hierarchy visitor.
class Visitor {
public:
  /** \brief Signal to visitor we are about to enter a node.
   *
   * This method is called just before BaseField::accept() is called. If this
   * method returns false, BaseField::accept() will not be called,
   * Visitor::exit() will be called (with the same argument), and the next item
   * for visitation is considered. If it returns true, then BaseField::accept()
   * will be called.
   */
  virtual bool enter(BaseField&) { return true; }

  /** \brief Signal to visitor we are exiting a node.
   *
   * This method is called each time a node is removed from consideration if
   * and only if Visitor::enter() has been called on it.
   */
  virtual void exit(BaseField&) {}

  virtual void visitSphere(Sphere&) = 0;

  virtual void visitScalarPlus(ScalarPlus&) = 0;
};

} // namespace fields
} // namespace openfield
