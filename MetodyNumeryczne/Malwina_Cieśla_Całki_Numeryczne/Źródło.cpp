#include <iostream>
#include <cmath>
#include <fstream>
#include <ctime>
using namespace std;

double Funkcja(double X) {
	double F = pow(X, 3) + 2 * pow(X, 2);
	return F;
}

double Simpson(double a, double b) {
	double srodek = (a + b) / 2;
	double pom = (b - a) / 6;
	return (Funkcja(a) + 4 * Funkcja(srodek) + Funkcja(b)) * pom;
}

double monte(double a, double b) {
	srand((unsigned)time(0));
	double fSrednia, pom = b - a;
	if (b < 1)
		b = 1;
	int p1 = (int)(rand() + a) % (int)b;
	int p2 = (int)(rand() + a) % (int)b;
	int p3 = (int)(rand() + a) % (int)b;
	int p4 = (int)(rand() + a) % (int)b;
	fSrednia = (Funkcja(p1) + Funkcja(p2) + Funkcja(p3) + Funkcja(p4)) / 4;
	return (fSrednia * (b - a));
}

double dwuwezle(double a, double b) {
	double pom;
	double* t = new double[2];
	double* x = new double[2];
	double* A = new double[2];
	A[0] = A[1] = 1;
	x[0] = (-pow(3, 0.5)) / 3;
	x[1] = pow(3, 0.5) / 3;
	for (int i = 0; i < 2; i++) {
		t[i] = ((a + b) / 2) + ((b - a) * x[i] / 2);
	}
	pom = Funkcja(t[0]) * A[0] + Funkcja(t[1]) * A[1];
	return (b - a) * pom / 2;
}

double czterowezle(double a, double b) {
	double pom;
	double* t = new double[4];
	double* x = new double[4];
	double* A = new double[4];
	A[0] = A[3] = (18 - pow(30, 0.5)) / 36;
	A[1] = A[2] = (18 + pow(30, 0.5)) / 36;
	x[0] = -pow((525 + 70 * pow(30, 0.5)), 0.5) / 35;
	x[1] = -pow((525 - 70 * pow(30, 0.5)), 0.5) / 35;
	x[2] = pow((525 - 70 * pow(30, 0.5)), 0.5) / 35;
	x[3] = pow((525 + 70 * pow(30, 0.5)), 0.5) / 35;
	for (int i = 0; i < 4; i++)
		t[i] = (a + b) / 2 + (b - a) * x[i] / 2;
	pom = Funkcja(t[0]) * A[0] + Funkcja(t[1]) * A[1] + Funkcja(t[2]) * A[2] + Funkcja(t[3]) * A[3];
	return (b - a) / 2 * pom;
}

void calki() {
	double* X = new double[2];
	int przedzial;
	cout << "Funkcja uzyta : y = x^3 + 2x^2" << endl;
	cout << "Podaj poczatek przedzialu" << endl;
	cin >> X[0];
	cout << "Podaj koniec przedzialu" << endl;
	cin >> X[1];
	cout << "Na ile przedzialow podzielic przedzial startowy? Podaj liczbe:" << endl;
	cin >> przedzial;
	double p = (X[1] - X[0]) / przedzial, simp = 0, mone = 0, dwu = 0, cztero = 0;
	cout << endl <<"Na przedziale <" << X[0] << "," << X[1] << "> dokonano " << przedzial << " podzialow i zostala wykonana " << endl;
	for (int i = 0; i < przedzial; i++) {
		X[1] = X[0] + p;
		simp += Simpson(X[0], X[1]);
		mone += monte(X[0], X[1]);
		dwu += dwuwezle(X[0], X[1]);
		cztero += czterowezle(X[0], X[1]);
		X[0] = X[1];
	}
	cout << endl << "Metoda Simpsona: " << endl << simp << endl;
	cout << endl << "Metoda Monte Carlo: " << endl << mone << endl;
	cout << endl << "Metoda dwoch wezlow: " << endl << dwu << endl;
	cout << endl << "Metoda czterech wezlow: " << endl << cztero << endl;
}

int main() {
	calki();
	system("PAUSE");
	return 0;
}