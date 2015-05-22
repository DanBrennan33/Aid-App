//includes go here
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <iomanip>
#include <cstring>
#include "NFI.h"

namespace oop244{
  // constructor
	NFI::NFI() : Item("", "", 0.0, 1)  {
		
	}

    
  // fstream& NFI::store(fstream& file)const
	std::fstream& NFI::store(std::fstream& file)const {
		if(file.is_open()) {
			file << "N,";
			file << upc() << ",";
			file << name() << ",";
			file << price() << ",";
			file << quantity() << ",";
			file << qtyNeeded() << std::endl;
		}
		return file;
	}


  // fstream& NFI::load(fstream& file)
	std::fstream& NFI::load(std::fstream& file) {
		char u[MAX_UPC_LEN + 1];
		char buffer[256];
		char pS[256];
		char qS[256];
		char qNS[256];
		
		int i = MAX_UPC_LEN + 1;
		
		char* n;
		double pR;
		int qR;
		int qNR;
	
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
				
				file.getline(qS, 4, ',');
				qR = atof(qS);
				quantity(qR);
			
				file.getline(qNS, 4);
				qNR = atof(qNS);
				qtyNeeded(qNR);
			}
		}
		return file;
	}
    
  // ostream& NFI::display(ostream& ostr, bool linear)const
	std::ostream& NFI::display(std::ostream& ostr, bool linear)const {
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
				ostr << std::setw(4) << std::setfill(' ') << qtyNeeded();
				ostr.unsetf(std::ios::right);
			}
			else {
				ostr << "upc: " << upc() << std::endl;
				ostr << "name: " << name() << std::endl;
				ostr.setf(std::ios::fixed);
				ostr << "price: " << std::setprecision(2) << price() << std::endl;
				ostr << "Price after tax: " << std::setprecision(2) << cost() << std::endl;
				ostr.unsetf(std::ios::fixed);
				ostr << "Quantity On Hand: " << quantity() << std::endl;
				ostr << "Quantity Needed: " << qtyNeeded() << std::endl;
			}
		}
		return ostr;
	}
  // istream& NFI::conInput(istream& istr)
	std::istream& NFI::conInput(std::istream& istr) {
		char u[MAX_UPC_LEN + 1];
		char buffer[256];
		char* n;
		double p = 0;
		int q = 0;
		int qN = 0;
		
		_err.message("");

		if (istr.fail()) {
			//exit function if istr fail.
		}
		else {
			std::cout << "Non-Food Item Entry:" << std::endl;
			std::cout << "Upc: ";
			istr >> u;
			upc(u);
			std::cout << "Name: ";
			istr >> buffer;
			n = new (std::nothrow) char[strlen(buffer) + 1];
			strcpy(n, buffer);
			name(n);
			std::cout << "Price: ";
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
					}
				}
			}
		}
		return istr;
	}
}
