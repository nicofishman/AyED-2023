#ifndef _TFILES_T_
#define _TFILES_T_

#include <stdio.h>

#include <iostream>

/**
 * Escribe el valor t en la posición actual del archivo f.
 * @param f Archivo donde se escribirá el valor.
 * @param t Valor a escribir.
 */
template <typename T>
void write(FILE* f, T t) {
    // Se debe anteponer esta linea al inicio de la funcion.
    // De otro modo, apareceran errores al momento de actualizar
    // archivos. Esto se debe a un error en la implementacion de Windows.
    //
    fseek(f, 0, SEEK_CUR);

    fwrite(&t, sizeof(T), 1, f);
}

/**
 * Lee del archivo f un registro tipo T y retorna el valor leído.
 * @param f Archivo donde se leerá el valor.
 */
template <typename T>
T read(FILE* f) {
    fseek(f, 0, SEEK_CUR);

    T t;
    fread(&t, sizeof(T), 1, f);
    return t;
}

/**
 * Mueve el indicador de posición del archivo f al inicio del registro n.
 * @param f Archivo donde se moverá el indicador de posición.
 * @param n Número de registro al que se moverá el indicador de posición.
 */
template <typename T>
void seek(FILE* f, int n) {
    fseek(f, n * sizeof(T), SEEK_SET);
}

/**
 * Retorna la cantidad de registros tipo T que contiene el archivo.
 * @param f Archivo del que se obtendrá la cantidad de registros.
 */
template <typename T>
int fileSize(FILE* f) {
    fseek(f, 0, SEEK_END);
    return ftell(f) / sizeof(T);
}

/**
 * Retorna el número de registro que está siendo apuntado por el indicador
de posición del archivo f.
 * @param f Archivo del que se obtendrá la posición actual.
*/
template <typename T>
int filePos(FILE* f) {
    return ftell(f) / sizeof(T);
}

#endif
