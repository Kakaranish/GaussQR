#include "BandMatrix.h"

BandMatrix::BandMatrix(unsigned size, double valueOnDiagonal, double valueInEvir, double c) : Matrix(size, size) {
	for (unsigned i = 0; i < size; i++) {
		this->arr[i][i] = valueOnDiagonal;

		if (i == size - 1)
			break;
		arr[i][i + 1] = valueInEvir;
		arr[i + 1][i] = valueInEvir;
	}
	arr[0][size - 1] = c;
	arr[size - 1][0] = c;
}