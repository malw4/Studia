#include<iostream>
#include <cstdlib>
#include <iomanip>
#include<random>
#include<chrono>
#include<fstream>
#include<string.h>
#include"opt_alg.h"
#include"ode_solver.h"
using namespace std;

int main()
{
	try
	{
		std::cout << "LAB NUMBER " << LAB_NO << std::endl;
		std::cout << "LAB PART " << LAB_PART << std::endl << endl;

#if LAB_NO == 1

		double t0 = 0, dt = 0.1, tend = 50;
		matrix Y0 = matrix(new double[2]{ 1, 0 }, 2);


		matrix* Y = solve_ode(t0, dt, tend, Y0);
		ofstream S("tout.csv");
		S << Y[0];
		S.close();
		S.open("Yout.csv");
		S << Y[1];
		S.close();

#elif LAB_NO == 2

		double d = 1, alpha = 8, epsilon = 0.0001, gamma = 0.0001;
		int Nmax = 1000;

		random_device R;

		//zad 1

		//solution x_lag = lag(8.76742, 200.767, epsilon, gamma, Nmax);
		//
		//fstream file("tabela1_8.csv", fstream::out | fstream::trunc);
		//file << "x_0; a; b; expansion_fcalls; fib_x; fib_y; fib_fcalls; lag_x; lag_y; lag_fcalls\n";
		//
		//for (int i = 0; i < 100; i++) {
		//	double x0 = 200.0 * R() / R.max() - 100;
		//	
		//	double *e = expansion(x0, d, alpha, Nmax);
		//	int e_calls = solution::f_calls;
		//	solution::clear_calls();
		//
		//	solution x_fib = fib(e[0], e[1], epsilon);
		//	int fib_calls = solution::f_calls;
		//	solution::clear_calls();
		//
		//	solution x_lag = lag(e[0], e[1], epsilon, gamma, Nmax);
		//	int lag_calls = solution::f_calls;
		//	solution::clear_calls();
		//
		//	if (x_lag.x(0) != x_lag.x(0)) {
		//		i--;
		//	}
		//	else {
		//		file << x0 << ";";
		//		file << e[0] << ";" << e[1] << ";" << e_calls << ";";
		//		file << x_fib.x(0) << ";" << x_fib.y(0) << ";" << fib_calls << ";";
		//		file << x_lag.x(0) << ";" << x_lag.y(0) << ";" << lag_calls << ";";
		//		file << "\n";
		//	}
		//
		//}
		//file.close();


		////przypadek bez wstepnego zwezania przedzialu
		//solution x_fib = fib(-100, 100, epsilon);
		//cout << x_fib.x(0) << "," << x_fib.y(0) << "," << solution::f_calls << endl;
		//solution::clear_calls();
		//solution x_lag = lag(-100, 100, epsilon, gamma, Nmax);
		//cout << x_lag.x(0) << "," << x_lag.y(0) << "," << solution::f_calls << endl;
		//solution::clear_calls();


		//zad 2
		//double t0 = 0, dt = 1, tend = 1000;
		//matrix Y0 = matrix(new double[3]{ 5, 1, 10 }, 3);
		//double a = 0.0001, b = 0.01; //przedzia³ poszukiwania

		//solution Dfib = fib(a, b, epsilon);
		//cout << "Fibonacci " << Dfib << endl;
		//matrix* YFib = solve_ode(t0, dt, tend, Y0, Dfib.x);
		//ofstream S("wynikFib.csv");
		//S << YFib[1];
		//S.close();
		//solution::clear_calls();

		//solution Dlag = lag(a, b, epsilon, gamma, Nmax);
		//cout << "Lagrange " << Dlag << endl;
		//matrix* YLag = solve_ode(t0, dt, tend, Y0, Dlag.y);
		//S.open("wynikLag.csv");
		//S << YLag[1];
		//S.close();
		//solution::clear_calls();


#elif LAB_NO == 3

#if LAB_PART == 1
		random_device R;
		for (double s = 0.2; s < 1.0; s += 0.3) {
			double avg_HJ[3] = { 0.0,0.0,0.0 };
			int avg_f_calls_HJ = 0;
			int global_count_HJ = 0;

			double avg_Rosen[3] = { 0.0,0.0,0.0 };
			int avg_f_calls_Rosen = 0;
			int global_count_Rosen = 0;

			cout << "s: " << s << endl;

			string filename = "no3_part1_s" + to_string(s) + ".csv";
			fstream file(filename, fstream::out | fstream::trunc);
			file << "x1_0; x2_0; HJ_x1; HJ_x2; HJ_y; HJ_fcalls; HJ_global; Rosen_x1; Rosen_x2; Rosen_y; Rosen_fcalls; Rosen_global\n";

			int n = 100;
			for (int i = 0; i < n; i++) {
				double x0_ = 2.0 * R() / R.max() - 1.0;
				double x1_ = 2.0 * R() / R.max() - 1.0;
				double x00[2] = { x0_, x1_ };
				matrix x0(x00, 2);
				file << x0_ << ";" << x1_ << ";";

				solution x = HJ(x0, s, 0.5, 0.01, 1000);
				file << x.x(0, 0) << ";" << x.x(1, 0) << ";" << x.y(0) << ";" << solution::f_calls << ";";

				if (x.y(0) < 0.1) {
					avg_HJ[0] += x.x(0, 0); avg_HJ[1] += x.x(1, 0); avg_HJ[2] += x.y(0);
					avg_f_calls_HJ += solution::f_calls;
					++global_count_HJ;
					file << "TAK" << ";";
				}
				else {
					file << "NIE" << ";";
				}
				solution::clear_calls();

				double s00[2] = { s, s };
				matrix s0(s00, 2);

				x = Rosen(x0, s0, 2, 0.5, 0.01, 1000);
				file << x.x(0, 0) << ";" << x.x(1, 0) << ";" << x.y(0) << ";" << solution::f_calls << ";";

				if (x.y(0) < 0.1) {
					avg_Rosen[0] += x.x(0, 0); avg_Rosen[1] += x.x(1, 0); avg_Rosen[2] += x.y(0);
					avg_f_calls_Rosen += solution::f_calls;
					++global_count_Rosen;
					file << "TAK" << endl;
				}
				else {
					file << "NIE" << endl;
				}
				solution::clear_calls();
			}
			file.close();
			avg_HJ[0] /= global_count_HJ; avg_HJ[1] /= global_count_HJ; avg_HJ[2] /= global_count_HJ;
			avg_f_calls_HJ /= global_count_HJ;
			cout << avg_HJ[0] << " " << avg_HJ[1] << " " << avg_HJ[2] << " " << avg_f_calls_HJ << " " << global_count_HJ << endl;

			avg_Rosen[0] /= global_count_Rosen; avg_Rosen[1] /= global_count_Rosen; avg_Rosen[2] /= global_count_Rosen;
			avg_f_calls_Rosen /= global_count_Rosen;
			cout << avg_Rosen[0] << " " << avg_Rosen[1] << " " << avg_Rosen[2] << " " << avg_f_calls_Rosen << " " << global_count_Rosen << endl;

		}

		cout.precision(15);
		cout << "________________" << endl;
		double x0_ = 2.0 * R() / R.max() - 1.0;
		double x1_ = 2.0 * R() / R.max() - 1.0;
		double x00[2] = { x0_, x1_ };
		matrix x0(x00, 2);
		solution x = HJ(x0, 1.0, 0.5, 0.01, 1000);

		cout << "________________" << endl;
		double s00[2] = { 1.0, 1.0 };
		matrix s0(s00, 2);
		x = Rosen(x0, s0, 2, 0.5, 0.01, 1000);

#elif LAB_PART == 2
double alfa = 1, beta = 0.5, gama = 2, delta = 0.5, s = 0.5;
matrix O(2, 2);
O(0, 0) = -10;
O(0, 1) = 10;
O(1, 0) = -10;
O(1, 1) = 10;
fstream fin;
string pom;
double epsilon = 0.001, R = 8.314, W, sigma, eps, sigma_p, e_dot;
long double S = 0.0, p, wyn = 0.0;
double a[7];
int Nmax = 10000, T;
double h[3] = { 0,0,0 };
a[0] = 1 + ((double)(1000 - 1) * rand() / (RAND_MAX));
a[1] = 0 + ((double)(1 - 0) * rand() / (RAND_MAX));
a[2] = 0 + ((double)(1 - 0) * rand() / (RAND_MAX));
a[3] = 1 + ((double)(10000 - 1) * rand() / (RAND_MAX));
a[4] = 0 + ((double)(1 - 0) * rand() / (RAND_MAX));
a[5] = 1 + ((double)(90000 - 1) * rand() / (RAND_MAX));
a[6] = 0 + ((double)(1 - 0) * rand() / (RAND_MAX));
for (int i = 1; i < 10; i++) {
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


		W = exp(-a[6] * eps);
		sigma = (W * a[0] * pow(eps, a[1]) * exp(a[3] / (R * (T + 273))) + (1 - W) * a[4] * exp(a[5] / (R * (T + 273)))) * pow(e_dot, a[2]);

		cout << sigma_p << "  ,   " << sigma << endl;
		if (sigma_p != 0) {
			p = (sigma_p - sigma) / sigma_p;
			S += p * p;
		}

	}
	fin.close();
	matrix x0(a, 2);
	solution x = sym_NM(x0, h[1], epsilon, Nmax, O);
	std::cout << x.x(0) << "," << x.x(1) << "," << x.y(0) << "," << solution::f_calls << "," << solution::g_calls << "," << solution::H_calls << std::endl;
	wyn += S;
	cout << "Funkcja celu :" << S << endl;

}

cout << "Koñcowa funkcja celu :" << wyn << endl;
solution::clear_calls();

#endif
#elif LAB_NO == 4
#if LAB_PART == 1
		//dla metody funkcji zewnetrznej
		//double c = 1.0, dc = 2.0, epsilon = 1e-4;

		//dla metody funkcji wewnetrznej
		double c = 0.5, dc = 0.1, epsilon = 1e-4;

		int Nmax = 1000;
		double a[3] = { 4.0, 4.4934, 5.0 };

		std::uniform_real_distribution<double> d(1.0, 3.75);
		std::minstd_rand0 g(0);
		for (int i = 0; i < 3; i++) {
			//std::cout << a[i] << " ------" << std::endl;
			for (int k = 0; k < 100; k++) {
				double x0_ = d(g);
				double x1_ = d(g);
				if (sqrt(x0_ * x0_ + x1_ * x1_) - a[i] <= 0.0) {

					double x00[2] = { x0_, x1_ };
					matrix x0(x00, 2);
					std::cout << x0_ << "," << x1_ << ",";

					solution x = pen(x0, c, dc, epsilon, Nmax, matrix(new double[1]{ a[i] }, 1));

					double r = norm(x.x);
					std::cout << x.x(0) << "," << x.x(1) << "," << r << "," << x.y(0) << "," << solution::f_calls << std::endl;

					solution::clear_calls();
				}
				else {
					k--;
					continue;
				}
			}
		}


#elif LAB_PART == 2
double alfa = 1, beta = 0.5, gama = 2, delta = 0.5, s = 0.5;
matrix O(2, 2);
O(0, 0) = -10;
O(0, 1) = 10;
O(1, 0) = -10;
O(1, 1) = 10;
fstream fin;
string pom;
double epsilon = 0.001, R = 8.314, W, sigma, eps, sigma_p, e_dot;
long double S = 0.0, p, wyn = 0.0;
double a[7];
int Nmax = 10000, T;
double h[3] = { 0,0,0 };
a[0] = 1 + ((double)(1000 - 1) * rand() / (RAND_MAX));
a[1] = 0 + ((double)(1 - 0) * rand() / (RAND_MAX));
a[2] = 0 + ((double)(1 - 0) * rand() / (RAND_MAX));
a[3] = 1 + ((double)(10000 - 1) * rand() / (RAND_MAX));
a[4] = 0 + ((double)(1 - 0) * rand() / (RAND_MAX));
a[5] = 1 + ((double)(90000 - 1) * rand() / (RAND_MAX));
a[6] = 0 + ((double)(1 - 0) * rand() / (RAND_MAX));
for (int i = 1; i < 10; i++) {
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


		W = exp(-a[6] * eps);
		sigma = (W * a[0] * pow(eps, a[1]) * exp(a[3] / (R * (T + 273))) + (1 - W) * a[4] * exp(a[5] / (R * (T + 273)))) * pow(e_dot, a[2]);

		cout << sigma_p << "  ,   " << sigma << endl;
		if (sigma_p != 0) {
			p = (sigma_p - sigma) / sigma_p;
			S += p * p;
		}

	}
	fin.close();
	matrix x0(a, 2);
	solution x = sym_NM(x0, s,alfa,beta,gama,delta, epsilon, Nmax, O);
	std::cout << x.x(0) << "," << x.x(1) << "," << x.y(0) << "," << solution::f_calls << "," << solution::g_calls << "," << solution::H_calls << std::endl;
	wyn += S;
	cout << "Funkcja celu :" << S << endl;

}

