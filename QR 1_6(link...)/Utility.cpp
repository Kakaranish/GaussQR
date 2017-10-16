#include "Utility.h"


bool gauss(Matrix&  A, Vector&  B, Vector& X) {

	if (A.getSize().x != A.getSize().y) {
		std::cout << "Unable to perform Gaussian Elimination!" << std::endl;
		exit(-1);
	}

	double m, s;
	unsigned size = A.getSize().x;
	double eps = 1e-12; //lower value than this will be trated as zero

						//Here we are creating extended matrix [A|B]
	Matrix AB(size, size + 1);
	for (unsigned i = 0; i < size; i++) {
		for (unsigned j = 0; j < size; j++)
			AB(i, j) = A(i, j);
		AB(i, size) = B(i);
	}

	//Elimination of coefficients
	for (int i = 0; i < size - 1; i++) {
		for (int j = i + 1; j < size; j++) {
			if (fabs(AB(i, i)) < eps)
				return false;
			m = -AB(j, i) / AB(i, i);
			for (int k = i + 1; k <= size; k++)
				AB(j, k) += m * AB(i, k);
		}
	}

	//Computing X matrix

	//in this loop we have to init i to int type, because if i=0, and loop iterates, then unsigned i will be very big positive number
	//and we will go out of range
	for (int i = size - 1; i >= 0; i--) {
		s = AB(i, size);
		for (unsigned j = size - 1; j >= i + 1; j--)
			s -= AB(i, j) * X(j);
		if (fabs(AB(i, i)) < eps)
			return false;
		X(i) = s / AB(i, i);
	}
	return true;
}


Vector project(const Vector& vec_e, const Vector& vec_a) {
	if (vec_e.getSize() != vec_a.getSize()) {
		std::cout << "Unable to perform projection!" << std::endl;
		exit(-1);
	}
	double scalar_ea = vec_e.scalarProduct(vec_a);
	double scalar_ee = vec_e.scalarProduct(vec_e);

	Vector proj_ea = vec_e.getMultipliedByScalar(scalar_ea / scalar_ee);
	return std::move(proj_ea);
}



std::pair<Matrix, Matrix> findQRPair(Matrix& matrix_A) {
	Vec2<unsigned> size = matrix_A.getSize();
	if (size.x != size.y) { //we need to have square matrix
		std::cout << "Unable to perform orthogonalization!" << std::endl;
		exit(-1);
	}

	std::vector<Vector> vec_a;
	std::vector<Vector> vec_u;


	for (unsigned k = 0; k < size.x; k++) {
		vec_a.push_back(matrix_A.getVector(k));
		//vec_a[k] = matrix_A.getVector(k);
		vec_u.push_back(vec_a[k]);

		for (unsigned j = 0; j < k; j++)
			vec_u[k] -= project(vec_u[j], vec_a[k]);
		//Normalizing vector
		vec_u[k] = vec_u[k].getMultipliedByScalar(1.f / vec_u[k].getVectorLength());


	}
	Matrix qMatrix(size.y, size.x);
	qMatrix.blockDeallocation();
	for (unsigned i = 0; i<size.x; i++) //we need to go through the vectors
		for (unsigned j = 0; j < size.y; j++)
			qMatrix(j, i) = vec_u[i](j);


	Matrix rMatrix(size.y, size.x);
	rMatrix.blockDeallocation();
	rMatrix = qMatrix.transpose().multiply(matrix_A);
	return std::pair<Matrix, Matrix>(std::move(qMatrix), std::move(rMatrix));
}

Vector findEigenvalues(Matrix& A, int steps) {
	Vec2<unsigned> size = A.getSize();
	if (size.x != size.y) {
		std::cout << "Unable to find eigenvalues!" << std::endl;
		exit(-1);
	}

	std::pair<Matrix, Matrix> *QRk, *QRk1;
	Matrix Ak(size), Ak1(size);

	QRk = new std::pair<Matrix, Matrix>(Matrix(size), Matrix(size));
	Ak = A;

	for (unsigned k = 0; k < steps; k++) {
		*QRk = findQRPair(Ak);
		Ak = QRk->second.multiply(QRk->first);
	}

	Vector result(size.x);
	for (unsigned i = 0; i < size.x; i++)
		result(i) = Ak(i, i);


	//std::cout << Ak << std::endl; ///////////////////////////////////////////////////////////////TEMP
	return std::move(result);
}