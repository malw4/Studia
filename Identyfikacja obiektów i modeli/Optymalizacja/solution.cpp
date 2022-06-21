//Do not edit the code below (unless you know what you are doing)
#define _USE_MATH_DEFINES
#include<cmath>
#include <string>
#include <fstream>
#include "solution.h"


int solution::f_calls = 0;
int solution::g_calls = 0;
int solution::H_calls = 0;

solution::solution(double L)
{
	x = matrix(L);
	g = NAN;
	H = NAN;
	y = NAN;
}

solution::solution(const matrix &A)
{
	x = A;
	g = NAN;
	H = NAN;
	y = NAN;
}

solution::solution(double *A, int n)
{
	x = matrix(A, n);
	g = NAN;
	H = NAN;
	y = NAN;
}

void solution::clear_calls()
{
	f_calls = 0;
	g_calls = 0;
	H_calls = 0;
}

ostream &operator<<(ostream &S, const solution &A)
{
	S << "x = " << A.x << endl;
	S << "y = " << A.y << endl;
	S << "f_calls = " << solution::f_calls << endl;
	S << "g_calls = " << solution::g_calls << endl;
	S << "H_calls = " << solution::H_calls << endl;
	return S;
}

double solution::f(double A1, double A2, double A3, double e_dot, matrix x, double t, double y, double tcr, double* ro) {
	double fun;

	if (t < tcr)
		fun = A1 * e_dot - A2 * y * e_dot;
	else {
		int pom = (t - tcr) * 10;
		fun = A1 * e_dot - A2 * y * e_dot - A3 * pow(y, x(7)) * ro[pom];
	}
	return fun;
}

double solution::euler(double A1, double A2, double A3, double e_dot, matrix xmat,double x, double y, double x0, double y0, double h,double tcr,double Rocr,double* ro) {
	int  val;
	int pom1 = 0;
	int start = 0;
	y = y0;
	while (x0 < x) {
		if (pom1 == 0) {
			if (y >= Rocr) {
				tcr = x0;
				pom1 = 1;
			}
		}
		y = y0 + h * f(A1,A2,A3,e_dot,xmat,x0, y, tcr,ro);
		y0 = y;
		x0 += h;
		val = (x0 - start) * 10;
		ro[val] = y;

		//cout << ro[val] <<endl;
	}
	//plik << y << endl;

	//cout << "x = " << x << " y = " << y << endl;
	return y;
}
//You can edit the following code

