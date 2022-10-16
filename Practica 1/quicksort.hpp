#ifndef QUICKSORT_HPP
#define QUICKSORT_HPP

#include <vector>
#include <algorithm>
#include <math.h>
#include <bits/stdc++.h>
#include "funciones.hpp"

using namespace std;

void rellenarVector(vector <int> &v, int nEle);
bool estaOrdenado(const vector <int> &v);
void tiemposOrdenacionQuicksort(int nMin, int nMax, int repeticiones, vector <double> &tiemposReales, vector <double> &numeroElementos);
void ajusteNlogN(const vector <double> &numeroElementos, const vector <double> &tiemposReales, vector <double> &a);
void calcularTiemposEstimadosNlogN(const vector <double> &numeroElementos, const vector <double> &a, vector <double> &tiemposEstimados);
double calcularTiempoEstimadoNlogN(const double &n, vector <double> &a);
void quicksort();

#endif