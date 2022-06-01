#include <iostream>
#include <cmath>
#include <fstream>
#include <ctime>
using namespace std;

double Funkcja(double X, double y) {
	double F = 2*X + y+3;
	return F;
}

double rungedwa(double* X, double* Y, double h, int N) {
	double k1, k2, fi;
	for (int i = 0; i < N; i++) {
		k1 = Funkcja(X[i], Y[i]);
		k2 = Funkcja(X[i] + h, Y[i] + h * k1);
		fi = (k1 + k2) / 2;
		Y[i + 1] = Y[i] + h * fi;
	}
	return Y[N];
}

double rungecztery(double* X, double* Y, double h, int N) {
	double k1, k2, k3, k4, fi;
	for (int i = 0; i < N; i++) {
		k1 = Funkcja(X[i], Y[i]);
		k2 = Funkcja(X[i] + h / 2, Y[i] + (h * k1) / 2);
		k3 = Funkcja(X[i] + h / 2, Y[i] + (h * k2) / 2);
		k4 = Funkcja(X[i] + h, Y[i] + h * k3);
		fi = (k1 + 2 * k2 + 2 * k3 + k4) / 6;
		Y[i + 1] = Y[i] + h * fi;
	}
	return Y[N];
}

void calki() {
	int N = 0;
	double h, pom, y;
	cout << "Funkcja uzyta : y'(x) = 2x + y(x) + 3" << endl;
	cout << "Podaj warunek poczatkowy y(0)=" << endl;
	cin >> y;
	cout << "Podaj punkt koncowy" << endl;
	cin >> pom;
	cout << "Podaj ilosc krokow" << endl;
	cin >> N;
	h = pom / N;
	double* X = new double[N];
	double* Y = new double[N];
	X[0] = 0;
	Y[0] = y;
	X[N] = pom;
	cout << endl << "Na przedziale <" << X[0] << "," << X[N] << "> dokonano " << N << " krokow co " << h << endl;
	for (int i = 0; i < N; i++) {
		X[i + 1] = X[i] + h;
		Y[i + 1] = Y[i] + h * Funkcja(X[i], Y[i]);
	}
	cout << "Metoda Eulera: y(" << X[N] << ") = " << Y[N] << endl;
	cout << "Metoda RK2: y(" << X[N] << ") = " << rungedwa(X, Y, h, N) << endl;
	cout << "Metoda RK4: y(" << X[N] << ") = " << rungecztery(X, Y, h, N) << endl;

}

int main() {
	calki();
	system("PAUSE");
	return 0;
}