cout << "Koñcowa funkcja celu :" << wyn << endl;
solution::clear_calls();


#endif
		//std::uniform_real_distribution<double> d(-10.0, 10.0);
				//std::minstd_rand0 g(1);
				//for (int i = 0; i < 100; i++) {
				//	double x0_, x1_;
				//	x0_ = d(g);
				//	x1_ = d(g);
				//	double x00[2] = { x0_, x1_ };
				//	matrix x0(x00, 2);
				//	for (int j = 2; j < 3; j++) {
				//		//solution x = SD(x0, h[j], epsilon, Nmax, O);
				//		solution x = CG(x0, h[j], epsilon, Nmax, O);
				//		std::cout << x.x(0) << "," << x.x(1) << "," << x.y(0) << "," << solution::f_calls << "," << solution::g_calls << std::endl;
				//		
				//		//solution x = Newton(x0, h[j], epsilon, Nmax, O);
				//		//
				//		solution::clear_calls();
				//	}
				//}
#elif LAB_NO == 9
#if LAB_PART == 1

		srand(time(NULL));
		double alfa = 1.0, beta = 0.5, gama = 2.0, delta = 0.5, s = 0.5;
		matrix O(2, 2);
		O(0, 0) = -10;
		O(0, 1) = 10;
		O(1, 0) = -10;
		O(1, 1) = 10;
		fstream fin;
		string pom;
		double epsilon = 0.001, R = 8.314, W, sigma, eps, sigma_p, e_dot;
		long double S = 0.0, p, wyn = 0.0;
		double a[7];
		int Nmax = 10000, T;
		double h[3] = { 0,0,0 };
			a[0] = 1 + ((double)(1000 - 1) * rand() / (RAND_MAX));
			a[1] = 0 + ((double)(1 - 0) * rand() / (RAND_MAX));
			a[2] = 0 + ((double)(1 - 0) * rand() / (RAND_MAX));
			a[3] = 1 + ((double)(10000 - 1) * rand() / (RAND_MAX));
			a[4] = 0 + ((double)(1 - 0) * rand() / (RAND_MAX));
			a[5] = 1 + ((double)(90000 - 1) * rand() / (RAND_MAX));
			a[6] = 0 + ((double)(1 - 0) * rand() / (RAND_MAX));
		
			matrix x0(a, 7);
			solution x = HJ(x0,s,alfa ,epsilon, Nmax, O);
			std::cout << x.x(0) << "," << x.x(1) << "," << x.y(0) << "," << solution::f_calls << "," << solution::g_calls << "," << solution::H_calls << std::endl;
			wyn += S;
			cout << "Funkcja celu :" << x.y(0) << endl;

	
		solution::clear_calls();



