#include"opt_alg.h"
#include <fstream>
#if LAB_NO>1
double *expansion(double x0, double d, double alfa, int Nmax, matrix O)
{
	double *p = new double[2];
	solution X0(x0), X1(x0 + d);
	X0.fit_fun();
	X1.fit_fun();
	if (X0.y == X1.y)
	{
		p[0] = X0.x(0);
		p[1] = X1.x(0);
		return p;
	}
	if (X0.y <= X1.y)
	{
		d *= -1;
		X1.x = X0.x + d;
		X1.fit_fun();
		if (X1.y >= X0.y)
		{
			p[0] = X1.x(0);
			p[1] = X0.x(0) - d;
			return p;
		}
	}
	solution X2;
	int i = 1;
	while (true)
	{
		X2.x = x0 + pow(alfa, i) * d;

		X2.fit_fun();
		if (X2.y >= X1.y || solution::f_calls > Nmax) {
			break;
		}


		X0 = X1;
		X1 = X2;
		++i;
	}
	if (d > 0) {
		p[0] = X0.x(0);
		p[1] = X2.x(0);
	}
	else {
		p[0] = X2.x(0);
		p[1] = X0.x(0);
	}


	return p;
}

solution fib(double a, double b, double epsilon, matrix O)
{
	//liczy n dla fibonnaciego (b-a)/epsilon
	int n = ceil(log((b - a) / epsilon * sqrt(5) + 0.5) / log((1 + sqrt(5)) / 2));

	int *F = new int[n] {1, 1};

	for (int i = 2; i < n; ++i)
		F[i] = F[i - 2] + F[i - 1];

	solution A(a), B(b), C, D;
	C.x(0) = B.x(0) - F[n - 2] * (B.x(0) - A.x(0)) / F[n - 1];

	D.x = A.x + B.x - C.x;
	C.fit_fun();
	D.fit_fun();


	for (int i = 2; i <= n - 3; ++i)
	{
		//wypisywanie dlugosci przedzialu
		//cout << B.x(0) - A.x(0) << endl;

		if (C.y < D.y)
		{
			B = D;
		}
		else
		{
			A = C;
		}


		C.x(0) = B.x(0) - F[n - i - 2] * (B.x(0) - A.x(0)) / F[n - i - 1];
		D.x(0) = A.x(0) + B.x(0) - C.x(0);
		C.fit_fun();
		D.fit_fun();
	}
	return C;
}

solution lag(double a, double b, double epsilon, double gamma, int Nmax, matrix O)
{
	solution A(a), B(b), C, D;
	C.x = (A.x + B.x) / 2;
	A.fit_fun();
	B.fit_fun();
	C.fit_fun();
	double l, m;
	int i = 0;

	//cout << B.x(0) - A.x(0) << endl;
	while (true)
	{
		l = A.y(0) * (pow(B.x(0), 2) - pow(C.x(0), 2)) + B.y(0) * (pow(C.x(0), 2) - pow(A.x(0), 2)) + C.y(0) * (pow(A.x(0), 2) - pow(B.x(0), 2));
		m = A.y(0) * (B.x(0) - C.x(0)) + B.y(0) * (C.x(0) - A.x(0)) + C.y(0) * (A.x(0) - B.x(0));
		if (m <= 0)
		{
			C.x = NAN;
			C.y = NAN;
			return C;
		}
		D.x = 0.5 * (l / m);
		D.fit_fun();
		if (A.x(0) < D.x(0) && D.x(0) < C.x(0))
		{
			if (C.y(0) > D.y(0))
			{
				B = C;
				C = D;
			}
			else
				A = D;
		}
		else if (C.x(0) < D.x(0) && D.x(0) < B.x(0))
		{
			if (D.y(0) < C.y(0))
			{
				A = C;
				C = D;
			}
			else
				B = D;
		}
		else
		{
			C.x = NAN;
			C.y = NAN;
			return C;
		}
		i++;
		//cout << B.x(0) - A.x(0) << endl;
		if (fabs(C.x(0) - D.x(0)) < gamma || solution::f_calls >= Nmax || B.x(0) - A.x(0) < gamma)
			return C;
	}
}
#endif
#if LAB_NO>2
solution HJ(matrix x0, double s, double alfa, double epsilon, int Nmax, matrix O)
{
	fstream plik;
	plik.open("wynikifunkcji.txt", std::ios::out);
	solution XB, XB_old, X;
	XB.x = x0;
	XB.y(0)=1;
	while (true)
	{
		//cout << XB.x(0, 0) << ";" << XB.x(1, 0) << endl;
		cout << "jestem tu" << endl;
		X = HJ_trial(XB, s);
		cout << "teraz tu" << endl;
		X.fit_fun();
		cout << X.y(0) << "    " << XB.y(0) << endl;
		if (X.y(0) < XB.y(0))
		{
			while (true)
			{
				XB_old = XB;
				XB = X;
				X.x = 2 * XB.x - XB_old.x;
				X.fit_fun();
				X = HJ_trial(X, s);
				if (X.y(0) >= XB.y(0)) {

					cout << X.y(0) << ";" << XB.y(0) << endl;
					return XB;
				}
				else {
					if (solution::f_calls > Nmax)
						break;
					cout << XB.y(0) << ";" << s<< endl;
					plik << XB.y(0)<<endl;
					//break;
					//
				}
			}
		}
		else {
			s *= alfa;
		}

		if (s < epsilon || solution::f_calls > Nmax) {
			cout << XB.y(0) << ";" << XB.x(1, 0) << endl;
			return XB;
		}
	}
}

