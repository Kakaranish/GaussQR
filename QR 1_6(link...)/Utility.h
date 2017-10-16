#pragma once
#include "Libs.h"
#include "Matrix.h"
#include <vector>
#include <utility>


bool gauss(Matrix&  A, Vector&  B, Vector& X);
Vector project(const Vector& vec_e, const Vector& vec_a);
std::pair<Matrix, Matrix> findQRPair(Matrix& matrix_A);
Vector findEigenvalues(Matrix& A, int steps);