#include <cstring>
#include <new>
#include <iomanip>
#include "AidApp.h"

using namespace std;
namespace oop244{

  // copy constructor and assignment operator
	AidApp::AidApp(const AidApp&) {
		// empty copy constructor
	}
	void AidApp::operator=(const AidApp&) {
		// empty assignment operator
	}

  // constructor 
  // copies filename to _filename
  // sets all the _items to null
  // sets _noOfItems to null
  // loads the Records
  AidApp::AidApp(const char* filename) {
	strcpy(_filename, filename);
	for (int i = 0; i < MAX_NO_RECS; i++) {
		_items[i] = nullptr;
	}
	_noOfItems = 0;
	loadRecs();

  }

  // Menu() displays the menu as follows and waits for the user to 
  // select an option. 
  // if the selection is valid, it will return the selection
  // if not it will return -1
  // this funtion makes sure there is no characters left in keyboard
  // and wipes it before exit.
	int AidApp::menu() {
		int selection = 0;
		int select = 0;

		if (!cin.fail()) {
			cout << "Disaster Aid Supply Management Program" << endl;
			cout << "1 - List Items" << endl;
			cout << "2 - Add Non-food item Item" << endl;
			cout << "3 - Add Perishable item" << endl;
			cout << "4 - Update item quantity" << endl;
			cout << "0 - exit program" << endl;
			cout << "> ";
			cin >> select;
		}

		if (select >= 0 && select <= 4) {
			selection = select;
		}
		else {
			selection = -1;
		}
		cin.clear();
		cin.ignore(MAX_NO_RECS, '\n');
		return selection;
    }

  // lists all the items in linear format on the screen 

  void AidApp::listItems()const{
	  double value = 0;
	  cout << " Row " << "|";
	  cout << " UPC    " << "|";
	  cout << " Item Name          " << "|";
	  cout << " Cost  " << "|";
	  cout << " QTY" << "|";
	  cout << "Need" << "|";
	  cout << " Unit     " << "|";
	  cout << " Expiry   " << endl;
	  cout << "-----|--------|--------------------|-------|----|----|----------|----------" << endl;

	  for (int i = 0; i < _noOfItems; i++) {
			  cout.setf(ios::right);
			  cout << setw(4) << setfill(' ') << i + 1;
			  cout.unsetf(ios::right);
			  cout << " | ";
			  _items[i]->display(cout, true);
			  cout << endl;
			  value += *_items[i];
	  }

	  cout << "---------------------------------------------------------------------------" << endl;
	  cout.setf(std::ios::fixed);
	  cout << "Total cost of support: $" << setprecision(2) << value << endl;
	  cout.unsetf(ios::fixed);
  }


  // opens the file for writing
  // stores the items in the file
  // closes the file
  void AidApp::saveRecs(){
	  datafile.open(_filename, ios::out);
				for (int i = 0; i < _noOfItems; i++) {
					_items[i]->store(datafile);
				}
	  datafile.close();
  }

 // Opens the file for reading, if it does not exist, it will create an
 // empty file and exits otherwise :
 // Loads Records from the file overwriting the old ones pointed by item.
 // This function makes sure when loading records into _item pointers, they 
 // are deallocated before if they are already pointing to an item
 // closes the file

