#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
using namespace std;

int maquinaDeEstado(string);
vector<string> split(string);

int main() {
  string nombreArchivo = "numerosYPalabras.txt";
  string linea;
  ifstream archivo(nombreArchivo.c_str());
  char caracter;
  int cantCadenas = 0;
  vector<string> cadenas;
  int cantNumerosValidos = 0;
  int cantNumerosInvalidos = 0;
  int cantPalabrasValidas = 0;
  int cantPalabrasInvalidas = 0;
  int response;
  if (archivo.is_open()) {
    while (getline(archivo, linea)) {
      cadenas = split(linea);
      for (int i = 0; i < cadenas.size(); i++) {
        response = maquinaDeEstado(cadenas[i]);
        if (response == 4) {
          cantNumerosValidos++;
        }else if (response == 5) {
          cantPalabrasValidas++;
        }else if (response == 6) {
          cantNumerosInvalidos++;
        }else if (response == 7) {
          cantPalabrasInvalidas++;
        }
        cantCadenas++;
      }
    }
    archivo.close();
  }else {
    cout << "No se pudo abrir el archivo: " << nombreArchivo << endl;
  }
  
  string nombreArchivo1 = "resultados.txt";
  ofstream archivo1;
  archivo1.open(nombreArchivo1.c_str(), ios::out);
  archivo1 << "Cantidad de números válidos: " << cantNumerosValidos << endl;
  archivo1 << "Cantidad de números inválidos: " << cantNumerosInvalidos << endl;
  archivo1 << "Cantidad de palabras válidas: " << cantPalabrasValidas << endl;
  archivo1 << "Cantidad de palabras inválidas: " << cantPalabrasInvalidas << endl << endl;
  archivo1 << "Total de cadenas válidas: " << cantNumerosValidos + cantPalabrasValidas << endl;
  archivo1 << "Total de cadenas inválidas: " << cantNumerosInvalidos + cantPalabrasInvalidas << endl;
  archivo1 << "Total de cadenas: " << cantCadenas << endl;
	archivo1.close();

  cout << "Fin del programa" << endl;

	return 0;
}

vector<string> split(string str) {
    int posInit = 0;
    int posFound = 0;
    string splitted;
    vector<string> results;
    int n;
    while(posFound >= 0){
      posFound = str.find("; ", posInit);
      n = 2;
      if(posFound < 0){
        posFound = str.find(";", posInit);
        n = 1;
      }
      splitted = str.substr(posInit, posFound - posInit);
      posInit = posFound + n;
      results.push_back(splitted);
    }
    
    return results;
}

int maquinaDeEstado(string cadena) {
  string tablaSimbolos[] = {
    "asm", "auto", "bool", "break", "case", "catch",
    "char", "class", "const", "const_cast", "continue", "default", "delete",
    "do", "double", "dynamic_cast", "else", "enum", "explicit", "extern", "false",
    "float", "for", "friend", "goto", "if", "inline", "int", "long", "mutable", "main",
    "namespace", "new", "operator", "printf", "private", "protected", "public", "register",
    "reinterpret_cast", "return", "short", "signed", "sizeof", "static", "static_cast",
    "struct", "switch", "template", "this", "throw", "true", "try", "typedef", "typeid",
    "typename", "union", "unsigned", "using", "virtual", "void", "volatile", "while"
  };
  enum TEstado {
    Q0,
    Q1,
    Q2,
    Q3,
    QACEPTACION_NUM,
    QACEPTACION_TXT,
    QERROR_NUM,
    QERROR_TXT
  };

  TEstado Estado = Q0;
  int simbolo, i = 0;
  while (i < cadena.length() && Estado != QERROR_NUM && Estado != QERROR_TXT) {
    simbolo = cadena[i];
    switch (Estado) {
      case Q0:
        if (simbolo == '-' || simbolo == '+') {
            Estado = Q1;
          }else if(simbolo >= '0' && simbolo <= '9' || simbolo == '.') {
            Estado = QERROR_NUM;
          }else if(simbolo >= 'a' && simbolo <= 'z') {
            Estado = QACEPTACION_TXT;
          }else {
            Estado = QERROR_TXT;
          }
        break;
      case Q1:
        if (simbolo >= '0' && simbolo <= '9') {
          Estado = Q2;
        }else {
          Estado = QERROR_NUM;
        }
        break;
      case Q2:
        if (simbolo >= '0' && simbolo <= '9') {
          Estado = Q2;
        }else if(simbolo == '.') {
          Estado = Q3;
        }else {
          Estado = QERROR_NUM;
        }
        break;
      case Q3:
        if (simbolo >= '0' && simbolo <= '9') {
          Estado = QACEPTACION_NUM;
        }else {
          Estado = QERROR_NUM;
        }
        break;
      case QACEPTACION_NUM:
        if (simbolo >= '0' && simbolo <= '9') {
          Estado = QACEPTACION_NUM;
        }else {
          Estado = QERROR_NUM;
        }
        break;
      case QACEPTACION_TXT:
        if (simbolo >= 'a' && simbolo <= 'z') {
          Estado = QACEPTACION_TXT;
        }else {
          Estado = QERROR_TXT;
        }
        break;
    }
    i++;
  }

  if (Estado == QACEPTACION_NUM) {
    cout<<"La cadena: "<<cadena<<" no es valido"<<endl;
    return QACEPTACION_NUM;
  }else if(Estado == QACEPTACION_TXT) {
    for (int i = 0; i < sizeof(tablaSimbolos) / sizeof(string); i++) {
      if (tablaSimbolos[i] == cadena) {
        cout<<"La cadena: "<<cadena<<" vAsido"<<endl;
        return QACEPTACION_TXT;
      }
    }
    cout<<"La cadena: "<<cadena<<" es una palabra INVALIDA"<<endl;
    return QERROR_TXT;
  }else if(Estado == QERROR_NUM || Estado >= Q0 && Estado <= Q3) {
    cout<<"La cadena: "<<cadena<<" es un numero INVALIDO"<<endl;
    return QERROR_NUM;
  }else if(Estado == QERROR_TXT) {
    cout<<"La cadena: "<<cadena<<" es una palabra INVALIDA"<<endl;
    return QERROR_TXT;
  }else {
    cout<<"ERROR: No se pudo determinar el estado de la cadena"<<endl;
  }
}
