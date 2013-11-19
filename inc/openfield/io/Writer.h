#pragma once
#include <ostream>

namespace openfield {
namespace io {

class Node;
class Writer {
public:
  virtual ~Writer() {}

  //! Write the given io::Node to the stream.
  virtual void write(std::ostream&, const Node&) const = 0;  
};

} // namespace io
} // namespace openfield
