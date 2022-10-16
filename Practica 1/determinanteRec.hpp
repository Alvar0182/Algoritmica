#ifndef DETERMINANTEREC_HPP
#define DETERMINANTEREC_HPP

#include "funciones.hpp"
#include "determinanteIter.hpp"

double calcularDeterminanteRec(const std::vector< std::vector<double> > &matriz);
void tiemposEjecucionDeterminanteRec(int nMin, int nMax, vector <double> &tiemposReales, vector <double> &numeroElementos);
int factorial(int n);
void ajusteFactorial(const vector <double> &n, const vector <double> &tiemposReales, vector <double> &a);
void calcularTiemposEstimadosFactorial(const vector <double> &n, const vector <double> &tiemposReales, const vector <double> &a, vector <double> &tiemposEstimados);
double calcularTiempoEstimadoFactorial(const double &n, const vector <double> &a);
void detRec();

#endif