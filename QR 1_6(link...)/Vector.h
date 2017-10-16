#pragma once
#include "Libs.h"
#include <ostream>
#include <string>

//Vector is just a matrix size x 1

class Vector {
private:
	double* arr;
	unsigned size; //size of arr
public:
	Vector(unsigned size);

	//Operator overloadings
	Vector& operator=(const Vector& vec);
	double& operator()(unsigned i);
	friend std::ostream& operator<<(std::ostream& output, const Vector& vec);
	Vector operator+(const Vector& q);
	Vector operator-(const Vector& q);
	Vector& operator+=(const Vector& vec);
	Vector& operator-=(const Vector& vec);

	
	Vector getMultipliedByScalar(double value) const; //we don't perform any operations on original object
	double scalarProduct(const Vector& vec1)const;
	double getVectorLength();
	inline unsigned getSize() const { return size; }
};
