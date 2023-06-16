#ifndef _TSTRINGS_T_
#define _TSTRINGS_T_

#include <math.h>
#include <stdio.h>

#include <iostream>
using namespace std;

/**
 * Devuelve la longitud de la cadena.
 * @param s la cadena
 */
int length(string s) {
    int i = 0;
    while (s[i] != '\0') {
        i++;
    }
    return i;
}

/**
 * Cuenta la cantidad de ocurrencias de un caracter en una cadena.
 * @param s la cadena
 * @param c el caracter
 */
int charCount(string s, char c) {
    int count = 0;
    for (int i = 0; i < length(s); i++) {
        if (s[i] == c) {
            count++;
        }
    }
    return count;
}

/**
 * Devuelve la subcadena de una cadena comprendida entre las posiciones d(inclusive) y `h` (no inclusive).
 * @param s la cadena
 * @param d la posición inicial (inclusive)
 * @param h la posición final (no inclusive)
 */
string substring(string s, int d, int h) {
    string sub = "";
    for (int i = d; i <= h; i++) {
        sub += s[i];
    }
    return sub;
}

/**
 * Devuelve la subcadena de una cadena comprendida entre las posiciones d(inclusive) y el final de la cadena.
 * @param s la cadena
 * @param d la posición inicial (inclusive)
 */
string substring(string s, int d) {
    string sub = substring(s, d, length(s) - 1);
    return sub;
}

/**
 * Devuelve la posición que ocupa la primera ocurrencia de un caracter en una cadena.
 * @param s la cadena
 * @param c el caracter
 */
int indexOf(string s, char c) {
    int idx = -1;
    for (int i = 0; i < length(s); i++) {
        if (s[i] == c) {
            idx = i;
            break;
        }
    }
    return idx;
}

/**
 * Devuelve la posición que ocupa la primera ocurrencia de un caracter en una cadena, comenzando a buscar a partir de una posición.
 * @param s la cadena
 * @param c el caracter
 * @param offSet la posición a partir de la cual se comienza a buscar
 */
int indexOf(string s, char c, int offSet) {
    string substrToAnalyze = substring(s, offSet);
    int idx = indexOf(substrToAnalyze, c);
    if (idx == -1) {
        return -1;
    } else {
        return idx + offSet;
    }
}

/**
 * Devuelve la posición que ocupa la primera ocurrencia de una subcadena en una cadena.
 * @param s la cadena
 * @param toSearch la subcadena a buscar
 */
int indexOf(string s, string toSearch) {
    int idx = -1;
    for (int i = 0; i < length(s); i++) {
        string substrToAnalyze = substring(s, i, i + length(toSearch) - 1);
        if (substrToAnalyze == toSearch) {
            idx = i;
            break;
        }
    }
    return idx;
}

/**
 * Devuelve la posición que ocupa la primera ocurrencia de una subcadena en una cadena, comenzando a buscar a partir de una posición.
 * @param s la cadena
 * @param toSearch la subcadena a buscar
 * @param offset la posición a partir de la cual se comienza a buscar
 */
int indexOf(string s, string toSearch, int offset)  // ok
{
    int idx = -1;
    string substrToAnalyze = substring(s, offset);
    idx = indexOf(substrToAnalyze, toSearch);
    if (idx == -1) {
        return -1;
    } else {
        return idx + offset;
    }
}

/**
 * Devuelve la posición que ocupa la última ocurrencia de un caracter en una cadena.
 * @param s la cadena
 * @param c el caracter
 */
int lastIndexOf(string s, char c) {
    int idx = -1;
    for (int i = 0; i < length(s); i++) {
        if (s[i] == c) {
            idx = i;
        }
    }
    return idx;
}

/**
 * Devuelve la posición que ocupa la n-ésima ocurrencia de un caracter en una cadena.
 * @param s la cadena
 * @param c el caracter
 * @param n la ocurrencia
 */
