#ifndef _TCOLL_T_
#define _TCOLL_T_

#include <iostream>

#include "../funciones/strings.hpp"

using namespace std;

template <typename T>
struct Coll {
    char separator;
    int currentToken = -1;
    string data;
};

/**
 * Crea una colección vacía, preparada para contener elementos de tipo T;
 * utilizando el carácter sep como separador de la cadena tokenizada sobre la que se implementa la colección.
 * @param sep Carácter separador de la cadena tokenizada sobre la que se implementa la colección.
 */
template <typename T>
Coll<T> coll(char sep) {
    Coll<T> c = {sep};
    return c;
}

/**
 * Crea una colección vacía, preparada para contener elementos tipo T;
 * definiendo un separador por defecto para usar en la cadena tokenizada sobre la
 * cual se implementa la colección
 */
template <typename T>
Coll<T> coll() {
    Coll<T> c = coll<T>('|');
    return c;
}

/**
 * Retorna la cantidad de elementos que contiene la colección c.
 * @param c Colección sobre la cual se consulta la cantidad de elementos.
 */
template <typename T>
int collSize(Coll<T> c) {
    return tokenCount(c.data, c.separator);
}

/**
 * Remueve de la colección c todos sus elementos, dejándola vacía.
 * @param c Colección a modificar.
 */
template <typename T>
void collRemoveAll(Coll<T>& c) {
    while (collSize(c) > 0) {
        removeTokenAt(c.data, c.separator, 0);
    }
}

/**
 * Remueve de la colección c el elemento ubicado en la posición p.
 * Si p es inválido, no hace nada.
 * @param c Colección a modificar.
 * @param p Posición del elemento a remover.
 */
template <typename T>
void collRemoveAt(Coll<T>& c, int p) {
    if (p < 0 || p >= collSize(c)) {
        return;
    }
    removeTokenAt(c.data, c.separator, p);
}

/**
 * Agrega el elemento t al final de la colección c
 * @param c Colección a modificar.
 * @param t Elemento a agregar.
 * @param tToString Función que convierte un elemento de tipo T a string.
 */
template <typename T>
int collAdd(Coll<T>& c, T t, string tToString(T)) {
    addToken(c.data, c.separator, tToString(t));
    return tokenCount(c.data, c.separator) - 1;
}

/**
 * Reemplaza por t al elemento que se ubica en la posición p.
 * Si p es inválido, no hace nada.
 * @param c Colección a modificar.
 * @param t Elemento a agregar.
 * @param p Posición del elemento a reemplazar.
 * @param tToString Función que convierte un elemento de tipo T a string.
 */
template <typename T>
void collSetAt(Coll<T>& c, T t, int p, string tToString(T)) {
    if (p < 0 || p >= collSize(c)) {
        return;
    }
    setTokenAt(c.data, c.separator, tToString(t), p);
}

/**
 * Retorna el elemento que se ubica en la posición p.
 * Si p es inválido, retorna un elemento por defecto.
 * @param c Colección sobre la cual se consulta el elemento.
 * @param p Posición del elemento a retornar.
 * @param tFromString Función que convierte un string a un elemento de tipo T.
 */
template <typename T>
T collGetAt(Coll<T> c, int p, T tFromString(string)) {
    if (p < 0 || p >= collSize(c)) {
        return tFromString("");
    }

    return tFromString(getTokenAt(c.data, c.separator, p));
}

/**
 * Determina si la colección c contiene al elemento k.
 * @param c Colección sobre la cual se consulta la existencia del elemento.
 * @param k Elemento a buscar.
 * @param cmpTK Función que compara un elemento de tipo T con uno de tipo K.
 * @param tFromString Función que convierte un string a un elemento de tipo T.
 */
template <typename T, typename K>
int collFind(Coll<T> c, K k, int cmpTK(T, K), T tFromString(string)) {
    for (int i = 0; i < collSize(c); i++) {
        if (cmpTK(collGetAt(c, i, tFromString), k) == 0) {
            return i;
        }
    }
    return -1;
}

/**
 *  Ordena los elementos de la colección c según el criterio de precedencia que establece cmpTT
 * @param c Colección a ordenar.
 * @param cmpTT Función que compara dos elementos de tipo T.
 * @param tFromString Función que convierte un string a un elemento de tipo T.
 * @param tToString Función que convierte un elemento de tipo T a string.
 */
template <typename T>
void collSort(Coll<T>& c, int cmpTT(T, T), T tFromString(string), string tToString(T)) {
    for (int i = 0; i < collSize(c); i++) {
        for (int j = i + 1; j < collSize(c); j++) {
            if (cmpTT(collGetAt(c, i, tFromString), collGetAt(c, j, tFromString)) > 0) {
                T aux = collGetAt(c, i, tFromString);
                collSetAt(c, collGetAt(c, j, tFromString), i, tToString);
                collSetAt(c, aux, j, tToString);
            }
        }
    }
}

/**
 * Retorna true o false según queden, en la colección c, más elementos para
 * continuar iterando
 * @param c Colección sobre la cual se consulta si quedan elementos para iterar.
 */
template <typename T>
bool collHasNext(Coll<T> c) {
    if (c.currentToken >= collSize(c)) {
        return false;
    }
    return true;
}

/**
 * Retorna el siguiente elemento de la colección c, avanzando el cursor de la
 * colección.
 * @param c Colección sobre la cual se consulta el siguiente elemento.
 * @param tFromString Función que convierte un string a un elemento de tipo T.
 */
template <typename T>
T collNext(Coll<T>& c, T tFromString(string)) {
    if (collHasNext(c)) {
        T t = collGetAt(c, c.currentToken, tFromString);
        c.currentToken++;
        return t;
    }
    return tFromString("");
}

/**
 * Retorna el próximo elemento de la colección c, indicando si se llegó al
 * final de la colección. De este modo, permite prescindir de usar collHasNext.
 * @param c Colección sobre la cual se consulta el siguiente elemento.
 * @param endOfColl Variable que indica si se llegó al final de la colección.
 * @param tFromString Función que convierte un string a un elemento de tipo T.
 */
template <typename T>
T collNext(Coll<T>& c, bool& endOfColl, T tFromString(string)) {
    if (endOfColl) {
        return tFromString("");
    }
    c.currentToken++;
    return collGetAt(c, c.currentToken, tFromString);
}

/**
 * Reinicia la colección c para que la podamos volver a iterar.
 * @param c Colección a reiniciar.
 */
template <typename T>
void collReset(Coll<T>& c) {
    c.currentToken = -1;
}

// Retorna una cadena representando el valor contenido en la coleccion x.
template <typename T>
string collToString(Coll<T> c) {
    return c.sep + c.s;
}

// Retorna la coleccion representada en la cadena s.
template <typename T>
Coll<T> collFromString(string s) {
    return {substring(s, 1), s[0], 0};
}

#endif
