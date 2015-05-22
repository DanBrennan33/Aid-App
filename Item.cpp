// header file includes
#include "Item.h"
#include "general.h"

#include <iostream>
#include <cstring>

using namespace std;

namespace oop244{

  // constructors 
	//Constructor
	Item::Item() {
		_upc[0] = '\0';
		_name = nullptr;
		_price = 0;
		_quantity = 0;
		_qtyNeeded = 0;

	}
	//Overload Constructor
	Item::Item(const char* upc, const char* name, double price, int qtyN, bool taxed) {
		strcpy(_upc, upc);
		_name = new (std::nothrow) char[strlen(name) + 1];
		strcpy(_name, name);
		_price = price;
		_taxed = taxed;
		_quantity = 0;
		_qtyNeeded = qtyN;
		
	}
	//Copy Constructor
	Item::Item(const Item& src) {
		strcpy(_upc, src._upc);
		_name = new (std::nothrow) char[strlen(src._name) + 1];
		strcpy(_name, src._name);
		_quantity = src._quantity;
		_qtyNeeded = src._qtyNeeded;
		_taxed = src._taxed;
		_price = src._price;
	}

  // operator=
	Item& Item::operator=(const Item& src) {
		if (this != &src) {
			strcpy(_upc, src._upc);
			_name = new (std::nothrow) char[strlen(src._name) + 1];
			strcpy(_name, src._name);
			_quantity = src._quantity;
			_qtyNeeded = src._qtyNeeded;
			_taxed = src._taxed;
			_price = src._price;
		}
		return *this;
	}

  // setters 
	void Item::upc(char* upc) {
		if(upc) {
			strcpy(_upc, upc);
		}
		else {
			_upc[0] = '\0';
		}
	}
	void Item::price(double& price) {
		_price = price;
	}
	void Item::name(char* name) {
		if (!name) {
			_name = nullptr;
		}
		else {
			if (_name) {
				delete[] _name;
				_name = nullptr;
			}
			_name = new (std::nothrow) char[strlen(name) + 1];
			strcpy(_name, name);
		}
	}
	void Item::taxed(bool taxed) {
		_taxed = taxed;
	}
	void Item::quantity(int qty) {
		_quantity = qty;
	}
	void Item::qtyNeeded(int qtyN) {
		_qtyNeeded = qtyN;
	}

  // getters
	const char* Item::upc()const {
		return _upc;
	}
	double Item::price()const {
		return _price;
	}
	const char* Item::name()const {
		return _name;
	}
	bool Item::taxed()const {
		return _taxed;
	}
	int Item::quantity()const {
		return _quantity;
	}
	int Item::qtyNeeded()const {
		return _qtyNeeded;
	}
	double Item::cost()const {
		double i = 0.0;
		if (_taxed) {
			i = _price + _price * TAX;
		}
		else {
			i = _price;
		}
		return i;
	}

  // member operator overloads 
	bool Item::operator==(const char* upc) {
		bool i;
		if (strcmp(_upc, upc) == 0) {
			i = true;
		}
		else {
			i = false;
		}
		return i;
	}
	int Item::operator+=(int qty) {
		_quantity += qty;
		return _quantity;
	}

  // non-member operator overload
	double operator+=(double& d, const Item& I) {
		d += I.quantity() * I.cost();
		return d;
	}

  // destructor
	Item::~Item() {
		if (_name) {
			delete [] _name;
			_name = nullptr;
		}
	}
}
