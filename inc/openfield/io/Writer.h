#pragma once
#include <ostream>

namespace openfield {
namespace io {

class Node;
class Writer {
public:
  virtual ~Writer() {}
  virtual void write(std::ostream&, const Node&) const = 0;  
};

} // namespace io
} // namespace openfield