  void AidApp::loadRecs(){
	  int readIndex = 0;
	  char Id;

	  datafile.open(_filename, ios::in);
	  if (datafile.fail()) {
		  datafile.clear();
		  datafile.close();
		  datafile.open(_filename, ios::in);
		  datafile.close();
	  }
	  else {
		  while (readIndex < MAX_NO_RECS && !datafile.eof()) {
			  if (_items[readIndex] != nullptr) {
				  delete[] _items[readIndex];
				  _items[readIndex] = nullptr;
			  }

			  Id = datafile.get();

			  if (Id == 'P') {
				  _items[readIndex] = new Perishable();
				  datafile.ignore(1);
				  _items[readIndex]->load(datafile);
				  readIndex += 1;
			  }
			  else if (Id == 'N') {
				  _items[readIndex] = new NFI();
				  datafile.ignore(1);
				  _items[readIndex]->load(datafile);
				  readIndex += 1;
			  }
		  }
		  _noOfItems = readIndex;
	  }
	  datafile.close();
  }
  // Searchers for the item in the _items array with the same UPC.
  // if found, it will display the item in non-linear format and then 
  // asks for the value of the items purchased, and if the value does not exceed
  // the number needed to fulfill the requirement, it will update the quantity onhand
  // value of the found record and then saves all the records to the file, overwriting 
  // the old values
  void AidApp::updateQty(const char* UPC){
	  int index;
	  int qTemp = 0;
	  int req = 0;
	  int qtyN = 0;
	  int qtyT = 0;
	  int cReq = 0;

	  index = SearchItems(UPC);
	  if (index == -1) {
		  cout << "Not found!" << endl;
	  }
	  else {
		  _items[index]->display(cout, false);
		  cout << "Please enter the number of purchased items: ";
		  cin >> qTemp;
		  if (cin.fail()) {
			  cout << "Invalid Quantity value!" << endl;
		  }
		  else {
			  qtyN = _items[index]->qtyNeeded();
			  qtyT = _items[index]->quantity();
			  req = qtyN - qtyT;
			  cReq = qTemp - req;
			  if (qTemp <= req) {
				  *_items[index] += qTemp;
			  }
			  else {
				  *_items[index] += req;
				  //req then cReq
				  cout << "Too much items, only " << req;
				  cout << " is needed, please return the extra " << cReq << " items." << endl;
			  }
			  saveRecs();
			  cout << "Updated!" << endl;
			  cin.clear();
		  }
	  }
  }

  // searches for an item in the _items array for the same upc
  // if found it will return the index of the found item in _items
  // otherwise returns -1
  int AidApp::SearchItems(const char* upc)const{
	  int index = 0;
	  for (int j = 0; j < _noOfItems; j++) {
		  if (*_items[j] == upc) {
			  index = j;
			  j = _noOfItems;
		  }
	  }
	  if (index == 0) {
			  index = -1;
	  }
	  
	  return index;
  }

  // creates a new item (NFI or Perishable) based on the argument
  // recieved dynamically, asks the user to fill in the values
  // if the user fills the values with no mistake, it will open the file 
  // for writing, and then stores the item in the file.
  // and print a proper message. 
  // if the user makes a mistake (cin fails) it will only display the item
  // to show the error.
  // in any way it will delete the item before exiting the function
  void AidApp::addItem(bool isPerishable){
	  if (isPerishable) {
		  Perishable p;
		  p.conInput(cin);
		  if (cin.fail()) {
			  p.display(cout, true);
			  cout << endl;
			  run();
		  }
		  else {
			  datafile.open(_filename, ios::out);
			  for (int i = 0; i < _noOfItems; i++) {
					  _items[i]->store(datafile);
			  }
			  p.store(datafile);
			  datafile.close();
			  cout << "Item Added!" << endl;
		  }
	  }
	  else {
		  NFI n;
		  n.conInput(cin);
		  if (cin.fail()) {
			  n.display(cout, true);
			  cout << endl;
			  run();
		  }
		  else {
			  datafile.open(_filename, ios::out);
			  for (int i = 0; i < _noOfItems; i++) {
					  _items[i]->store(datafile);
			  }
			  n.store(datafile);
			  datafile.close();
			  cout << "Item Added!" << endl;
		  }
	  }
  }

  // diplays the menu and receives the user selection
  // if valid, it will preform the action requsted:
  // 1, lists the items in the file on the screen
  // 2 and 3, adds the item and then re-loads the records
  //     from the file into the AidApp
  // 4, gets a UPC and then updates the quantity of it
  // 0, exits the program.
  int AidApp::run(){
	  char buffer[MAX_UPC_LEN + 1];
	  int i = 0;

	  for (i = menu(); i != 0; i = menu()) {
		  switch (i) {
		  
		  case 0:
			  cout << "Goodbye!!" << endl;
			  exit(1);
			  break;
		  case 1:
			  for (int j = 0; j < MAX_NO_RECS; j++) {
				  _items[j] = nullptr;
			  }
			  loadRecs();
			  listItems();
			  break;
		  case 2:
			  addItem(false);
			  for (int j = 0; j < MAX_NO_RECS; j++) {
				  _items[j] = nullptr;
			  }
			  loadRecs();
			  break;
		  case 3:
			  addItem(true);
			  for (int j = 0; j < MAX_NO_RECS; j++) {
					_items[j] = nullptr;
			  }
			  loadRecs();
			  break;
		  case 4:
			  cout << "Please enter the UPC: ";
			  cin >> buffer;
			  updateQty(buffer);
			  break;
		  default:
			  cout << "===Invalid Selection, try again.===";
			  break;
		  }
	  }
	  return 0;
  }

}