solution HJ_trial(solution XB, double s, matrix O)
{
	int *n = get_size(XB.x);
	//matrix D = ident_mat(n[0]);
	solution X;
	for (int i = 0; i < n[0]; ++i)
	{
		cout << "W trialu " << i << endl;
		X.x = XB.x;
		X.x(i) += s;
		X.fit_fun();
		if (X.y(0) < XB.y(0)){
			XB = X;
		}
		else
		{
			X.x = XB.x;
			X.x(i) -= s;
			X.fit_fun();
			if (X.y(0) < XB.y(0)) {
				XB = X;
			}
		}
	}
	return XB;
}


solution Rosen(matrix x0, matrix s0, double alfa, double beta, double epsilon, int Nmax, matrix O)
{
	int *n = get_size(x0);
	matrix l(n[0], 1), p(n[0], 1), s(s0);
	matrix D(n[0], n[0]);
	for (int i = 0; i < n[0]; i++) {
		D(i, i) = 1;
	}
	solution X, Xt;
	X.x = x0 ;
	X.fit_fun();
	int it = 0;
	while (true)
	{
		//cout << X.x(0, 0) << ";" << X.x(1, 0) << endl;

		for (int i = 0; i < n[0]; ++i)
		{
			Xt.x = X.x + s(i) * D[i];
			Xt.fit_fun();
			if (Xt.y(0)<X.y(0))
			{
				X = Xt;
				l(i) += l(i) + s(i);
				s(i) *= alfa;
			}
			else
			{
				p(i) = p(i) + 1;
				s(i) *= -beta;
			}
		}
		++it;
		bool change = true;
		for (int i = 0; i < n[0]; ++i)
			if (fabs(l(i)) < 10e-50 || static_cast<int>(p(i)) == 0)
			{
				change = false;
				break;
			}
		if (change)
		{
			matrix Q(n[0], n[0]), v(n[0], 1);
			for (int i = 0; i < n[0]; ++i)
				for (int j = 0; j <= i; ++j)
					Q(i, j) = l(i);
			Q = D * Q;
			v = Q[0];
			D = set_col(D, v, 0);
			for (int i = 1; i < n[0]; ++i)
			{
				matrix temp(n[0], 1);
				for (int j = 0; j < i; ++j)
					temp = trans(Q[i]) * D[j] * D[j];
				v = Q[i] - temp;
				D = set_col(D, v, i);
			}
			s = s0;
			l = matrix(n[0], 1);
			p = matrix(n[0], 1);
		}
		double max_s = abs(s(0));
		for (int i = 1; i < n[0]; ++i)
			if (max_s < abs(s(i)))
				max_s = abs(s(i));
		if (max_s < epsilon || it > Nmax) {
			//cout << X.x(0, 0) << ";" << X.x(1, 0) << endl;
			return X;
		}
	}
}
#endif
#if LAB_NO>3
solution pen(matrix x0, double c0, double dc, double epsilon, int Nmax, matrix O)
{
	double alfa = 1, beta = 0.5, gama = 2, delta = 0.5, s = 0.5;
	matrix A(new double[2]{ c0,O(0) }, 2);
	solution X, X1;
	X.x = x0;
	while (true)
	{
		X1 = sym_NM(X.x, s, alfa, beta, gama, delta, epsilon, Nmax, A);
		double d = norm(X1.x - X.x);
		//std::cout << d << std::endl;
		if (d < epsilon)
			return X1;
		A(0) *= dc;
		X = X1;
	}
}

