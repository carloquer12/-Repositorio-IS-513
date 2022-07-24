#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main(void){
    
    //Declaracioness
    char * tipos_datos[][3]={"entero","decimal","cadena"};
    char palabras_reservadas[][11]={"definir","hasta que","mientras","repetir","si","hacer","finsi","sino","leer","imprimir","cursor"};
    int estado=0; //ESTADO INICIAL
    char * res;
    char cadena[50];
    char imprimir[100]=" ";
    
    
    printf("--------------ANALIZADOR LEXICO EN C--------------\n");
    //Abriendo Archivo Externo
    FILE *ptfile;
    char caracter;
    ptfile=fopen("analizador_lexico.prg","r");
    if(ptfile==NULL){
        fputs("error",stderr);
        exit(1);
    }
    while ((caracter=fgetc(ptfile))!=EOF){
        //printf("%c",caracter);
        *cadena=caracter;
