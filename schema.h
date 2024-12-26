#ifndef SCHEMA_H
#define SCHEMA_H
#include <vector>
#include "qmath.h"

using std::vector;

double k_main(double x, double xi);
double q_main(double x, double xi);
double f_main(double x, double xi);
double k_test(double x, double xi);
double q_test(double x, double xi);
double f_test(double x, double xi);
vector<double> solveMatrix(vector<double> A, vector<double>& C, vector<double> B, vector<double> Fi, double mu1, double mu2, int n);
vector<double> calc_true_sol(double levGran, double pravGran, double xi, double n);

class Scheme {
public:
    double mu1;
    double mu2;
    double xi;
    double levGran;
    double pravGran;
    vector<double> x;
    vector<double> v;
    vector<double> v2;
    vector<double> diff;
    Scheme(double mu1 = 1.0, double mu2 = 1.0, double xi = (M_PI / 4.0), double a = 0.0, double b = 1.0) :mu1(mu1), mu2(mu2), xi(xi), levGran(a), pravGran(b) {}

    void calculate_test(int n);
    void calculate_main(int n);
};

#endif // SCHEMA_H