void solution::fit_fun(matrix O)
{
#if LAB_NO == 2

#elif LAB_NO == 3;

#if LAB_PART == 0
	

#endif

#elif LAB_NO == 9
#if LAB_PART == 1
string pom;
int T;
string a = " ";
fstream f;
f.open("wyniki1.txt", std::ios::out);
y = matrix(1, 1);
double epsilon = 0.001, R = 8.314, W, sigma, eps, sigma_p, e_dot;
long double S = 0.0, p, wyn = 0.0;
for (int i = 1; i < 10; i++) {
	fstream fin;
	if (i == 1)
		fin.open("Doswiadczenia(1).txt", std::ios::in);
	else if (i == 2)
		fin.open("Doswiadczenia(2).txt", std::ios::in);
	else if (i == 3)
		fin.open("Doswiadczenia(3).txt", std::ios::in);
	else if (i == 4)
		fin.open("Doswiadczenia(4).txt", std::ios::in);
	else if (i == 5)
		fin.open("Doswiadczenia(5).txt", std::ios::in);
	else if (i == 6)
		fin.open("Doswiadczenia(6).txt", std::ios::in);
	else if (i == 7)
		fin.open("Doswiadczenia(7).txt", std::ios::in);
	else if (i == 8)
		fin.open("Doswiadczenia(8).txt", std::ios::in);
	else if (i == 9)
		fin.open("Doswiadczenia(9).txt", std::ios::in);

	S = 0.0;
	fin >> T;
	fin >> e_dot;
	for (int j = 1; j < 22; j++) {
		fin >> pom;
		eps = std::stod(pom);
		fin >> pom;
		sigma_p = std::stof(pom);


		W = exp(-x(6) * eps);
		sigma = (W * x(0) * pow(eps, x(1)) * exp(x(3) / (R * (T + 273))) + (1 - W) * x(4) * exp(x(5) / (R * (T + 273)))) * pow(e_dot, x(2));

		//cout << sigma_p << "  ,   " << sigma << endl;
		f << sigma_p<<' ' <<sigma << endl;
		if (sigma_p != 0) {
			p = (sigma_p - sigma) / sigma_p;
			y(0) += p * p;
		}

	}

	fin.close();
}
#elif LAB_PART == 2

double T, Qdef = 312000, epsilon = 0.001, Rs = 8.314, R, Z;
double Sigma, Sigma_p, sigma0, sigmaSS, sigmaSSE, epsi, epsR, epsXS, epsXR, epsC, nsse, a, b, e_dot;
long double S = 0.0, p, wyn = 0.0;
int j,i;
y = matrix(1, 1);
fstream fin;
fstream f;
f.open("wynikisigm.txt", std::ios::out);
fin.open("zad2.txt", std::ios::in);
for (j = 0; j < 9; j++) {
	for ( i = 0; i < 52; i++) {
		fin >> T;
		T += 273;
		fin >> e_dot;
		Z = e_dot * exp(Qdef / T * Rs);
		sigma0 = 1 / x(2) * pow(sinh(pow(Z / x(0), 1 / x(1))), -1);
		sigmaSSE = 1 / x(5) * pow(sinh(pow(Z / x(3), 1 / x(4))), -1);
		sigmaSS = 1 / x(9) * pow(sinh(pow(Z / x(8), 1 / x(9))), -1);
		epsR = (x(6) + x(7) * pow(sigmaSSE, 2)) / 3.23;
		epsC = x(11) * pow(Z / pow(sigmaSSE, 2), x(12));
		epsXS = x(13) * pow(Z / pow(sigmaSSE, 2), x(14)) + epsC;
		epsXR = (epsXS - epsC) / 1.98 + epsC;
		fin >> epsi;
		fin >> Sigma_p;
		if (epsi > epsC)
			R = (sigmaSSE - sigmaSS) * (1 - exp(-1 * pow((epsi - epsC) / (epsXR - epsC), 2)));
		else
			R = 0;
		Sigma = sigma0 + (sigmaSSE - sigma0) * pow(1 - exp(-1 * epsi / epsR), 1 / 2) - R;
		//f << Sigma <<  endl;
		y(0) = y(0)+pow((Sigma_p - Sigma) / Sigma_p, 2);
		
	
	}
}
#elif LAB_PART == 3
double t, odl, h , tcr; 
fstream plik;
plik.open("wynikiobliczone.txt", std::ios::out);
int i, j=0;
double S,b = 0.25 * pow(10, -9), D = 30, fi = 43500, Q = 312000, Z, l, r, R = 8.314,Rocr,Ro,RO;
	for ( i = 1; i < 10; i++) {
		fstream fin;
		if (i == 1) {
			fin.open("Doswiadczenia1.txt", std::ios::in);
			tcr = 1.00E-01;
			h = 1.00E-04;
		}
		else if (i == 2) {
			fin.open("Doswiadczenia2.txt", std::ios::in);
			tcr = 1.00E-01;
			h = 1.00E-04;
		}
		else if (i == 3) {
			fin.open("Doswiadczenia3.txt", std::ios::in);
			tcr = 1.00E-01;
			h = 1.00E-04;
		}
		else if (i == 4) {
			fin.open("Doswiadczenia4.txt", std::ios::in);
			tcr = 1.00E-00;
			h = 1.00E-03;
		}
		else if (i == 5) {
			fin.open("Doswiadczenia5.txt", std::ios::in);
			tcr = 1.00E-00;
			h = 1.00E-03;
		}
		else if (i == 6) {
			fin.open("Doswiadczenia6.txt", std::ios::in);
			tcr = 1.00E-00;
			h = 1.00E-03;
		}
		else if (i == 7) {
			fin.open("Doswiadczenia7.txt", std::ios::in);
			tcr = 1.00E+01;
			h = 1.00E-02;
		}
		else if (i == 8) {
			fin.open("Doswiadczenia8.txt", std::ios::in);
			tcr = 1.00E+01;
			h = 1.00E-02;
		}
		else if (i == 9) {
			fin.open("Doswiadczenia9.txt", std::ios::in);
			tcr = 1.00E+01;
			h = 1.00E-02;
		}
		S = 0.0;
		fin >> T;
		T += 273;
		fin >> e_dot;
		Z = e_dot * exp(Q / (R * T));
		Rocr = -1 * x(10) + x(11) * pow(Z, x(9));
		l = x(0) / pow(Z, x(12));
		A1 = 1 / (b * l);
		A2 = x(1) * pow(e_dot, -x(8)) * exp(-x(2) / (R * T));
		r = (pow(10, 6) * fi * pow(b, 2)) / 2;
		A3 = x(3) * r / D * exp(-x(4) / (R * T));
		start = 0;
		for (j = 0; j < 100001;j++) {
			fin >> t;
			Ro=euler(A1, A2, A3, e_dot, x, t, 0, 0, 10000, h, tcr, Rocr, ro);
			plik << Ro << endl;
			fin >> RO;
			if (j != 0)
				y(0) = y(0) + pow((RO - Ro) / RO, 2);
			else
				y(0) = 0;
			//cout << y(0) << endl;
		//cout << pow((RO - Ro) / RO, 2) <<endl;
			//j++;
			if (j % 20000 == 0) {
				cout << "jestem j=" << j << endl;
				
			}
		}
		y(0) /= j;
		cout << i << endl;
		cout << y(0) << endl;
	}
	y(0) /= i;

plik.close();
//fin.close();

++f_calls;
#endif

#elif LAB_NO == 6
#if LAB_PART == 1
	double a = 100.0;

	int *n = get_size(O);	
	if (n[1] == 1) {
		y = matrix(2, 1);
		y(0) = a * (pow(x(0) - 5.0, 2.0) + pow(x(1) - 5.0, 2.0));
		y(1) = 1.0 / a * (pow(x(0) + 5.0, 2.0) + pow(x(1) + 5.0, 2.0));
		++f_calls;
	}
	else {
		solution temp;
		temp.x = O[0] + x * O[1];
		temp.fit_fun();
		y = O(0, 2)*temp.y(0) + (1.0 - O(0, 2))*temp.y(1);
	}
#else
	
	int *n = get_size(O);
	if (n[1] == 1) {
		y = matrix(3, 1);
		double ro = 7800, P = 1e3, E = 207e9;
		//masa
		y(0) = ro * x(0)*3.14*pow(x(1), 2.0) / 4.0;
		//ugiecie
		y(1) = 64.0*P*pow(x(0), 3.0) / (3.0 * E*3.14*pow(x(1), 4.0));
		//naprezenie
		y(2) = 32.0*P*x(0) / (3.14*pow(x(1), 3.0));
		++f_calls;
	}
	else {
		double f1min=0.440078, f1max=3.05745, 
			f2min=4.21679e-05, f2max= 0.00203537;

		solution T;
		T.x = O[0] + x * O[1];
		T.fit_fun();
		
		matrix yn(2, 1);
		yn(0) = (T.y(0) - f1min) / (f1max - f1min);
		yn(1) = (T.y(1) - f2min) / (f2max - f2min);

		y = O(0, 2)*yn(0) + (1.0 - O(0, 2))*yn(1);

		if (T.y(1) > 0.005)
			y = y + 1e6*pow(T.y(1) - 0.005, 2.0);
		if (T.y(2) > 300e6)
			y = y + 1e6*pow(T.y(2) - 300e6, 2.0);
	}
#endif

#elif LAB_NO == 7

#if LAB_PART == 1

	y(0) = x(0, 0)*x(0, 0) + x(1, 0)*x(1, 0) - cos(2.5*M_PI*x(0, 0)) - cos(2.5*M_PI*x(1, 0)) + 2.0;
	++f_calls;
#else
	double t0 = 0.0, dt = 0.1, t_end = 100.0;

	int N = 1001;
	static matrix X(N, 2);
	if (solution::f_calls == 0) {
		ifstream S("polozenia.txt");
		S >> X;
		S.close();
	}
	matrix Y0(4, 1);
	matrix *Y = solve_ode(t0, dt, t_end, Y0, x);
	y(0) = 0.0;
	for (int i = 0; i < N; i++) {
		y(0) = y(0) + fabs(X(i, 0) - Y[1](i, 0)) + fabs(X(i, 1) - Y[1](i, 2));
	}
	y(0) = y(0) / (2.0*N);

#endif
#else
	y = NAN;
	++f_calls;

#endif
}

