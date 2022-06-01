#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

double Funkcja(double X) {
	double F = log(X);
	return F;
}

void calki() {
	fstream plik;
	plik.open("plik.txt", ios::in);
	int N;
	double Pole = 0, Pole2=0, dl;
	plik >> N;
	double* X = new double[N];
	double* F = new double[N];
	plik >> X[0];
	plik >> X[N - 1];
	dl = abs(X[0] - X[N - 1]) / N;
	F[0] = Funkcja(X[0]);
	Pole += X[0] * dl;
	cout << "Na przedziale <" << X[0] << "," << X[N - 1] << "> tworze " << N << " podzialow o dlugosci " << dl << endl << endl;
	cout <<"Metoda Prostokatow:" << endl;
	for (int i = 0; i < N - 1; i++) {
		X[i + 1] = X[i] + dl;
		F[i + 1] = Funkcja(X[i + 1]);
		Pole += F[i + 1] * dl;
		//cout << F[i + 1] * dl << endl;
	}
	cout << "Razem: " <<Pole << endl << endl << "Metoda Trapezow:" << endl;
	for (int i = 0; i < N; i++) {
		X[i + 1] = X[i] + dl;
		F[i + 1] = Funkcja(X[i + 1]);
		Pole2 += (F[i] + F[i + 1]) * dl / 2;
		//cout << F[i + 1] * dl << endl;
	}
	cout <<"Razem: " <<  Pole2 << endl;
}

int main() {
	calki();
	system("PAUSE");
	return 0;
}