int indexOfN(string s, char c, int n) {
    if (n == 0) {
        return -1;
    }
    int occurrencias = 0;
    int idx = -1;
    for (int i = 0; i < length(s); i++) {
        if (s[i] == c) {
            occurrencias++;
            if (occurrencias == n) {
                idx = i;
                break;
            }
        }
    }
    return idx;
}

/**
 * Devuelve el valor numérico de un caracter.
 * @param c el caracter
 */
int charToInt(char c) {
    if (c >= '0' && c <= '9') {
        return c - '0';
    } else if (c >= 'A' && c <= 'Z') {
        return c - 'A' + 10;
    } else if (c >= 'a' && c <= 'z') {
        return c - 'a' + 10;
    } else {
        return -1;
    }
}

/**
 * Devuelve el caracter correspondiente a un valor numérico. El valor numérico debe estar comprendido entre 0 y 9 o entre 65 y 90.
 * @param i el valor numérico
 */
char intToChar(int i) {
    if (i >= 0 && i <= 9) {
        return i + '0';
    } else if (i >= 65 && i <= 90) {
        return (i - 65) + 'A';
    } else {
        return '-';
    }
}

/**
 * Devuelve el i-ésimo dígito de un número, contando desde la derecha.
 * @param n el número
 * @param i la posición del dígito
 */
int getDigit(int n, int i) {
    string s = "";
    while (n > 0) {
        s += intToChar(n % 10);
        n = n / 10;
    }
    char c = s[i];
    return charToInt(c);
}

/**
 * Devuelve la cantidad de dígitos de un número.
 * @param n el número
 */
int digitCount(int n) {
    int cont = 0;
    int num = n;
    while (n != 0) {
        n = n / 10;
        cont++;
    }
    return cont;
}

/**
 * Devuelve una cadena de caracteres representando el valor de un número.
 * @param i el número
 */
string intToString(int i) {
    string s = "";
    while (i > 0) {
        s = intToChar(i % 10) + s;
        i = i / 10;
    }
    return s;
}

/**
 * Devuelve el valor numérico de una cadena de caracteres, considerando que la cadena representa un número en base b.
 * @param s la cadena
 * @param b la base
 */
int stringToInt(string s, int b) {
    int n = 0;
    int exp = 1;
    for (int i = length(s) - 1; i >= 0; i--) {
        n += charToInt(s[i]) * exp;
        exp *= b;
    }
    return n;
}

/**
 * Devuelve el valor numérico de una cadena de caracteres, considerando que la cadena representa un número en base 10.
 */
int stringToInt(string s) {
    // chequear que la cadena sea un número
    for (int i = 0; i < length(s); i++) {
        if (s[i] < '0' || s[i] > '9') {
            return -1;
        }
    }
    return stringToInt(s, 10);
}

/**
 * Devuelve una cadena cuyo unico caracter es el caracter c.
 * @param c el caracter
 */
string charToString(char c) {
    string s = "";
    s += c;
    return s;
}

/**
 * Devuelve un caracter correspondiente a una cadena de un solo caracter.
 * @param s la cadena
 */
char stringToChar(string s) {
    return s[0];
}

/**
 * Devuelve la misma cadena que recibe como parámetro.
 * @param s la cadena
 */
string stringToString(string s) {
    return s;
}

/**
 * Devuelve la representación en cadena de un número de punto flotante.
 * @param d el número
 */
//* VER POR QUE ME AGREGA DECIMALES RANDOM:
//* d = 123.456 -> 123.4560000000000030695446184836328029632568359375
string doubleToString(double d) {
    string s = "";
    int parteEntera = (int)d;
    double parteDecimal = d - parteEntera;

    s = intToString(parteEntera);

    string parteDecimalStr = "";
    while (parteDecimal > 0) {
        parteDecimal *= 10;
        int digito = (int)parteDecimal;
        parteDecimalStr += intToChar(digito);
        parteDecimal -= digito;
    }

    return s + "." + parteDecimalStr;
}

