#include <iostream> 
#include <fstream> 
using namespace std; 
 

int main() { 
    string lineaActual, primerLinea; 
    ifstream archivo("JSON.txt"); 
    int llavesAbiertas = 0; 
    bool inicioAnalisis = true; 
 
     (getline(archivo, lineaActual));//Esta instruccion es para pasar de una linea del texto, a la siguiente. 
 
    while(lineaActual==""){ //instruccion que ignora las lineas en blanco, itera hasta encontrar la linea con la "{" 
        getline(archivo, lineaActual); 
    } 
