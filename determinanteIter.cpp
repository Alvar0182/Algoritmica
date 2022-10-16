#include "determinanteIter.hpp"

std::vector< std::vector<double> > rellenarMatrizAleatoriamente(int n){
    std::vector< std::vector<double> > matriz (n, std::vector <double>(n) );
    srand(time(NULL));
    for(int i=0;matriz.size()>i;i++){
        for(int j=0;matriz.size()>j;j++){
            matriz[i][j]=(0.95 + (double)(rand()%10000)/100000);
        }
    }
    return matriz;
}

std::vector< std::vector<double> > rellenarMatrizManualmente(int n){
    std::vector< std::vector<double> > matriz (n, std::vector <double>(n) );
    for(int i=0;matriz.size()>i;i++){
        for(int j=0;matriz.size()>j;j++){
            std::cout<<"Introduzca el elemento de la fila "<<i+1<<" y de la columna "<<j+1<<std::endl;
            std::cin>>matriz[i][j];
        }
    }
    return matriz;
}

double calcularDeterminanteIter(std::vector< std::vector<double> > &matriz){
    double aux,pivote1,pivote2,deter;
    deter=1;

    for(int i=0;matriz.size()>i;i++){
        pivote1=matriz[i][i];
        for(int j=i+1;matriz.size()>j;j++){
            pivote2=matriz[j][i];
            aux=pivote2/pivote1;
            for(int k=0;matriz.size()>k;k++){
                matriz[j][k]=matriz[j][k]-aux*matriz[i][k];
            }
        }
    }
    for(int i=0;matriz.size()>i;i++){
        deter=deter*matriz[i][i];
    }
    return deter;
}

void tiemposEjecucionDeterminanteIter(int nMin, int nMax, vector <double> &tiemposReales, vector <double> &numeroElementos){
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
        calcularDeterminanteIter(matriz);
        if(tiempo.isStarted()){
            tiempo.stop();
        }
        media = tiempo.elapsed();
        tiemposReales.push_back(media);
        numeroElementos.push_back(nMin);
    }
}

void ajustePolinomico(const vector <double> &n, const vector <double> &tiemposReales, vector <double> &a){
    double sumatorioN=sumatorio(n,tiemposReales,1,0);
    double sumatorioT=sumatorio(n,tiemposReales,0,1);
    double sumatorioNCuadrado=sumatorio(n,tiemposReales,2,0);
    double sumatorioNCubo=sumatorio(n,tiemposReales,3,0);
    double sumatorioNCuarta=sumatorio(n,tiemposReales,4,0);
    double sumatorioNQuinta=sumatorio(n,tiemposReales,5,0);
    double sumatorioNSexta=sumatorio(n,tiemposReales,6,0);

    double sumatorioTN=sumatorio(n,tiemposReales,1,1);
    double sumatorioTNCuadrado=sumatorio(n,tiemposReales,2,1);
    double sumatorioTNCubo=sumatorio(n,tiemposReales,3,1);

    std::vector< std::vector<double> > matrizA (4, std::vector <double>(4) );
    matrizA[0][0]=n.size();
    matrizA[0][1]=sumatorioN;
    matrizA[0][2]=sumatorioNCuadrado;
    matrizA[0][3]=sumatorioNCubo;
    matrizA[1][0]=sumatorioN;
    matrizA[1][1]=sumatorioNCuadrado;
    matrizA[1][2]=sumatorioNCubo;
    matrizA[1][3]=sumatorioNCuarta;
    matrizA[2][0]=sumatorioNCuadrado;
    matrizA[2][1]=sumatorioNCubo;
    matrizA[2][2]=sumatorioNCuarta;
    matrizA[2][3]=sumatorioNQuinta;
    matrizA[3][0]=sumatorioNCubo;
    matrizA[3][1]=sumatorioNCuarta;
    matrizA[3][2]=sumatorioNQuinta;
    matrizA[3][3]=sumatorioNSexta;

    std::vector< std::vector<double> > matrizB (4, std::vector <double>(1) );
    matrizB[0][0]=sumatorioT;
    matrizB[1][0]=sumatorioTN;
    matrizB[2][0]=sumatorioTNCuadrado;
    matrizB[3][0]=sumatorioTNCubo;
    
    std::vector< std::vector<double> > matrizX (4, std::vector <double>(1) );
    resolverSistemaEcuaciones(matrizA,matrizB,4,matrizX);

    a.push_back(matrizX[0][0]);
    a.push_back(matrizX[1][0]);
    a.push_back(matrizX[2][0]);
    a.push_back(matrizX[3][0]);
    cout<<"t(n) = "<<a[0]<<" + "<<a[1]<<"*n"<<" + "<<a[2]<<"*n^2"<<" + "<<a[3]<<"*n^3"<<endl;
}

void calcularTiemposEstimadosPolinomico(const vector <double> &n, const vector <double> &tiemposReales, const vector <double> &a, vector <double> &tiemposEstimados){
    double tiempo;
    for(int i=0;n.size()>i;i++){
        tiempo = a[0] + a[1]*n[i] + a[2]*n[i]*n[i] + a[3]*n[i]*n[i]*n[i];
        tiemposEstimados.push_back(tiempo);
    }
}

double calcularTiempoEstimadoPolinomico(const double &n, const vector <double> &a){
    double tiempo=(a[0] + a[1]*n + a[2]*n*n + a[3]*n*n*n);
    return tiempo;
}

void detIter(){
    vector <double> tiemposReales;
    vector <double> numeroElementos;
    vector <double> a;
    vector <double> tiemposEstimados;
    tiemposEjecucionDeterminanteIter(100,500,tiemposReales,numeroElementos);
    escribirFichero(tiemposReales,numeroElementos);
    ajustePolinomico(numeroElementos,tiemposReales,a);
    calcularTiemposEstimadosPolinomico(numeroElementos,tiemposReales,a,tiemposEstimados);
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
            double time=calcularTiempoEstimadoPolinomico(n,a);
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