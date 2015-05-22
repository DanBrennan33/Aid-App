// includes go here
#include "Perishable.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <iomanip>
#include <cstring>

namespace oop244{
  // constructor
	Perishable::Perishable() : Item ("", "", 0.0, 1, false) {
		_unit[0] = '\0';

	}

  // Setters 
	void Perishable::expiry(const Date& value) {
		_expiry = value;
	}
	void Perishable::unit(const char* value) {
		if (value) {
			strcpy(_unit, value);
		}
		else {
			_unit[0] = '\0';
		}
	}

  // getters 
	const Date& Perishable::expiry()const {
		return _expiry;
	}
	const char* Perishable::unit()const {
		return _unit;
	}

  // fstream& Perishable::store(fstream& file)const
	std::fstream& Perishable::store(std::fstream& file)const {
		if (file.is_open()) {
			file << "P,";
			file << upc() << ",";
			file << name() << ",";
			file << price() << ",";
			file << unit() << ",";
			file << quantity() << ",";
			file << qtyNeeded() << ",";
			file << expiry() << std::endl;
		}
		return file;
	}

  //fstream& Perishable::load(fstream& file)
	std::fstream& Perishable::load(std::fstream& file) {
		char u[MAX_UPC_LEN + 1];
		char buffer[256];
		char pS[256];
		char qS[256];
		char qNS[256];
		char unt[11];

		int i = MAX_UPC_LEN + 1;

		char* n;
		double pR;
		int qR;
		int qNR;
		Date expire;

		if (file.is_open()){
			if (file.good()) {
				file.getline(u, i, ',');
				upc(u);

				file.getline(buffer, 20, ',');
				n = new (std::nothrow) char[strlen(buffer) + 1];
				strcpy(n, buffer);
				name(n);

				file.getline(pS, 7, ',');
				pR = atof(pS);
				price(pR);

				file.getline(unt, 11, ',');
				unit(unt);

				file.getline(qS, 4, ',');
				qR = atof(qS);
				quantity(qR);

				file.getline(qNS, 4, ',');
				qNR = atof(qNS);
				qtyNeeded(qNR);

				expire.read(file);	
				expiry(expire);
			}
		}
		return file;
	}

  //ostream& Perishable::display(ostream& os, bool linear)const  
	std::ostream& Perishable::display(std::ostream& ostr, bool linear)const {
		if (!_err.isClear()) {
			ostr << _err;
		}
		else {
			if (linear == true) {
				ostr.setf(std::ios::left);
				ostr << std::setw(MAX_UPC_LEN) << std::setfill(' ') << upc() << "|";
				ostr << std::setw(20) << std::setfill(' ') << name() << "|";
				ostr.unsetf(std::ios::left);
				ostr.setf(std::ios::right);
				ostr.setf(std::ios::fixed);
				ostr << std::setw(7) << std::setprecision(2) << std::setfill(' ') << cost() << "|";
				ostr.unsetf(std::ios::fixed);
				ostr << std::setw(4) << std::setfill(' ') << quantity() << "|";
				ostr << std::setw(4) << std::setfill(' ') << qtyNeeded() << "|";
				ostr.unsetf(std::ios::right);
				ostr.setf(std::ios::left);
				ostr << std::setw(10) << std::setfill(' ') << unit() << "|";
				ostr.unsetf(std::ios::left);
				ostr << expiry();
			}
			else {
				ostr << "upc: " << upc() << std::endl;
				ostr << "name: " << name() << std::endl;
				ostr.setf(std::ios::fixed);
				ostr << "price: " << std::setprecision(2) << price() << std::endl;
				ostr << "Price after tax: " << std::setprecision(2) << cost() << std::endl;
				ostr.unsetf(std::ios::fixed);
				ostr << "Quantity On hand: " << quantity() << std::endl;
				ostr << "Quantity Needed: " << qtyNeeded() << std::endl;
				ostr << "Unit: " << unit() << std::endl;
				ostr << "Expiry date: " << expiry() << std::endl;
			}
		}
		return ostr;
	}

  // istream& Perishable::conInput(istream& is)
	std::istream& Perishable::conInput(std::istream& istr) {
		char u[MAX_UPC_LEN + 1];
		char buffer[256];
		char* n;
		double p = 0;
		int q = 0;
		int qN = 0;
		char unt[11];
		Date expire;

		_err.message("");

		if (istr.fail()) {
			//exit function if istr fail.
		}
		else {
			std::cout << "Perishable Item Entry: " << std::endl;
			std::cout << "upc: ";
			istr >> u;
			upc(u);
			std::cout << "name: ";
			istr >> buffer;
			n = new (std::nothrow) char[strlen(buffer) + 1];
			strcpy(n, buffer);
			name(n);
			std::cout << "price: ";
			istr >> p;
			if (istr.fail()) {
				_err.message("Invalid Price Entry");
			}
			else {
				price(p);
				std::cout << "Quantity On hand: ";
				istr >> q;
				if (istr.fail()) {
					_err.message("Invalid Quantity Entry");
				}
				else {
					quantity(q);
					std::cout << "Quantity Needed: ";
					istr >> qN;
					if (istr.fail()) {
						_err.message("Invalid Quantity Needed Entry");
					}
					else {
						qtyNeeded(qN);
						std::cout << "Unit: ";
						istr >> unt;
						unit(unt);
						std::cout << "Expiry date (YYYY/MM/DD) : ";
						expire.read(istr);
						if (istr.fail()) {
							_err.message("Invalid Date Entry");
							istr.setstate(std::ios::failbit);
						}
						else if (expire.errCode() == 2) {
							_err.message("Invalid Year in Date Entry");
							istr.setstate(std::ios::failbit);
						}
						else if (expire.errCode() == 3) {
							_err.message("Invalid Month in Date Entry");
							istr.setstate(std::ios::failbit);
						}
						else if (expire.errCode() == 4) {
							_err.message("Invalid Day in Date Entry");
							istr.setstate(std::ios::failbit);
						}
						else {
							expiry(expire);
						}
					}
				}
			}
		}
		return istr;
	}

}
