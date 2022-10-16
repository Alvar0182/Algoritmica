#include "main.hpp"

using namespace std;

int main(){
    int opcion;
    std::cout<<"Introduzca el algoritmo que desea ejecutar"<<std::endl;
    std::cout<<"Opcion 1: Quicksort"<<std::endl;
    std::cout<<"Opcion 2: Calculo del determinante de forma iterativa"<<std::endl;
    std::cout<<"Opcion 3: Calculo del determinante de forma recursiva"<<std::endl;
    std::cin>>opcion;

    switch(opcion){
        case 1:
        quicksort();
        break;
        
        case 2:
        detIter();
        break;

        case 3:
        detRec();
        break;

        default:
        std::cout<<"Debe seleccionar una de las 3 opciones"<<std::endl;
        return EXIT_FAILURE;
    }
}