#pragma once
#include "Libs.h"
#include <type_traits>
#include "Vec2.h"
#include "Vector.h"


class Matrix {
protected:
	double** arr; //In this array are stored values of matrix
	Vec2<unsigned> size; /*
							size.y - quantity of lines
							size.x - quantity of columns
						   */

private:
	bool remFlag = true; /*
						 If we've used std::move on any Matrix object
						 it's necessary to block deallocation of arr, when destructor is calling, 
						 */
	
	void init(); //Fill the matrix with zeros
	static void deallocate2DArray(double**& arr, unsigned size_y); //Dealocating double** arr
public:
	Matrix(unsigned y_size, unsigned x_size); 
	Matrix(Vec2<unsigned>size); //this constructor is equivalent to the above
	~Matrix();
	inline void blockDeallocation() { remFlag = false; } //Turning off deallocating of arr at the end of life of object

	Matrix multiply(Matrix const &B); //ordinary multiplication of two matrices
	Matrix transpose(); //return transposed matrix

	inline const Vec2<unsigned>& getSize()const { return size; }
	Vector getVector(unsigned col) const; //Returns vector that's part of matrix
	double& operator()(unsigned y, unsigned x); //Easy way to have acces to specific element of arr. Arr is still protected
	friend std::ostream& operator<<(std::ostream& output, const Matrix& vec);
};

