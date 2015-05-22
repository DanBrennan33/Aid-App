#include "Streamable.h"
namespace oop244{
	// destructor:
	Streamable::~Streamable() {
		//Empty Destructor
	}


	// Non-memenber operator overoad implementation for cin and cout:
	std::istream& operator>>(std::istream& istr, Streamable& s) {
		s.conInput(istr);
		return istr;
	}
	std::ostream& operator<<(std::ostream& ostr, const Streamable& s) {
		s.display(ostr);
		return ostr;
	}
}
