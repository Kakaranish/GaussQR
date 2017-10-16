#pragma once
#include "Matrix.h"

class BandMatrix : public Matrix {
public:
	BandMatrix(unsigned size, double valueOnDiagonal, double valueInEvir, double c = 0);
};
