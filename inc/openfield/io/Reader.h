#pragma once
#include <istream>

namespace openfield {
namespace io {

class Node;
class Reader {
public:
  virtual ~Reader() {}

  //! Read the stream into the given io::Node
  virtual void read(std::istream&, Node&) const = 0;  
};

} // namespace io
} // namespace openfield