void solution::grad(matrix O)
{
#if LAB_NO == 5
#if LAB_PART == 1
	g = matrix(2, 1);
	g(0) = 10.0*x(0) + 8.0*x(1) - 34.0;
	g(1) = 8.0*x(0) + 10.0*x(1) - 38.0;
	++g_calls;
#elif LAB_PART == 2
	int m = 100;
	int *n = get_size(x);
	static matrix X(n[0], m), Y(1, m);
	if (solution::g_calls == 0) {
		std::ifstream S("XData.txt");
		S >> X;
		S.close();
		S.open("YData.txt");
		S >> Y;
		S.close();
	}

	double h;
	g = matrix(n[0], 1);
	for (int j = 0; j < n[0]; ++j) {
		for (int i = 0; i < m; ++i) {
			h = (trans(x)*X[i])(0);
			h = 1.0 / (1.0 + exp(-h));
			g(j) = g(j) + X(j, i)*(h - Y(0, i));
		}
		g(j) = g(j) / m;
	}
	++g_calls;
#endif
#else
	g = NAN;
	++g_calls;
#endif

}

void solution::hess(matrix O)
{
#if LAB_NO == 5
#if LAB_PART == 1
	H = matrix(2, 2);
	H(0, 0) = 10;
	H(0, 1) = 8;
	H(1, 0) = 8;
	H(1, 1) = 10;
	++H_calls;
#else
	H = NAN;
	++H_calls;
#endif
#else
	H = NAN;
	++H_calls;
#endif
}
