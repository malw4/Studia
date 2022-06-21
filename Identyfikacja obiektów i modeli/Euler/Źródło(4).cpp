#include <iostream>
#include <math.h>
#include <fstream>
using namespace std;
double A1, A2, A3, e_dot = 10, T = 675, tcr = 0.1, Rocr;
fstream plik("wyn.txt", std::ios::out);
double ro[1000];
int pom1 = 0;
int start;
double a[13] = { 2.1 * pow(10,-3),176,19.5 * pow(10,3),0.000148 * 3 * pow(10,10),151 * pow(10,3),0.973,5.77,1,0,0.262,0,0.000605 * pow(10,13),0.167 };

double f(double t, double y, double tcr) {
	double fun;

	if (t < tcr)
		fun = A1 * e_dot - A2 * y * e_dot;
	else {
		int pom = (t - tcr) * 10;
		fun = A1 * e_dot - A2 * y * e_dot - A3 * pow(y, a[7]) * ro[pom];
	}
	return fun;
}
double y;
void euler(double x, double x0, double y0, double h) {
	int  val;
	y = y0;
	while (x0 < x) {
		if (pom1 == 0) {
			if (y >= Rocr) {
				tcr = x0;
				pom1 = 1;
			}
		}
		y = y0 + h * f(x0, y, tcr);
		y0 = y;
		x0 += h;
		val = (x0 - start) * 10;
		ro[val] = y;

		//cout << ro[val] <<endl;
	}
	plik << y << endl;
	cout << "x = " << x << " y = " << y << endl;
}

int main() {
	for (int i = 0; i < 1000; i++) {
		ro[i] = 0;
	}
	//double tcr, t = 0, Rocr = 0.4, Ro0 = 0, x = 0, h = 0.001;
	//tcr = 1 / A2 * log((Ro0 - (A1 / A2)) / (Rocr - (A1 / A2)));
	/*a[0] = (0 + ((double)(10 - 0) * rand() / (RAND_MAX)))*pow(10,-3);
	a[1] = 10 + ((double)(25000 - 10) * rand() / (RAND_MAX));
	a[2] = (1 + ((double)(100 - 1) * rand() / (RAND_MAX)))*pow(10,3);
	a[3] = (0 + ((double)(0.1 - 0) * rand() / (RAND_MAX)))* 3*pow(10, 10);
	a[4] = (10 + ((double)(500 - 10) * rand() / (RAND_MAX)))* pow(10, 3);
	a[5] = 0.1 + ((double)(1 - 0.1) * rand() / (RAND_MAX));
	a[6] = 1 + ((double)(10 - 1) * rand() / (RAND_MAX));
	a[7] = 0 + ((double)(10 - 0) * rand() / (RAND_MAX));
	a[8] = 0 + ((double)(10 - 0) * rand() / (RAND_MAX));
	a[9] = 0 + ((double)(1 - 0) * rand() / (RAND_MAX));
	a[10] = (0 + ((double)(1 - 0) * rand() / (RAND_MAX))) * pow(10, 13);
	a[11] = (0 + ((double)(0.1 - 0) * rand() / (RAND_MAX))) * pow(10, 13);
	a[12] = 0 + ((double)(1 - 0) * rand() / (RAND_MAX));*/
	double t = pow(10, 4), x = 0, h = 0.0001;
	double b = 0.25 * pow(10, -9), D = 30, fi = 45000, Q = 238000, Z, l, r, R = 8.314;

	T += 273;
	Z = e_dot * exp(Q / (R * T));
	Rocr = -1 * a[10] + a[11] * pow(Z, a[9]);
	l = a[0] / pow(Z, a[12]);
	A1 = 1 / (b * l);
	A2 = a[1] * pow(e_dot, -a[8]) * exp(-a[2] / (R * T));
	r = (pow(10, 6) * fi * pow(b, 2)) / 2;
	A3 = a[3] * r / D * exp(-a[4] / (R * T));
	start = 0;
	for (double x = 0; x <= 0.1; x += 0.0025) {
		euler(x, 0, 10000, h);
	}

	return 0;
}