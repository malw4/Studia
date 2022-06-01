#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

double* Funkcja(double* X) {
	double* F =new double[2];
	F[0] = pow(X[0], 3) + 2 * pow(X[1], 2);
	F[1] = 4 * X[0] + sin(X[1]);
	return F;
}
double** Jakobian(double*X) {
	double** F = new double* [2]; //Jakobian
	for (int i = 0; i < 2; i++)
		F[i] = new double[2];
	F[0][0] = 3 * pow(X[0], 2); //poszczególne wartoœci w macierzy 2x2
	F[0][1] = 4 * X[1]; 
	F[1][0] = 4;
	F[1][1] = cos(X[1]);
	return F;
 }

void newtonRaph() {
	fstream plik;
	plik.open("plik.txt", ios::in);
	double eps, N = 1000;
	double** X = new double* [N];
	double** J = new double* [N];
	double** F = new double* [N];
	for (int i = 0; i < N; i++) {
		F[i] = new double[2];
		J[i] = new double[2];
		X[i] = new double[2];
	}
	plik >> X[0][0];
	plik >> X[0][1];
	plik >> eps;
	F[0] = Funkcja(X[0]);
	J = Jakobian(X[0]);
	cout << "Krok: 0" << endl << "X = " << X[0][0] << " | " << X[0][1] << " wartosci F =  " << F[0][0] << " | " <<F[0][1] << endl;
	int k = 0;
	while (F[k][0] > eps || F[k][1] > eps) {
		k++;
		cout << "Krok: " << k << endl;
		double fi = J[0][0] * J[1][1] - (J[0][1] * J[1][0]);
		double f1 = (J[1][1] * F[k - 1][0] + (-1) * J[0][1] * F[k - 1][1]) / fi;
		double f2 = ((-1) * J[1][0] * F[k - 1][0] + J[0][0] * F[k - 1][1]) / fi;
		X[k][0] = X[k - 1][0] - f1;
		X[k][1] = X[k - 1][1] - f2;
		F[k] = Funkcja(X[k]);
		J = Jakobian(X[k]);
		cout << X[k][0] << " | " << X[k][1] << endl;
	}
	cout << "Dla X= " << X[k][0] << " | " << X[k][1]  << " jedna z wartosci " 
		<< F[k][0] << " | " << F[k][1] << endl << "jest blizsza zeru niz nadane przyblizenie " << eps << endl;
}


int main() {
	newtonRaph();
	system("PAUSE");
	return 0;
}