#elif LAB_PART == 2
		srand(time(NULL));
		double alfa = 1.0, beta = 0.5, gama = 2.0, delta = 0.5, s = 0.5;
		matrix O(2, 2);
		O(0, 0) = -10;
		O(0, 1) = 10;
		O(1, 0) = -10;
		O(1, 1) = 10;
		fstream f;
		fstream plik;
		string pom;
		double epsilon = 0.001,a,b;// Rs = 8.314, R, Z, Sigma, Sigma_p, sigma0, sigmaSS, sigmaSSE, epsi, epsR, epsXS, epsXR, epsC, nsse, a, b, e_dot;
		long double S = 0.0, p, wyn = 0.0;
		double A[15];
		int Nmax = 200, T,Qdef= 312000,j;
		double h[3] = { 0,0,0 };
		f.open("tabA.txt", std::ios::in);
		for (int i = 0; i < 14; i++) {
			if (i == 4)
				A[i] = A[1];
			else if (i == 14)
				A[i] = -1;
			else {
				f >> a;
				f >> b;
				A[i] = a + ((double)(b - a) * rand() / (RAND_MAX));

			}
		}
		f.close();
		//nsse = A[1];
		matrix x0(A, 15);
		solution x = HJ(x0,s, alfa,epsilon,Nmax, O);
	
		solution::clear_calls();
		for (int i = 0; i < 15; i++)
			cout << A[i] << endl;
		//}
		//S /= j;
		//cout << "Koncowy wynik = " << S << endl
		
				std::cout << "Koncowa funkcja =" << x.y(0)   << std::endl;
