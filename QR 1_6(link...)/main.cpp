#include "Matrix.h"
#include "Vec2.h"
#include "BandMatrix.h"
#include "Utility.h"



int main(){
	
	BandMatrix b(9, 4, 1, 1);
	std::cout << b << std::endl << std::endl;
	std::cout << findEigenvalues(b, 300) << std::endl;
	/*
	BandMatrix bandMatrix(9, 4, 1, 0);
	//macierz 9x9 z c=1
	Vector B(9); //wektor z wartosciami od 1 do n
	for (unsigned i = 0; i < 9; i++)
		B(i) = i + 1;
	Vector X(9);//pusty wektor na odpowiedzi
	if (gauss(bandMatrix, B, X))
		std::cout <<"Rozwiazania ukladu rownan: "<< X << std::endl;

	std::cout << "Wartosci wlasne macierzy: " << findEigenvalues(bandMatrix, 200) << std::endl;
	*/
	_getch();
	return 0;
}