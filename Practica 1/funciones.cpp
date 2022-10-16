#include "funciones.hpp"

using namespace std;

void escribirFichero(vector <double> &tiemposReales, vector <double> &numeroElementos){
    ofstream fichero("tiempoReales.txt");
    for(int i=0;tiemposReales.size()>i;i++){
        fichero<<numeroElementos[i]<<" "<<tiemposReales[i]<<endl;
    }
    fichero.close();
}

double sumatorio(const vector <double> &n, const vector <double> &t, int expN, int expT){
    /*
    Sumatorio de n: sumatorio(n,t,1,0);
    Sumatorio de n^2: sumatorio(n,t,2,0);
    Sumatorio de t: sumatorio(n,t,0,1);
    Sumatorio de n^z: sumatorio(n,t,z,0);
    Sumatorio de n*t: sumatorio(n,t,1,1);
    */
    double suma = 0.0;
    for(int i=0; n.size()>i;i++){
        double sumaN = pow(n[i], expN);
        double sumaT = pow(t[i], expT);
        suma = suma + sumaN * sumaT;
    }
    return suma;
}

double calcularCoeficienteDeterminacion(const vector <double> &tiemposReales, const vector <double> &tiemposEstimados){
    double varianzaReal=0.0; 
    double varianzaEstimada=0.0;
    double mediaReal=0.0;
    double mediaEstimada=0.0;
    mediaReal=media(tiemposReales);
    mediaEstimada=media(tiemposEstimados);
    varianzaReal=varianza(tiemposReales, mediaReal);
    varianzaEstimada=varianza(tiemposEstimados, mediaEstimada);
    double CoeficienteDeterminacion = varianzaEstimada/varianzaReal;
    return CoeficienteDeterminacion;
}

double varianza(std::vector<double> vector, double media){
    double varianza=0.0;
    for(int i=0;vector.size()>i; i++){
        varianza= varianza + pow((vector[i]-media),2);
    }
    varianza= varianza / vector.size();
    return varianza;
}

double media(std::vector<double> vector){
    double media=0.0;
    for(int i=0;vector.size()>i; i++){
        media= media + vector[i];
    }
    media = media / vector.size();
    return media;
}

void escribirFicheroFinal(vector <double> &tiemposReales, vector <double> &numeroElementos, vector <double> &tiemposEstimados){
    ofstream fichero("datosFinales.txt");
    for(int i=0; i< tiemposReales.size(); i++){
        fichero<<numeroElementos[i]<<" "<<tiemposReales[i]<<" "<< tiemposEstimados[i]<<endl;
    }
    fichero.close();
}

void tiempo(int totalSegundos,int &anos, int &dias, int &horas, int &minutos, int &segundos){
    horas=totalSegundos/3600;
    totalSegundos = totalSegundos%3600;
    minutos = totalSegundos/60;
    segundos = totalSegundos%60;
    dias=totalSegundos/86400;
    anos=totalSegundos/31536000;
}