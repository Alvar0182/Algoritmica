#ifndef DETERMINANTEITER_HPP
#define DETERMINANTEITER_HPP

#include <vector>
#include <random>
#include "funciones.hpp"

using namespace std;

std::vector< std::vector<double> > rellenarMatrizAleatoriamente(int n);
std::vector< std::vector<double> > rellenarMatrizManualmente(int n);
double calcularDeterminanteIter(std::vector< std::vector<double> > &matriz);
void tiemposEjecucionDeterminanteIter(int nMin, int nMax, vector <double> &tiemposReales, vector <double> &numeroElementos);
void ajustePolinomico(const vector <double> &n, const vector <double> &tiemposReales, vector <double> &a);
void calcularTiemposEstimadosPolinomico(const vector <double> &n, const vector <double> &tiemposReales, const vector <double> &a, vector <double> &tiemposEstimados);
double calcularTiempoEstimadoPolinomico(const double &n, const vector <double> &a);
void detIter();

#endif