#include "quicksort.hpp"

using namespace std;

void rellenarVector(vector <int> &v, int nEle){
    srand(time(NULL));
    for(int i=0;nEle>i;i++){
        v.push_back(rand()%10000000);
    }
}

bool estaOrdenado(const vector <int> &v){
    bool ord=false;
    int a=-1;
    for(int i=0;v.size()>i;i++){
        if(v[i]>a){
            ord=true;
        }
        else{
            return false;
        }
        a=v[i];
    }
    return ord;
}

void tiemposOrdenacionQuicksort(int nMin, int nMax, int repeticiones, std::vector <double> &tiemposReales, std::vector <double> &numeroElementos){
    int inc;
    double media=0.0;
    Clock tiempo;
    std::cout<<"Introduzca el incremento de n"<<std::endl;
    std::cin>>inc;
    for(int i=nMin;nMax>=nMin;nMin=nMin+inc){
        media=0.0;
        for(int i=0;repeticiones>i;i++){
            std::vector <int> v;
            rellenarVector(v, nMin);
            tiempo.restart();
            std::sort(v.begin(),v.end());
            if(tiempo.isStarted()){
                tiempo.stop();
            }
            media = media + tiempo.elapsed();
        }
        media=media/repeticiones;
        tiemposReales.push_back(media);
        numeroElementos.push_back(nMin);
    }
}

void ajusteNlogN(const vector <double> &numeroElementos, const vector <double> &tiemposReales, vector <double> &a){
    //La curva seria del tipo: t(n)= a0 + a1*n*log n
    //Con cambio de variable: z=n*log n -> t(n)=a0 + a1*z
    //Por tanto a=[a0,a1];

    double sumatorioN=sumatorio(numeroElementos,tiemposReales,1,0);
    double sumatorioT=sumatorio(numeroElementos,tiemposReales,0,1);

    vector <double> z;
    double valorZ;
    for(int i=0;numeroElementos.size()>i;i++){
        valorZ = numeroElementos[i] * log10(numeroElementos[i]);
        z.push_back(valorZ);
    }
    
    double sumatorioZ=sumatorio(z,tiemposReales,1,0);
    double sumatorioZCuadrado=sumatorio(z,tiemposReales,2,0);
    double sumatorioZT=sumatorio(z,tiemposReales,1,1);
    
    std::vector< std::vector<double> > matrizA (2, std::vector <double>(2) );
    matrizA[0][0]=numeroElementos.size();
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

    cout<<"t(n) = "<<a[0]<<" + "<<a[1]<<" *n*log(n)"<<endl;

    
    /*std::vector< std::vector<double> > matrizA (2, std::vector <double>(2) );
    for(int i=0;matrizA.size()>i;i++){
        for(int j=0;matrizA.size()>j;j++){
            if(i==0 && j==0){
                matrizA[i][j]=numeroElementos.size();
            }
            else matrizA[i][j]=sumatorio(numeroElementos,tiemposReales,i+j,1);
        }
    }

    std::vector< std::vector<double> > matrizB (2, std::vector <double>(1) );//Resultados
    for(int i=0;matrizB.size()>i;i++){
        matrizB[i][0]=sumatorio(numeroElementos,tiemposReales,i,1);
    }

    std::vector< std::vector<double> > matrizX (2, std::vector <double>(1) );//Matriz solucion de 2*1
    resolverSistemaEcuaciones(matrizA,matrizB,matrizA.size(),matrizX);

    for(int i=0;matrizX.size()>i;i++) a.push_back(matrizX[i][0]);
    cout<<"t(n) = "<<a[0]<<" + "<<a[1]<<" *n*log(n)"<<endl;*/

    /*Lo hago de forma "no automatica" sin usar estos bucles porque por alguna razon que desconozco no me calcula 
    bien los tiempos estimados y de la otra manera si*/
}

void calcularTiemposEstimadosNlogN(const vector <double> &numeroElementos, const vector <double> &a, vector <double> &tiemposEstimados){
    double tiempo;
    for(int i=0;numeroElementos.size()>i;i++){
        tiempo = a[0] + a[1]*numeroElementos[i]*log10(numeroElementos[i]);
        tiemposEstimados.push_back(tiempo);
    }
}

double calcularTiempoEstimadoNlogN(const double &n, vector <double> &a){
    double tiempo=(a[0] + a[1]*n*log10(n));
    return tiempo;
}

void quicksort(){
    vector <double> tiemposReales;
    vector <double> numeroElementos;
    vector <double> a;
    vector <double> tiemposEstimados;
    tiemposOrdenacionQuicksort(10000,500000,3,tiemposReales,numeroElementos);
    escribirFichero(tiemposReales,numeroElementos);
    ajusteNlogN(numeroElementos,tiemposReales,a);
    calcularTiemposEstimadosNlogN(numeroElementos,a,tiemposEstimados);
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
            double time=calcularTiempoEstimadoNlogN(n,a);
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