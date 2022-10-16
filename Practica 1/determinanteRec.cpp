#include "determinanteRec.hpp"

using namespace std;

double calcularDeterminanteRec(const std::vector< std::vector<double> > &matriz) {
    int orden = matriz.size();
    double det = 0, aux = 0;
    int c;

    // Caso base del determinante
    if (orden == 2) {
        return matriz[0][0]*matriz[1][1] - matriz[1][0]*matriz[0][1];
    }

    // Caso general
    for (int j = 0; j < orden; j++) {
        std::vector< std::vector<double> > menor(orden-1, std::vector<double>(orden-1));

        for (int k = 1; k < orden; k++) {
            c = 0;
            for (int l = 0; l < orden; l++) {
                if (l != j) {
                    menor[k-1][c] = matriz[k][l];
                    c++;
                }
            }
        }
        // Llamada recursiva al determinante del menor
        aux = pow(-1, 2+j) * matriz[0][j] * calcularDeterminanteRec(menor);
        det += aux;
    }
    return det;
} // determinante

void tiemposEjecucionDeterminanteRec(int nMin, int nMax, vector <double> &tiemposReales, vector <double> &numeroElementos){
    int inc;
    int opcion;
    double media;
    Clock tiempo;
    std::cout<<"Introduzca el incremento de n"<<std::endl;
    std::cin>>inc;
    std::cout<<"Introduzca 1 si quiere rellenar la matriz con valores aleatorios en el rango [0.95,1.05] o 2 si desea rellenarla manualmente"<<std::endl;
    std::cin>>opcion;
    for(int i=nMin;nMax>=nMin;nMin=nMin+inc){
        std::vector< std::vector<double> > matriz;
        if(opcion==1){
            matriz=rellenarMatrizAleatoriamente(nMin);
        }
        else if(opcion==2){
            matriz=rellenarMatrizManualmente(nMin);
        }
        else{
            cout<<"Introduzca 1 o 2"<<endl;
            exit(-1);
        }
        tiempo.restart();
        calcularDeterminanteRec(matriz);
        if(tiempo.isStarted()){
            tiempo.stop();
        }
        media = tiempo.elapsed();
        tiemposReales.push_back(media);
        numeroElementos.push_back(nMin);
    }
}

int factorial(int n){
    int fact=1;
    while(n!=0){
        fact = fact*n;
        n--;
    }
    return fact;
}

void ajusteFactorial(const vector <double> &n, const vector <double> &tiemposReales, vector <double> &a){
    double sumatorioT=sumatorio(n,tiemposReales,0,1);
    double sumatorioN=sumatorio(n,tiemposReales,1,0);
    vector <double> z;
    for(int i=0;n.size()>i;i++){
        double num=factorial(n[i]);
        z.push_back(num);
    }
    double sumatorioZ=sumatorio(z,tiemposReales,1,0);
    double sumatorioZCuadrado=sumatorio(z,tiemposReales,2,0);
    double sumatorioZT=sumatorio(z,tiemposReales,1,1);

    std::vector< std::vector<double> > matrizA (2, std::vector <double>(2) );
    matrizA[0][0]=n.size();
    matrizA[0][1]=sumatorioZ;
    matrizA[1][0]=sumatorioZ;
    matrizA[1][1]=sumatorioZCuadrado;
    
    std::vector< std::vector<double> > matrizB (2, std::vector <double>(1) );//Resultados
    matrizB[0][0]=sumatorioT;
    matrizB[1][0]=sumatorioZT;
    
    std::vector< std::vector<double> > matrizX (2, std::vector <double>(1) );//Matriz solucion de 2*1
    resolverSistemaEcuaciones(matrizA,matrizB,2,matrizX);

    a.push_back(matrizX[0][0]);
    a.push_back(matrizX[1][0]);
    cout<<"t(n) = "<<a[0]<<" + "<<a[1]<<"*n!"<<endl;
}

void calcularTiemposEstimadosFactorial(const vector <double> &n, const vector <double> &tiemposReales, const vector <double> &a, vector <double> &tiemposEstimados){
    /*Observacion: Para n pequeño las estimaciones no son correctas ya que al tratarse de tamaños pequeños la CPU
    /mete tareas antes de llamar a time.stop() y los tiempos calculados son extraños.*/
    double tiempo;
    for(int i=0;n.size()>i;i++){
        tiempo = a[0] + a[1]*factorial(n[i]);
        tiemposEstimados.push_back(tiempo);
    }
}

double calcularTiempoEstimadoFactorial(const double &n, const vector <double> &a){
    double tiempo=a[0] + a[1]*factorial(n);
    return tiempo;
}

void detRec(){
    vector <double> tiemposReales;
    vector <double> numeroElementos;
    vector <double> a;
    vector <double> tiemposEstimados;
    tiemposEjecucionDeterminanteRec(2,12,tiemposReales,numeroElementos);
    escribirFichero(tiemposReales,numeroElementos);
    ajusteFactorial(numeroElementos,tiemposReales,a);
    calcularTiemposEstimadosFactorial(numeroElementos,tiemposReales,a,tiemposEstimados);
    double coef=calcularCoeficienteDeterminacion(tiemposReales,tiemposEstimados);
    cout<<"El coeficiente de determinacion es "<<coef<<endl;
    escribirFicheroFinal(tiemposReales,numeroElementos,tiemposEstimados);
    int opcion;
    cout<<"Introduzca 1 si desea calcular el tiempo que tardaria el algoritmo para un determinado tamaño de muestra o 2 si no quiere. En caso afirmativo, para finalizar la ejecucion introduzca un tamaño de muestra 0"<<endl;
    cin>>opcion;
    if(opcion==1){
        int n;
        cout<<"Introduzca el tamaño de muestra"<<endl;
        cin>>n;
        vector <int> tiemposAnos;
        vector <int> tiemposDias;
        vector <int> tiemposMinutos;
        vector <int> tiemposSegundos;
        vector <int> numElem;
        while(n!=0){
            double time=calcularTiempoEstimadoFactorial(n,a);
            time=time/1000000;//Pasamos a segundos
            time=(int)time;
            int anos,dias,horas,minutos,segundos;
            tiempo(time,anos,dias,horas,minutos,segundos);
            numElem.push_back(n);
            tiemposAnos.push_back(anos);
            tiemposDias.push_back(dias);
            tiemposMinutos.push_back(minutos);
            tiemposSegundos.push_back(segundos);
            cin>>n;
        }
        for(int i=0;numElem.size()>i;i++){
            cout<<"Para una muestra de "<<numElem[i]<<" elementos tardaria una estimacion de: "<<tiemposAnos[i]<<" anos, "<<tiemposDias[i]<<" dias, "<<tiemposMinutos[i]<<" minutos y "<<tiemposSegundos[i]<<" segundos."<<endl; 
        }
    }
    else if(opcion==2){
        cout<<"Programa finalizado"<<endl;
    }
    else{
        cout<<"Debe introducir 1 o 2"<<endl;
        exit(-1);
    }
}