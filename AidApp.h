#ifndef __244_AIDAPP_H__
#define __244_AIDAPP_H__
#include "Perishable.h"
#include "NFI.h"

namespace oop244{
  class AidApp{
    // private member arguments
	  char _filename[256];
	  Item* _items[MAX_NO_RECS]; 
	  std::fstream datafile;
	  int _noOfItems;

    // copy constructor and assignment operator
    // to prevent copying and assignment
	  AidApp(const AidApp&);
	  void operator=(const AidApp&);

    // private member functions
	  int menu();
	  void loadRecs();
	  void saveRecs();
	  void listItems()const;
	  int SearchItems(const char* upc)const;
	  void updateQty(const char* upc);
	  void addItem(bool isPerishable);

  public:
    // constructor and run member function
	  AidApp(const char* filename);
	  int run();

  };
}
#endif