solution sym_NM(matrix x0, double s, double alfa, double beta, double gama, double delta, double epsilon, int Nmax, matrix O)
{
	int po = 0;
	int *n = get_size(x0);
	//matrix D = ident_mat(n[0]);
	matrix D(n[0], n[0]);
	for (int i = 0; i < n[0]; i++) {
		D(i, i) = 1;
	}
	int N = n[0] + 1;
	solution *S = new solution[N];
	S[0].x = x0;
	S[0].fit_fun(O);
	for (int i = 1; i < N; ++i)
	{
		S[i].x = x0 + D[i - 1] * s;
		S[i].fit_fun(O);
	}
	solution p_o, p_e, p_z;
	matrix p_sr;
	int i_min, i_max;
	while (true)
	{
		i_min = i_max = 0;
		for (int i = 1; i < N; ++i)
		{
			if (S[i].y(0) < S[i_min].y(0))
				i_min = i;
			if (S[i].y(0) > S[i_max].y(0))
				i_max = i;
		}
		p_sr = matrix(n[0], 1);
		for (int i = 0; i < N; ++i) {
			if (i != i_max)
				p_sr = p_sr + S[i].x;
		}


		p_sr = p_sr / n[0];
		p_o.x = p_sr + alfa * (p_sr - S[i_max].x);
		p_o.fit_fun(O);
		if (S[i_min].y(0) <= p_o.y(0) < S[i_max].y(0))
			S[i_max] = p_o;
		else if (p_o.y(0) < S[i_min].y(0))
		{
			p_e.x = p_sr + gama * (p_o.x - p_sr);
			p_e.fit_fun(O);
			if (p_e.y(0) < p_o.y(0))
				S[i_max] = p_e;
			else
				S[i_max] = p_o;
		}
		else
		{
			p_z.x = p_sr + beta * (S[i_max].x - p_sr);
			p_z.fit_fun(O);
			if (p_z.y(0) < S[i_max].y(0))
				S[i_max] = p_z;
			else
			{
				for (int i = 0; i < N; ++i) {
					if (i != i_min)
					{
						S[i].x = delta * (S[i].x + S[i_min].x);
						S[i].fit_fun(O);
					}
				}
			}
		}
		double max_s = norm(S[0].x - S[i_min].x);
		for (int i = 1; i < N; ++i) {
			if (max_s < norm(S[i].x - S[i_min].x))
				max_s = norm(S[i].x - S[i_min].x);
		}
		if (solution::f_calls > Nmax || max_s < epsilon)
			return S[i_min];

	}
}
#endif
#if LAB_NO>4
solution SD(matrix x0, double h0, double epsilon, int Nmax, matrix O)
{
	int *n = get_size(x0);
	solution X, X1;
	X.x = x0;
	matrix d(n[0], 1), P(n[0], 2), limits = O;
	solution h;
	double b;
	while (true)
	{
		X.grad();
		d = -X.g;
		P = set_col(P, X.x, 0);
		P = set_col(P, d, 1);
		if (h0 < 0)
		{
			b = compute_b(X.x, d, limits);
			h = golden(0.0, b, epsilon, Nmax, P);
			X1.x = X.x + d * h.x(0);
		}
		else
			X1.x = X.x + d * h0;

		//std::cout << X1.x(0) << "," << X1.x(1) << std::endl;;

		if (norm(X1.x - X.x) < epsilon ||
			solution::f_calls > Nmax ||
			solution::g_calls > Nmax)
		{
			X1.fit_fun();
			return X1;
		}
		X = X1;
	}
}