/**
 * Devuelve el valor numérico de una cadena de caracteres, considerando que la cadena representa un número de punto flotante.
 */
double stringToDouble(string s) {
    int posPunto = indexOf(s, '.');
    string parteEntera = substring(s, 0, posPunto - 1);
    string parteDecimal = substring(s, posPunto + 1);

    int parteEnteraInt = stringToInt(parteEntera);
    int parteDecimalInt = stringToInt(parteDecimal);

    double parteDecimalDouble = parteDecimalInt;
    int exp = 1;
    for (int i = 0; i < length(parteDecimal); i++) {
        exp *= 10;
    }
    parteDecimalDouble = parteDecimalDouble / exp;

    return parteEnteraInt + parteDecimalDouble;
}

/**
 * Devuelve true si la cadena es vacía.
 * @param s la cadena
 */
bool isEmpty(string s) {
    return s[0] == '\0';
}

/**
 * Devuelve true si la cadena empieza con la cadena x.
 * @param s la cadena
 * @param x la cadena a buscar si empieza
 */
bool startsWith(string s, string x) {
    int xLength = length(x);
    string substrToAnalyze = substring(s, 0, xLength - 1);
    return substrToAnalyze == x;
}

/**
 * Devuelve true si la cadena termina con la cadena x.
 * @param s la cadena
 * @param x la cadena a buscar si empieza
 */
bool endsWith(string s, string x) {
    int xLength = length(x);
    string substrToAnalyze = substring(s, length(s) - xLength, length(s) - 1);
    return substrToAnalyze == x;
}

/**
 * Devuelve true si la cadena contiene al caracter x.
 * @param s la cadena
 * @param x el caracter a buscar
 */
bool contains(string s, char c) {
    return indexOf(s, c) != -1;
}

/**
 * Reemplaza en s todas las ocurrencias de oldChar por newChar
 * @param s la cadena
 * @param oldChar el caracter a reemplazar
 * @param newChar el caracter nuevo
 */
string replace(string s, char oldChar, char newChar) {
    string newString = "";
    for (int i = 0; i < length(s); i++) {
        char caracter = s[i];
        if (caracter == oldChar) {
            newString += newChar;
        } else {
            newString += caracter;
        }
    }
    return newString;
}

/**
 * Inserta el caracter c en la posicion pos de la cadena s.
 * @param s la cadena
 * @param pos la posición
 * @param c el caracter
 */
string insertAt(string s, int pos, char c) {
    string prevToPos = substring(s, 0, pos - 1);
    string afterPos = substring(s, pos);
    return prevToPos + c + afterPos;
}

/**
 * Remover de s el caracter ubicado en la posicion pos
 * @param s la cadena
 * @param pos la posición
 */
string removeAt(string s, int pos) {
    string prevPos = substring(s, 0, pos - 1);
    string afterPos = substring(s, pos + 1);
    return prevPos + afterPos;
}

/**
 * Recorta los espacios en blanco que se encuentren a la izquierda de s
 * @param s la cadena
 */
string ltrim(string s) {
    while (s[0] == ' ') {
        s = substring(s, 1);
    }
    return s;
}

/**
 * Recorta los espacios en blanco que se encuentren a la derecha de s
 * @param s la cadena
 */
string rtrim(string s) {
    while (s[length(s) - 1] == ' ') {
        s = substring(s, 0, length(s) - 2);
    }
    return s;
}

/**
 * Recorta los espacios en blanco que se encuentren a la izquierda y a la derecha de s
 * @param s la cadena
 */
string trim(string s) {
    return ltrim(rtrim(s));
}

/**
 * Devuelve una cadena de longitud n, compuesta por el caracter c
 * @param c el caracter
 * @param n la longitud
 */
string replicate(char c, int n) {
    string s = "";
    for (int i = 0; i < n; i++) {
        s += c;
    }
    return s;
}

