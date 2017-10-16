#include "Vector.h"

//constructor
Vector::Vector(unsigned size) :size(size) {
	arr = new double[size];
	for (unsigned i = 0; i < size; i++)
		arr[i] = 0;
}

/*///////////////////////////
	OPERATOR
		OVERLOADINGS
///////////////////////////*/

Vector& Vector::operator=(const Vector& vec) {
	if (this->size != vec.size) {
		std::cout << "Unable to perform = operation!" << std::endl;
		exit(-2);
	}
	for (unsigned i = 0; i < size; i++)
		arr[i] = vec.arr[i];
	return *this;
}

double& Vector::operator()(unsigned i) {
	return arr[i];
}

std::ostream& operator<<(std::ostream& output, const Vector& vec) {
	output << "[ ";
	for (unsigned i = 0; i < vec.size; i++)
		output << vec.arr[i] << [](unsigned x, unsigned size)
		->std::string {return (x != size - 1) ? ", " : " ]"; }(i, vec.size);
	return output;
}

Vector Vector::operator+(const Vector& q) {
	if (q.size != this->size) {
		std::cout << "Unable to add given vectors!" << std::endl;
		exit(-1);
	}
	Vector tVec(size);
	for (unsigned i = 0; i < size; i++)
		tVec(i) = this->arr[i] + q.arr[i];
	return std::move(tVec);
}


Vector Vector::operator-(const Vector& q) {
	if (q.size != this->size) {
		std::cout << "Unable to subtract given vectors!" << std::endl;
		exit(-1);
	}
	Vector tVec(size);
	for (unsigned i = 0; i < size; i++)
		tVec(i) = this->arr[i] - q.arr[i];
	return std::move(tVec);
}

Vector& Vector::operator+=(const Vector& vec) {
	if (this->size != vec.size) {
		std::cout << "Unable to perform += operation!" << std::endl;
		exit(-1);
	}
	for (unsigned i = 0; i < vec.size; i++)
		this->arr[i] += vec.arr[i];
	return *this;
}
Vector& Vector::operator-=(const Vector& vec) {
	if (this->size != vec.size) {
		std::cout << "Unable to perform -= operation!" << std::endl;
		exit(-1);
	}
	for (unsigned i = 0; i < vec.size; i++)
		this->arr[i] -= vec.arr[i];
	return *this;
}


////////////////////////////////////////////////////////////////////////////////


Vector Vector::getMultipliedByScalar(double value) const {
	Vector tVec(this->size);
	for (unsigned i = 0; i < size; i++)
		tVec(i) = this->arr[i] * value;
	return std::move(tVec);
}


double Vector::scalarProduct(const Vector& vec1)const {
	if (vec1.size != size) {
		std::cout << "Unable to compute scalar product!" << std::endl;
		exit(-1);
	}
	double result = 0;
	for (unsigned i = 0; i < size; i++)
		result += (vec1.arr[i] * arr[i]);

	return result;
}

double Vector::getVectorLength() {
	double sum = 0;
	for (unsigned i = 0; i < size; i++)
		sum += pow(arr[i], 2);
	return sqrt(sum);
}