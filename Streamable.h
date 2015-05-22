#ifndef __244__Streamable__
#define __244__Streamable__
// hearfile includes:
#include <iostream>
#include <fstream>

namespace oop244{
  class Streamable{
  public:
    // pure virutal methods:
	  virtual std::fstream& store(std::fstream& file)const = 0;
	  virtual std::fstream& load(std::fstream& file) = 0;
	  virtual std::ostream& display(std::ostream& ostr, bool linear = true)const = 0;
	  virtual std::istream& conInput(std::istream& istr) = 0;

	// virutal destructor:
	  virtual ~Streamable();
  };
  // Non-memenber operator overoad prototypes for cin and cout:
	  std::istream& operator>>(std::istream& istr, Streamable& s);
	  std::ostream& operator<<(std::ostream& ostr, const Streamable& s);
}
#endif