/**
 * Devuelve una cadena de longitud n, compuesta por espacios
 * @param n la longitud
 */
string spaces(int n) {
    return replicate(' ', n);
}

/**
 * Retorna una cadena idéntica a s, con longitud n completando, si fuese
necesario, con caracteres c a la izquierda hasta llegar a la longitud requerida.
* @param s la cadena
* @param n la longitud
* @param c el caracter
*/
string lpad(string s, int n, char c) {
    if (length(s) >= n) {
        return s;
    } else {
        return replicate(c, n - length(s)) + s;
    }
}

/**
 * Retorna una cadena idéntica a s, con longitud n completando, si fuese
necesario, con caracteres c a la derecha hasta llegar a la longitud requerida.
* @param s la cadena
* @param n la longitud
* @param c el caracter
*/
string rpad(string s, int n, char c) {
    if (length(s) >= n) {
        return s;
    } else {
        return s + replicate(c, n - length(s));
    }
}

/**
 * Retorna una cadena idéntica a s, con longitud n completando, si fuese
necesario, con caracteres c a la derecha y a la izquierda hasta llegar a la longitud requerida.
* @param s la cadena
* @param n la longitud
* @param c el caracter
*/
string cpad(string s, int n, char c) {
    if (length(s) >= n) {
        return s;
    } else {
        int cantCaracteresParaLlenar = n - length(s);
        int cantCaracteresIzq = cantCaracteresParaLlenar / 2;
        int cantCaracteresDer = cantCaracteresParaLlenar - cantCaracteresIzq;
        return replicate(c, cantCaracteresIzq) + s + replicate(c, cantCaracteresDer);
    }
}

/**
 * Determina si el valor de c corresponde o no a un dígito numérico.
 * @param c el caracter
 */
bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

/**
 * Determina si el valor de c corresponde o no a una letra.
 * @param c el caracter
 */
bool isLetter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

/**
 * Determinar si el valor de c corresponde a una letra mayúscula.
 * @param c el caracter
 */
bool isUpperCase(char c) {
    return c >= 'A' && c <= 'Z';
}

/**
 * Determinar si el valor de c corresponde a una letra minúscula.
 * @param c el caracter
 */
bool isLowerCase(char c) {
    return c >= 'a' && c <= 'z';
}

/**
 * Convertir el valor de c a mayúscula.
 * @param c el caracter
 */
char toUpperCase(char c) {
    if (isLowerCase(c)) {
        return c - 'a' + 'A';
    } else {
        return c;
    }
}

/**
 * Convertir el valor de c a minúscula.
 * @param c el caracter
 */
char toLowerCase(char c) {
    if (isUpperCase(c)) {
        return c - 'A' + 'a';
    } else {
        return c;
    }
}

/**
 * Retorna una cadena idéntica a s pero completamente en mayúsculas.
 * @param s la cadena
 */
string toUpperCase(string s) {
    string sUpper = "";
    for (int i = 0; i < length(s); i++) {
        sUpper += toUpperCase(s[i]);
    }
    return sUpper;
}

/**
 * Retorna una cadena idéntica a s pero completamente en minúsculas.
 * @param s la cadena
 */
string toLowerCase(string s) {
    string sLower = "";
    for (int i = 0; i < length(s); i++) {
        sLower += toLowerCase(s[i]);
    }
    return sLower;
}

/**
 * Compara alfabéticamente dos cadenas.
 * @param a la cadena a
 * @param b la cadena b
 */
int cmpString(string a, string b) {
    if (a == b) {
        return 0;
    } else if (a < b) {
        return -1;
    } else {
        return 1;
    }
}

/**
 *  Compara dos valores.
 * @param a el valor a
 * @param b el valor b
 */
int cmpDouble(double a, double b) {
    if (a == b) {
        return 0;
    } else if (a < b) {
        return -1;
    } else {
        return 1;
    }
}

#endif
