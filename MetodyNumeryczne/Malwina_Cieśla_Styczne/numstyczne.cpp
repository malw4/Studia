#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

double changeX(double x) {
	double f = pow(x,2)+2*x-1;
	return f;
}

double pochodna(double x, double f) {
	double fi = 2*x+2;
	double pkt = x - (f / fi);
	return pkt;
}

void styczna(double p, double eps) {
	double*x = new double[1000];
	double*f = new double[1000];
	x[0] = p;
	f[0] = changeX(x[0]);
	for (int i = 0; abs(f[i]) > eps;i++) {
		x[i + 1] = pochodna(x[i], f[i]);
		f[i + 1] = changeX(x[i + 1]);
		cout << "Krok:  " << i+1 << endl;
		cout << "Wartosc przyblizenia dla punktu: " << x[i+1] << " wynosi " << f[i+1] << endl;
	}

 }

void sieczna(double p,double eps) {
	double*x = new double[1000];
	double*f=new double [1000];
	int i = 1; 
	x[0] = p;
	f[0] = changeX(x[0]);
	x[1] = 0.5;
	f[1] = changeX(x[1]);
	cout << "Krok:  " << i << endl;
	cout << "Wartosc przyblizenia dla punktu: "<< x[1] << " wynosi "<< f[1]<<endl;
	while(abs(f[i])>eps){
		cout << "Krok:  " << i+1 <<endl;
		x[i + 1] = (x[i] - x[i - 1]) * f[i] / (f[i] - f[ i- 1]);
		f[i + 1] = changeX(x[i + 1]);
		cout << "Wartosc przyblizenia dla punktu: " << x[i+1] << " wynosi " << f[i+1] << endl;
		i++;
	}
	cout << "Wykonano " << i << " krokow " << endl;
}


int main() {
	double eps,x;
	cout << "Podaj w jakim punkcie chcesz zaczac: " << endl;
	cin >> x;
	cout << "Podaj wymagana dokladnosc: " << endl;
	cin >> eps;
	styczna(x, eps);
	cout << endl <<endl;
	sieczna(x, eps);
	system("PAUSE");
	return 0;
}

