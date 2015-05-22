#ifndef __244_erishable_H__
#define __244_Perishable_H__
// includes go here
#include "Date.h"
#include "ErrorMessage.h"
#include "Item.h"


namespace oop244{
  class Perishable:public Item{
  private:
    ErrorMessage _err;
    // expiry and unit go here
	char _unit[11];
	Date _expiry;

  public:
    // default constructor
	  Perishable();

    // pure virutal method implementation prototypes
	  std::fstream& store(std::fstream& file)const;
	  std::fstream& load(std::fstream& file);
	  std::ostream& display(std::ostream& ostr, bool linear = true)const;
	  std::istream& conInput(std::istream& istr);

    // Setters 
	  void expiry(const Date& value);
	  void unit(const char* value);

	// Getters
	  const Date& expiry()const;
	  const char* unit()const;

  };
}


#endif
