#pragma once
#include <iostream>
#include "conio.h"

class Tropical_Int {
public :
	Tropical_Int() {
		// :(
	}
	~Tropical_Int() {
		// :(
	}
	Tropical_Int(const Tropical_Int &num) {
		this->num = num.num;
	}
	Tropical_Int(Tropical_Int &&num) {
		this->num = num.num;
	}
	Tropical_Int(const int &num) {
		this->num = num;
	}
	Tropical_Int(int &&num) {
		this->num = num;
	}
	Tropical_Int& operator = (const int &num) {
		this->num = num;
		return *this;
	}
	Tropical_Int& operator = (int &&num) {
		this->num = num;
		return *this;
	}
	bool operator == (Tropical_Int num) {
		return (this->num == num.num);
	}

	bool operator != (Tropical_Int num) {
		return (this->num != num.num);
	}
	Tropical_Int& operator = (const Tropical_Int &num) {
		this->num = num.num;
		return *this;
	}
	Tropical_Int& operator = (Tropical_Int &&num) {
		this->num = num.num;
		return *this;
	}
	Tropical_Int operator * (const Tropical_Int &num) {
		Tropical_Int newNum;
		newNum = this->num;
		newNum.num += num.num;
		return newNum;
	}
	Tropical_Int& operator *= (const Tropical_Int &num) {
		this->num += num.num;
		return *this;
	}

	Tropical_Int operator / (const Tropical_Int &num) {
		Tropical_Int newNum;
		newNum = this->num;
		newNum.num -= num.num;
		return newNum;
	}
	Tropical_Int& operator /= (const Tropical_Int &num) {
		this->num -= num.num;
		return *this;
	}
	Tropical_Int operator + (const Tropical_Int &num) {
		Tropical_Int newNum;
		newNum.num = this->num > num.num ? this -> num : num.num;
		return newNum;
	}
	Tropical_Int& operator += (const Tropical_Int &num) {
		if (this->num < num.num) this->num = num.num;
		return *this;
	}
	
	Tropical_Int operator - (const Tropical_Int &num) {
		Tropical_Int newNum;
		newNum.num = this->num < num.num ? this->num : num.num;
		return newNum;
	}
	Tropical_Int& operator -= (const Tropical_Int &num) {
		if (this->num > num.num) this->num = num.num;
		return *this;
	}
	bool operator < (const Tropical_Int &num) {
		return (this->num < num.num);
	}
	bool operator <= (const Tropical_Int &num) {
		return (this->num <= num.num);
	}
	bool operator > (const Tropical_Int &num) {
		return (this->num > num.num);
	}
	bool operator >= (const Tropical_Int &num) {
		return (this->num >= num.num);
	}

	friend std::ostream& operator << (std::ostream &os , const Tropical_Int &num) {
		os << num.num;
		return os;
	}
	friend  std :: istream& operator >> (std :: istream & is, Tropical_Int & num) {
		is >> num.num;
		return is;
	}

	int getNum() {
		return this->num;
	}

	static Tropical_Int abs(Tropical_Int num) {
		return num = abs(num.num);
	}

private :
	int num;
};