#ifndef _TTOKENS_T_
#define _TTOKENS_T_

#include <stdio.h>

#include <iostream>

#include "strings.hpp"
using namespace std;

/**
 * Cuenta la cantidad tokens que el separador sep genera en s.
 * @param s Cadena de caracteres a analizar.
 * @param sep Caracter separador.
 */
int tokenCount(string s, char sep) {
    int start = length(s) == 0 ? 0 : 1;
    return charCount(s, sep) + start;
}

/**
 * Agrega el token t al final de la cadena s.
 * Si s es vacía, simplemente agrega t.
 * @param s Cadena de caracteres a modificar.
 * @param sep Caracter separador.
 * @param t Token a agregar.
 */
void addToken(string& s, char sep, string t) {
    if (length(s) == 0) {
        s = t;
    } else {
        s = s + sep + t;
    }
}

/**
 * Retorna el i-ésimo token de la cadena tokenizada s.
 * Si i es inválido, retorna una cadena vacía.
 * @param s Cadena de caracteres a analizar.
 * @param sep Caracter separador.
 * @param i Posición del token a retornar.
 */
string getTokenAt(string s, char sep, int i) {
    int n = tokenCount(s, sep);
    if (i < 0 || i >= n) {
        return "";
    }
    int startSepIndex = indexOfN(s, sep, i);
    if (i == n - 1) {
        return substring(s, startSepIndex + 1, length(s));
    }
    int endSepIndex = indexOfN(s, sep, i + 1);

    return substring(s, startSepIndex + 1, endSepIndex - 1);
}

/**
 *  Remueve de s el token ubicado en la posición i
 * Si i es inválido, no hace nada.
 * @param s Cadena de caracteres a modificar.
 * @param sep Caracter separador.
 * @param i Posición del token a remover.
 */
void removeTokenAt(string& s, char sep, int i) {
    int n = tokenCount(s, sep);
    if (i < 0 || i >= n) {
        return;
    }
    int startSepIndex = i == 0 ? 0 : indexOfN(s, sep, i);
    if (i == n - 1) {
        s = substring(s, 0, startSepIndex - 1);
    } else {
        int endSepIndex = indexOfN(s, sep, i + 1);
        char addedToken = i == 0 ? '\0' : sep;
        s = substring(s, 0, startSepIndex - 1) + addedToken + substring(s, endSepIndex + 1, length(s));
    }
}

/**
 * Reemplaza por t el token de s ubicado en la posición i
 * Si i es inválido, no hace nada.
 * @param s Cadena de caracteres a modificar.
 * @param sep Caracter separador.
 * @param t Token a agregar.
 * @param i Posición del token a reemplazar.
 */
void setTokenAt(string& s, char sep, string t, int i) {
    int n = tokenCount(s, sep);
    if (i < 0 || i >= n) {
        return;
    }
    int startSepIndex = i == 0 ? 0 : indexOfN(s, sep, i);
    if (i == n - 1) {
        s = substring(s, 0, startSepIndex) + sep + t;
    } else {
        int endSepIndex = indexOfN(s, sep, i + 1);
        char addedToken = i == 0 ? '\0' : sep;
        s = substring(s, 0, startSepIndex - 1) + addedToken + t + substring(s, endSepIndex, length(s));
    }
}

/**
 * Determinar la posición que el token t ocupa dentro de la cadena s.
 * @param s Cadena de caracteres a analizar.
 * @param sep Caracter separador.
 * @param t Token a buscar.
 * @returns int - La posición de la primera ocurrencia del token t dentro de la cadena s, o un valor negativo si s no contiene a t.
 */
int findToken(string s, char sep, string t) {
    int n = tokenCount(s, sep);
    for (int i = 0; i < n; i++) {
        if (getTokenAt(s, sep, i) == t) {
            return i;
        }
    }
    return -1;
}

#endif