solution CG(matrix x0, double h0, double epsilon, int Nmax, matrix O)
{
	int *n = get_size(x0);
	solution X, X1;
	X.x = x0;
	matrix d(n[0], 1), P(n[0], 2), limits = O;
	solution h;
	double b, beta;
	X.grad();
	d = -X.g;
	while (true)
	{
		P = set_col(P, X.x, 0);
		P = set_col(P, d, 1);
		if (h0 < 0)
		{
			b = compute_b(X.x, d, limits);
			h = golden(0.0, b, epsilon, Nmax, P);
			X1.x = X.x + d * h.x(0);
		}
		else
			X1.x = X.x + d * h0;

		//std::cout << X1.x(0) << "," << X1.x(1) << std::endl;;

		if (norm(X1.x - X.x) < epsilon ||
			solution::f_calls > Nmax ||
			solution::g_calls > Nmax)
		{
			X1.fit_fun();
			return X1;
		}
		X1.grad();
		beta = pow(norm(X1.g), 2.0) / pow(norm(X.g), 2.0);
		d = -X1.g + d * beta;
		X = X1;
	}
}

solution Newton(matrix x0, double h0, double epsilon, int Nmax, matrix O){
	int *n = get_size(x0);
	solution X, X1;
	X.x = x0;
	int i = 0;
	matrix d(n[0], 1), P(n[0], 2), limits = O;
	solution h;
	double b;
	while (true){
		X.grad();
		X.hess();
		//d = -inv(X.H)*X.g;
		P = set_col(P, X.x, 0);
		P = set_col(P, d, 1);
		if (h0 < 0)
		{
			b = compute_b(X.x, d, limits);
			h = golden(0, b, epsilon, Nmax, P);
			X1.x = X.x + h.x * d;
		}
		else
			X1.x = X.x + h0 * d;
		//std::cout << X1.x(0) << "," << X1.x(1) << std::endl;;

		if (norm(X1.x - X.x) < epsilon || solution::f_calls > Nmax ||
			  solution::g_calls > Nmax || solution::H_calls > Nmax){
			X1.fit_fun();
			cout << X1.y << endl;
			return X1;
		}
		X = X1;
	}
}

solution golden(double a, double b, double epsilon, int Nmax, matrix O)
{
	double alfa = 0.5*(sqrt(5.0) - 1.0);
	solution A, B, C, D;
	A.x = a;
	B.x = b;
	C.x = b - alfa*(b - a);
	C.fit_fun(O);
	D.x = a + alfa*(b - a);
	D.fit_fun(O);
	while (true)
	{
		if (C.y(0) < D.y(0))
		{
			B = D;
			D = C;
			C.x = B.x - alfa * (B.x - A.x);
			C.fit_fun(O);
		}
		else
		{
			A = C;
			C = D;
			D.x = A.x + alfa * (B.x - A.x);
			D.fit_fun(O);
		}
		if (B.x - A.x < epsilon || solution::f_calls > Nmax)
		{
			A.x = (A.x + B.x) / 2.0;
			A.fit_fun(O);
			return A;
		}
	}
}

double compute_b(matrix x, matrix d, matrix limits)
{
	int *n = get_size(x);
	double b = 1e9, bi;
	for (int i = 0; i < n[0]; ++i)
	{
		if (d(i) == 0)
			bi = 1e9;
		else if (d(i) > 0)
			bi = (limits(i, 1) - x(i)) / d(i);
		else
			bi = (limits(i, 0) - x(i)) / d(i);
			if (b > bi)
				b = bi;
	}
	return b;
}
#endif
#if LAB_NO>5
solution Powell(matrix x0, double epsilon, int Nmax, matrix O)
{
	int *n = get_size(x0);
	matrix D(n[0], n[0]), A(n[0], 3), limits(n[0], 2);
	for (int i = 0; i < n[0]; i++) {
		D(i, i) = 1;
	}
	limits = set_col(limits, O[0], 0);
	limits = set_col(limits, O[1], 1);
	A(0, 2) = O(0, 2);
	solution X, P, h;
	X.x = x0;
	double *ab;
	while (true)
	{
		P = X;
		for (int i = 0; i < n[0]; ++i)
		{
			A = set_col(A, P.x, 0);
			A = set_col(A, D[i], 1);
			ab = compute_ab(P.x, D[i], limits);
			h = golden(ab[0], ab[1], epsilon, Nmax, A);
			P.x = P.x + h.x(0) * D[i];
		}
		if (solution::f_calls > Nmax || norm(P.x - X.x) < epsilon)
		{
			P.fit_fun();
			return P;
		}
		for (int i = 0; i < n[0] - 1; ++i)
			D[i] = D[i+1];
		D[n[0] - 1] = P.x - X.x;
		A = set_col(A, P.x, 0);
		A = set_col(A, D[n[0] - 1], 1);
		ab = compute_ab(P.x, D[n[0] - 1], limits);
		h = golden(ab[0], ab[1], epsilon, Nmax, A);
		X.x = P.x + h.x(0) * D[n[0] - 1];
	}
}

