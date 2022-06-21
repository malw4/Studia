//Do not edit this file (unless you know what you are doing)

#ifndef ODE_SOLVER_H
#define ODE_SOLVER_H

#include"matrix.h"
#include"lab_no.h"

matrix *solve_ode(double, double, double, const matrix &, matrix = 0.0); // throw (char*);
matrix diff(double, const matrix &, matrix = 0.0);

#endif