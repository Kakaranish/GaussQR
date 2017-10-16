#include "Matrix.h"

void Matrix::init() { // Filling the array with 0
	for (unsigned i = 0; i < size.y; i++)
		for (unsigned j = 0; j < size.x; j++)
			arr[i][j] = 0;
}

void Matrix::deallocate2DArray(double**& arr, unsigned size_y) { // Deallocating memory 
	for (unsigned i = 0; i < size_y; i++)
		delete[] arr[i];
	delete[] arr;
}

Matrix::Matrix(unsigned y_size, unsigned x_size) {
	arr = new double*[y_size];
	for (unsigned i = 0; i < y_size; i++)
		arr[i] = new double[x_size];
	size = Vec2<unsigned>(x_size, y_size);
	init();
}

Matrix::Matrix(Vec2<unsigned>size): size(size) {
	arr = new double*[size.y];
	for (unsigned i = 0; i < size.y; i++)
		arr[i] = new double[size.x];
	init();
}

Matrix::~Matrix() {
	if (!remFlag)
		return;
	deallocate2DArray(this->arr, size.y);
}


/*/////////////////////////////////
ACTIONS ON THE MATRIX
/////////////////////////////////*/

Matrix Matrix::multiply(Matrix const &B) {
	Matrix rMatrix(size.y, B.size.x);
	if (size.x != B.size.y) {
		std::cout << "Unable to multiply matrixes! Wrong dimensions!" << std::endl;
		exit(-1);
	}


	for (unsigned i = 0; i < size.y; i++)
		for (unsigned j = 0; j < B.size.x; j++) {
			double sum = 0;
			for (unsigned k = 0; k < size.x; k++)
				sum += (arr[i][k] * B.arr[k][j]);
			rMatrix(i, j) = sum;
		}

	rMatrix.blockDeallocation();
	return std::move(rMatrix);
}

Matrix Matrix::transpose() {

	Matrix tMatrix(size.x, size.y);
	tMatrix.blockDeallocation();

	for (unsigned i = 0; i < size.x; i++) 
		for (unsigned j = 0; j < size.y; j++)
			tMatrix(i,j) = arr[j][i];
	

	return std::move(tMatrix);
}

/*/////////////////////////////////
OTHER FUNCTIONS
/////////////////////////////////*/

Vector Matrix::getVector(unsigned col) const {
	Vector tVector(size.y);
	for (int i = 0; i < size.y; i++)
		tVector(i) = this->arr[i][col];
	return std::move(tVector);
}

double& Matrix::operator()(unsigned y, unsigned x) {
	return arr[y][x];
}

std::ostream& operator<<(std::ostream& output, const Matrix& _m) {
	for (unsigned i = 0; i < _m.size.y; i++) {
		for (unsigned j = 0; j < _m.size.x; j++)
			output << _m.arr[i][j] << " ";
		output << std::endl;
	}
	return output;
}

