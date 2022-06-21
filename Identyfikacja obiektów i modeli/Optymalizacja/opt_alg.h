//Do not edit the code below (unless you know what you are doing)

#ifndef OPT_ALG_H
#define OPT_ALG_H

#include"solution.h"
#include<random>
#include<chrono>
#include<cmath>

#if LAB_NO>1
double *expansion(double x0, double d, double alfa, int Nmax, matrix O = 0.0);
solution fib(double a, double b, double epsilon, matrix O = 0.0);
solution lag(double a, double b, double epsilon, double gamma, int Nmax, matrix O = 0.0);
#endif
#if LAB_NO>2
solution HJ(matrix x0, double s, double alfa, double epsilon, int Nmax, matrix O = 0.0);
solution HJ_trial(solution XB, double s, matrix O = 0.0);
solution Rosen(matrix x0, matrix s0, double alfa, double beta, double epsilon, int Nmax, matrix O = 0.0);
#endif
#if LAB_NO>3
solution pen(matrix x0, double c, double dc, double epsilon, int Nmax, matrix O = 0.0);
solution sym_NM(matrix x0, double s, double alfa, double beta, double gama, double delta, double epsilon, int Nmax, matrix O = 0.0);
#endif
#if LAB_NO>4
solution SD(matrix x0, double h0, double epsilon, int Nmax, matrix O = 0.0);
solution CG(matrix x0, double h0, double epsilon, int Nmax, matrix O = 0.0);
solution Newton(matrix x0, double h0, double epsilon, int Nmax, matrix O = 0.0);
solution golden(double a, double b, double epsilon, int Nmax, matrix O = 0.0);
double compute_b(matrix x, matrix d, matrix limits);
#endif
#if LAB_NO>5
solution Powell(matrix x0, double epsilon, int Nmax, matrix O = 0.0);
double *compute_ab(matrix x, matrix d, matrix limits);
#endif
#if LAB_NO>6
solution EA(int N, matrix limits, double epsilon, int Nmax, matrix O = 0.0);
#endif

#endif