#elif LAB_PART == 3	
double a[13] = { 0.1 * pow(10,-3),20000,83.349 * pow(10,3),0.05317 * 3 * pow(10,10),123 * pow(10,3),1.973,0,0.452 ,0.13751,0.409,0, 0.000042 * pow(10,13),0.07486 };
double epsilon = 0.001;
int Nmax = 200;
double h0 = 0.1;
		double alfa = 1.0, beta = 0.5, gama = 2.0, delta = 0.5, s = 0.5;
		matrix O(13, 13);
		for (int i = 0; i < 13; i++) {
			for (int j = 0; j < 13; j++) {
				if (i == j)
					O(i, j) = -10;
				else
					O(i, j) = 10;
			}
		}
		O(0, 0) = -10;
		O(0, 1) = 10;
		O(1, 0) = -10;
		O(1, 1) = 10;
		matrix x0(a, 13);
		solution x = Newton(x0,h0,epsilon,Nmax,O);

		solution::clear_calls();
		for (int i = 0; i < 13; i++)
			cout << a[i] << endl;
#endif

#elif LAB_NO == 6

#if LAB_PART == 1
		double epsilon = 0.001;
		int Nmax = 10000;

		matrix O(2, 3);
		O(0, 0) = -10;
		O(0, 1) = 10;
		O(1, 0) = -10;
		O(1, 1) = 10;

		std::uniform_real_distribution<double> d(-10.0, 10.0);
		std::minstd_rand0 g(0);


		for (int i = 0; i <= 100; i++) {
			O(0, 2) = static_cast<double>(i) * 0.01;

			double x0_, x1_;
			x0_ = d(g);
			x1_ = d(g);
			double x00[2] = { x0_, x1_ };
			matrix x0(x00, 2);
			//std::cout << x0_ << "," << x1_ << std::endl;

			solution x = Powell(x0, epsilon, Nmax, O);

			std::cout << x.x(0) << "," << x.x(1) << "," << x.y(0) << "," << x.y(1) << "," << solution::f_calls << std::endl;
			solution::clear_calls();

		}

