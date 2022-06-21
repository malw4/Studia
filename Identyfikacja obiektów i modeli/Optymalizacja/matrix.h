//Do not edit this file (unless you know what you are doing)

#ifndef MATRIX_H
#define MATRIX_H

#include<iostream>
#include<string>
#include<sstream>
using namespace std;

#define SEP_SYMBOL ','

class matrix
{
	int n, m;
	double **M;
	friend matrix operator+(const matrix &, const matrix &); // throw (char*);
	friend matrix operator-(const matrix &, const matrix &); // throw (char*);
	friend matrix operator*(const matrix &, const matrix &); // throw (char*);
	friend matrix operator*(double, const matrix &);
	friend matrix operator/(const matrix &, double);
	friend matrix operator-(const matrix &);
	friend bool operator<(const matrix &, const matrix &); // throw (char*);
	friend bool operator>(const matrix &, const matrix &); // throw (char*);
	friend bool operator<=(const matrix &, const matrix &); // throw (char*);
	friend bool operator>=(const matrix &, const matrix &); // throw (char*);
	friend bool operator==(const matrix &, const matrix &); // throw (char*);
	friend bool operator!=(const matrix &, const matrix &); // throw (char*);
	friend matrix ident_mat(int = 1); // throw (char*);
	friend matrix set_col(const matrix &, matrix, int); // throw (char*);
	friend double det(const matrix &); // throw (char*);
	friend matrix inv(const matrix &); // throw (char*);
	friend matrix trans(const matrix &);
	friend double norm(const matrix &); // throw (char*);
	friend int *get_size(const matrix &);
	friend ostream &operator<<(ostream &, const matrix &);
	friend istream &operator>>(istream &, matrix &); // throw (char*);
public:
	matrix(int = 1, int = 1); // throw (char*);
	matrix(double);
	matrix(double *, int); // throw (char*);
	matrix(double **, int, int); // throw (char*);
	matrix(const matrix &);
	~matrix();
	matrix &operator=(const matrix &);
	matrix operator[](int) const; // throw (char*);
	double &operator()(int, int = 0); // throw (char*);
	double &operator()(int, int = 0) const; // throw (char*);
};

#endif