double *compute_ab(matrix x, matrix d, matrix limits)
{
	int *n = get_size(x);
	double *ab = new double[2]{ -1e9,1e9 };
	double ai, bi;
	for (int i = 0; i < n[0]; ++i)
	{
		if (d(i) == 0)
		{
			ai = -1e9;
			bi = 1e9;
		}
		else if (d(i) > 0)
		{
			ai = (limits(i, 0) - x(i)) / d(i);
			bi = (limits(i, 1) - x(i)) / d(i);
		}
		else
		{
			ai = (limits(i, 1) - x(i)) / d(i);
			bi = (limits(i, 0) - x(i)) / d(i);
		}
		if (ab[0] < ai)
			ab[0] = ai;
		if (ab[1] > bi)
			ab[1] = bi;
	}
	return ab;
}
#endif
#if LAB_NO>6
solution EA(int N, matrix limits, double epsilon, int Nmax, matrix O)
{
	int mi = 20, lambda = 40;
	solution *P = new solution[mi + lambda];
	solution *Pm = new solution[mi];
	random_device rd;
	default_random_engine gen;
	gen.seed(static_cast<unsigned int>(chrono::system_clock::now().time_since_epoch().count()));
	normal_distribution<double> distr(0.0, 1.0);
	uniform_real_distribution<double> distr_u(0.0, 1.0);
	matrix IFF(mi, 1), temp(N, 2);
	double r, s, s_IFF;
	double tau = 1.0 / sqrt(2.0*N), tau1 = 1 / sqrt(2.0*sqrt(N));
	int j_min;
	for (int i = 0; i < mi; ++i)
	{
		P[i].x = matrix(N, 2);
		for (int j = 0; j < N; ++j)
		{
			P[i].x(j, 0) = (limits(j, 1) - limits(j, 0))*distr_u(gen) + limits(j, 0);
			P[i].x(j, 1) = O(0, 0);
		}
		P[i].fit_fun();
		if (P[i].y < epsilon)
			return P[i];
	}
	while (true)
	{
		s_IFF = 0;
		for (int i = 0; i < mi; ++i)
		{
			IFF(i) = 1 / P[i].y(0);
			s_IFF += IFF(i);
		}
		for (int i = 0; i < lambda; ++i)
		{
			r = distr_u(gen)*s_IFF;
			s = 0;
			for (int j = 0; j < mi; ++j)
			{
				s += IFF(j);
				if (s >= r)
				{
					P[mi + i] = P[j];
					break;
				}
			}
		}
		for (int i = 0; i < lambda; ++i)
		{
			r = distr(gen);
			for (int j = 0; j < N; ++j)
			{
				P[mi + i].x(j, 1) *= exp(tau1 * r + tau * distr(gen));
				P[mi + i].x(j, 0) += P[mi + i].x(j, 1) * distr(gen);
			}
		}
		for (int i = 0; i < lambda; i += 2)
		{
			r = distr_u(gen);
			temp = P[mi + i].x;
			P[mi + i].x = r * temp + (1.0 - r)*P[mi + i + 1].x;
			P[mi + i + 1].x = r * P[mi + i + 1].x + (1.0 - r)*temp;
		}
		for (int i = 0; i < lambda; ++i)
		{
			P[mi + i].fit_fun();
			if (P[mi + i].y < epsilon)
				return P[mi + i];
		}
		for (int i = 0; i < mi; ++i)
		{
			j_min = 0;
			for (int j = 1; j < mi + lambda; ++j)
				if (P[j_min].y > P[j].y)
					j_min = j;
			Pm[i] = P[j_min];
			P[j_min].y = 1e10;
		}
		for (int i = 0; i < mi; ++i)
			P[i] = Pm[i];
		if (solution::f_calls > Nmax)
			return P[0];
	}
}
#endif