#else
		double epsilon = 0.0001;
		int Nmax = 1000;

		matrix O(2, 3);
		O(0, 0) = 0.2;
		O(0, 1) = 1.0;
		O(1, 0) = 0.01;
		O(1, 1) = 0.05;

		std::uniform_real_distribution<double> d0(0.2, 1.0);
		std::uniform_real_distribution<double> d1(0.01, 0.05);

		std::minstd_rand0 g(0);

		for (int i = 0; i <= 100; i++) {
			O(0, 2) = static_cast<double>(i) * 0.01;

			double x0_, x1_;
			x0_ = d0(g);
			x1_ = d1(g);
			double x00[2] = { x0_, x1_ };
			matrix x0(x00, 2);

			solution x = Powell(x0, epsilon, Nmax, O);


			std::cout << x0_ * 1e3 << "," << x1_ * 1e3 << ","
				<< x.x(0) * 1e3 << "," << x.x(1) * 1e3 << ","
				<< x.y(0) << "," << x.y(1) * 1e3 << ","
				<< solution::f_calls << std::endl;
			solution::clear_calls();
		}
#endif

#elif LAB_NO==7

#if LAB_PART == 1

		double epsilon = 0.001;
		int Nmax = 10000;
		double sigma[5] = { 0.01,0.1,1.0,10.0,100.0 };
		matrix limits(2, 2);
		limits(0, 0) = -5.0;
		limits(0, 1) = 5.0;
		limits(1, 0) = -5.0;
		limits(1, 1) = 5.0;

		for (int i = 0; i < 5; i++) {
			double x1 = 0.0, x2 = 0.0, y = 0.0;
			int f_calls = 0, n = 0;
			for (int j = 0; j < 100; j++) {
				solution x = EA(2, limits, epsilon, Nmax, matrix(sigma[i]));
				std::cout << x.x(0) << "," << x.x(1) << "," << x.y(0) << "," << solution::f_calls;
				if (x.y(0) < epsilon) {
					std::cout << ",TAK" << std::endl;
					x1 += x.x(0); x2 += x.x(1); y += x.y(0); f_calls += solution::f_calls; n++;
				}
				else {
					std::cout << ",NIE" << std::endl;
				}
				solution::clear_calls();

			}
			std::cout << x1 / n << "," << x2 / n << "," << y / n << "," << f_calls / n << "," << n << std::endl << std::endl;
		}

#else
		double epsilon = 0.001;
		int Nmax = 10000;
		matrix limits(2, 2);
		limits(0, 0) = 0.1;
		limits(0, 1) = 3.0;
		limits(1, 0) = 0.1;
		limits(1, 1) = 3.0;

		solution x = EA(2, limits, epsilon, Nmax, matrix(1.0));
		std::cout << x.x(0) << "," << x.x(1) << "," << x.y(0) << "," << solution::f_calls << std::endl;

		double t0 = 0.0, dt = 0.1, t_end = 100.0;
		matrix Y0(4, 1);
		matrix* Y = solve_ode(t0, dt, t_end, Y0, x.x);
		int* n = get_size(Y[1]);
		for (int i = 0; i < n[0]; i++) {
			std::cout << Y[1](i, 0) << "," << Y[1](i, 2) << std::endl;
		}

#endif
#endif 

		}
	catch (char* EX_INFO)
	{
		std::cout << EX_INFO << std::endl;
	}
	system("pause");
	return 0;
	}
