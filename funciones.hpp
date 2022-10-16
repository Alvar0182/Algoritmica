#ifndef FUNCIONES_HPP
#define FUNCIONES_HPP

#include <vector>
#include <iostream>
#include <fstream>
#include <math.h>
#include "ClaseTiempo.cpp"
#include "sistemaEcuaciones.hpp"

using namespace std;

void escribirFichero(vector <double> &tiemposReales, vector <double> &numeroElementos);
double sumatorio(const vector <double> &n, const vector <double> &t, int expN, int expT);
double calcularCoeficienteDeterminacion(const vector <double> &tiemposReales, const vector <double> &tiemposEstimados);
double varianza(std::vector<double> vector, double media);
double media(std::vector<double> vector);
void escribirFicheroFinal(vector <double> &tiemposReales, vector <double> &numeroElementos, vector <double> &tiemposEstimados);
void tiempo(int totalSegundos,int &anos, int &dias, int &horas, int &minutos, int &segundos);

#endif