// Date Implementation file - Milestone 1
/////////////////////////////////////////

#include "Date.h"
#include "general.h"
#include <iomanip>
#include <iostream>

using namespace std;

 namespace oop244 {
	
	// constructor 
Date::Date() {
	_year = 0;
	_mon = 0;
	_day = 0;
	_readErrorCode = NO_ERROR;
}
Date::Date(int y, int m, int d) {
	if (y >= MIN_YEAR && y <= MAX_YEAR) {
		_year = y;
		if (m >= 1 && m <= 12) {
			_mon = m;
			if (d >= 1 && d <= mdays()) {
				_day = d;
				errCode(NO_ERROR);
			}
			else {
				_day = 0;
				errCode(DAY_ERROR);
			}
		}
		else {
			_mon = 0;
			errCode(MON_ERROR);
		}
	}
	else {
		_year = 0;
	errCode(YEAR_ERROR);
	}
	
}
		
  // validate function 
void Date::errCode(int errorCode) {
	_readErrorCode = errorCode;
}
	// member functions 

	// returns a unique value for a date
	// this value is used to compare two dates
int Date::value()const {
	return _year * 372 + _mon * 31 + _day;
}

	// returns the day of the month. 
	// _mon value must be set for this to work
	// if _mon is invalid, this function returns -1
	// leap years are considered in this logic
int Date::mdays()const {
    int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
    int mon = _mon >= 1 && _mon <= 12 ? _mon : 13;
    mon--;
    return days[mon] + int((mon == 1)*((_year % 4 == 0) && (_year % 100 != 0)) || (_year % 400 == 0));
}

int Date::errCode()const {
	return _readErrorCode;
}

bool Date::bad()const {
	if (_readErrorCode != 0)
		return true;
	else
		return false;
}

	// operators
bool Date::operator==(const Date& D)const {
	bool i;
	if (this->value() == D.value()) {
		i = true;
	}
	else {
		i = false;
	}
	return i;
}

bool Date::operator!=(const Date& D)const {
	bool i;
	if (this->value() != D.value()) {
		i = true;
	}
	else {
		i = false;
	}
	return i;
}

bool Date::operator<(const Date& D)const {
	bool i;	
	if (this->value() < D.value()) {
		i = true;
	}
	else {
		i = false;
	}
	return i;
}

bool Date::operator>(const Date& D)const {
	bool i;
	if (this->value() > D.value()) {
		i = true;
	}
	else {
		i = false;
	}
	return i;
}

bool Date::operator<=(const Date& D)const {
	bool i;
	if (this->value() <= D.value()) {
		i = true;
	}
	else {
		i = false;
	}
	return i;
}

bool Date::operator>=(const Date& D)const {
	bool i;
	if (this->value() >= D.value()) {
		i = true;
	}
	else {
		i = false;
	}
	return i;
}

	// IO funtions
std::istream& Date::read(std::istream& istr) {
	istr >> _year;
	if (istr.fail()) {
		errCode(CIN_FAILED);
		return istr;
	}
	istr.ignore(1);
	istr >> _mon;
	if (istr.fail()) {
		errCode(CIN_FAILED);
		return istr;
	}
	istr.ignore(1);
	istr >> _day;
	if (istr.fail()) {
		errCode(CIN_FAILED);
		return istr;
	}
	if (_year >= MIN_YEAR && _year <= MAX_YEAR) {
		if (_mon >= 1 && _mon <= 12) {
			if (_day >= 1 && _day <= mdays()) {
				errCode(NO_ERROR);
			}				
			else {
				errCode(DAY_ERROR);
			}
		}
		else {
			errCode(MON_ERROR);
		}
	}
	else {
		errCode(YEAR_ERROR);
	}
	return istr;
}

std::ostream& Date::write(std::ostream& ostr)const {
	ostr << _year << "/";
	ostr.setf(ios::right);
	ostr << std::setw(2) << std::setfill('0') << _mon;
	ostr << "/";
	ostr << std::setw(2) << std::setfill('0') << _day;
	ostr.unsetf(ios::right);
	return ostr;
}

	// non-memeber operator overloads
std::istream& operator>>(std::istream& i, Date& c) {
	c.read(i);
	return i;
}

std::ostream& operator<<(std::ostream& o, const Date& c) {
	c.write(o);
	return o;
}

}
