//Do not edit the code below (unless you know what you are doing)

#define _USE_MATH_DEFINES
#include <cmath>

#include"ode_solver.h"

matrix* solve_ode(double t0, double dt, double tend, const matrix& Y0, matrix P)
{
	int N = static_cast<int>(floor((tend - t0) / dt) + 1);
	if (N < 2)
		throw "The time interval is defined incorrectly";
	int* s = get_size(Y0);
	if (s[1] != 1)
		throw "Initial condition must be a vector";
	int n = s[0];
	delete[]s;
	matrix* S = new matrix[2]{ matrix(N), matrix(n,N) };
	S[0](0) = t0;
	for (int i = 0; i < n; ++i)
		S[1](i, 0) = Y0(i);
	matrix k1(n), k2(n), k3(n), k4(n);
	for (int i = 1; i < N; ++i)
	{
		S[0](i) = S[0](i - 1) + dt;
		k1 = dt * diff(S[0](i - 1), S[1][i - 1], P);
		k2 = dt * diff(S[0](i - 1) + 0.5 * dt, S[1][i - 1] + 0.5 * k1, P);
		k3 = dt * diff(S[0](i - 1) + 0.5 * dt, S[1][i - 1] + 0.5 * k2, P);
		k4 = dt * diff(S[0](i - 1) + dt, S[1][i - 1] + k3, P);
		for (int j = 0; j < n; ++j)
			S[1](j, i) = S[1](j, i - 1) + (k1(j) + 2 * k2(j) + 2 * k3(j) + k4(j)) / 6;
	}
	S[1] = trans(S[1]);
	return S;
}

//You can edit the following code

matrix diff(double t, const matrix& Y, matrix P)
{
#if LAB_NO == 1

	double m = 5, b = 1.5, k = 1, F = 0.5;
	matrix dY(Y);
	dY(0) = Y(1);
	dY(1) = (F - b * Y(1) - b * Y(0)) / m;
	return dY;



#elif LAB_NO == 2

	double
		a = 0.98, b = 0.63, g = 9.81,
		PA = 1, TA = 90, DA = P(0),
		PB = 1, DB = 36.5665e-4,
		Tin = 10, Fin = 0.01;

	matrix dY(Y);

	double FAout, FBout;

	FAout = Y(0) <= 0 ? 0 : a * b * DA * sqrt(2 * g * Y(0) / PA);
	FBout = Y(1) <= 0 ? 0 : a * b * DB * sqrt(2 * g * Y(1) / PB);
	dY(0) = -FAout;
	dY(1) = FAout + Fin - FBout;
	dY(2) = FAout * (TA - Y(2)) / Y(1) + Fin * (Tin - Y(2)) / Y(1);
	return dY;

#elif LAB_NO == 3
#if LAB_PART == 2
	double mr = 1.0, mc = 10.0,
		l = 0.5, b = 0.5,
		alfa_ref = M_PI, omega_ref = 0,
		I = mc * pow(l, 2) + mr * pow(l, 2) / 3.0;
	matrix dY(2, 1);
	dY(0) = Y(1);
	dY(1) = (P(0)*(alfa_ref - Y(0)) + P(1)*(omega_ref - Y(1)) - b * Y(1)) / I;
	return dY;
#else
	matrix dY;
	return dY;
#endif

#elif LAB_NO == 4

#if LAB_PART == 2

	double m = 0.6, r = 0.12, ro = 1.2, g = 9.81, C = 0.47;
	double S = M_PI * r*r;
	double Dx = 0.5*C*ro*S*Y(1)*fabs(Y(1));
	double Dy = 0.5*C*ro*S*Y(3)*fabs(Y(3));
	double Fmx = M_PI * ro*Y(3)*P(0)*pow(r, 3);
	double Fmy = M_PI * ro*Y(1)*P(0)*pow(r, 3);

	matrix dY(4, 1);
	dY(0) = Y(1);
	dY(1) = (-Dx - Fmx) / m;
	dY(2) = Y(3);
	dY(3) = (-m * g - Dy - Fmy) / m;

	return dY;

#else 
	matrix dY;
	return dY;
#endif
#elif LAB_NO == 7
#if LAB_PART == 2
	
	double m1 = 5.0, m2 = 5.0, k1 = 1.0, k2 = 1.0, F = 1.0;
	double b1 = P(0), b2 = P(1);
	matrix dY(4, 1);
	dY(0) = Y(1);
	dY(1) = (-b1 * Y(1) - b2 * (Y(1) - Y(3)) - k1 * Y(0) - k2 * (Y(0) - Y(2))) / m1;
	dY(2) = Y(3);
	dY(3) = (F + b2 * (Y(1) - Y(3)) + k2 * (Y(0) - Y(2))) / m2;
	return dY;
#else
	matrix dY;
	return dY;
#endif
#else
	matrix dY;
	return dY;
#endif
}
