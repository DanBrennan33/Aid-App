#ifndef __244_NFI_H__
#define __244_NFI_H__

// includes go here
#include "Item.h"
#include "ErrorMessage.h"

namespace oop244{
  class NFI : public Item {
  private:
    ErrorMessage _err;
  public:
    // default constructor
	  NFI();

    // pure virutal method implementation prototypes
	  std::fstream& store(std::fstream& file)const;
	  std::fstream& load(std::fstream& file);
	  std::ostream& display(std::ostream& ostr, bool linear = true)const;
	  std::istream& conInput(std::istream& istr);

  };
}
#endif
