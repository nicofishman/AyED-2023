#ifndef _MAINHPP
#define _MAINHPP
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <sstream>
#include <string>

#include "../biblioteca/funciones/strings.hpp"
#include "../biblioteca/funciones/tokens.hpp"
#include "../biblioteca/tads/Coll.hpp"
using namespace std;

struct Ciudad {
    int idCiu;
    char descr[20];
    int millas;
};

struct Vuelo {
    int idVue;
    int cap;
    int idOri;
    int idDes;
};

struct Reserva {
    int idCli;
    int idVue;
    int cant;
};

string ciudadToString(Ciudad x) {
    char sep = 1;
    string sIdCiu = to_string(x.idCiu);
    string sDescr = x.descr;
    string sMillas = to_string(x.millas);
    return sIdCiu + sep + sDescr + sep + sMillas;
}

Ciudad ciudadFromString(string s) {
    char sep = 1;
    Ciudad x;
    string t0 = getTokenAt(s, sep, 0);
    x.idCiu = stoi(t0);
    string t1 = getTokenAt(s, sep, 1);
    strcpy(x.descr, t1.c_str());
    string t2 = getTokenAt(s, sep, 2);
    x.millas = stoi(t2);
    return x;
}

string ciudadToDebug(Ciudad x) {
    stringstream sout;
    sout << "[";
    sout << x.idCiu;
    sout << ",";
    sout << x.descr;
    sout << ",";
    sout << x.millas;
    sout << "]";
    return sout.str();
}

string ciudadToDebug(string mssg, Ciudad x) {
    stringstream sout;
    sout << mssg << ":[";
    sout << x.idCiu;
    sout << ",";
    sout << x.descr;
    sout << ",";
    sout << x.millas;
    sout << "]";
    return sout.str();
}

Ciudad ciudad(int idCiu, string descr, int millas) {
    Ciudad a;
    a.idCiu = idCiu;
    strcpy(a.descr, descr.c_str());
    a.millas = millas;
    return a;
}

bool ciudadEquals(Ciudad a, Ciudad b) {
    if (a.idCiu != b.idCiu) return false;
    if (a.millas != b.millas) return false;
    return true;
}

string vueloToString(Vuelo x) {
    char sep = 2;
    string sIdVue = to_string(x.idVue);
    string sCap = to_string(x.cap);
    string sIdOri = to_string(x.idOri);
    string sIdDes = to_string(x.idDes);
    return sIdVue + sep + sCap + sep + sIdOri + sep + sIdDes;
}

Vuelo vueloFromString(string s) {
    char sep = 2;
    Vuelo x;
    string t0 = getTokenAt(s, sep, 0);
    x.idVue = stoi(t0);
    string t1 = getTokenAt(s, sep, 1);
    x.cap = stoi(t1);
    string t2 = getTokenAt(s, sep, 2);
    x.idOri = stoi(t2);
    string t3 = getTokenAt(s, sep, 3);
    x.idDes = stoi(t3);
    return x;
}

string vueloToDebug(Vuelo x) {
    stringstream sout;
    sout << "[";
    sout << x.idVue;
    sout << ",";
    sout << x.cap;
    sout << ",";
    sout << x.idOri;
    sout << ",";
    sout << x.idDes;
    sout << "]";
    return sout.str();
}

string vueloToDebug(string mssg, Vuelo x) {
    stringstream sout;
    sout << mssg << ":[";
    sout << x.idVue;
    sout << ",";
    sout << x.cap;
    sout << ",";
    sout << x.idOri;
    sout << ",";
    sout << x.idDes;
    sout << "]";
    return sout.str();
}

Vuelo vuelo(int idVue, int cap, int idOri, int idDes) {
    Vuelo a;
    a.idVue = idVue;
    a.cap = cap;
    a.idOri = idOri;
    a.idDes = idDes;
    return a;
}

bool vueloEquals(Vuelo a, Vuelo b) {
    if (a.idVue != b.idVue) return false;
    if (a.cap != b.cap) return false;
    if (a.idOri != b.idOri) return false;
    if (a.idDes != b.idDes) return false;
    return true;
}

string reservaToString(Reserva x) {
    char sep = 3;
    string sIdCli = to_string(x.idCli);
    string sIdVue = to_string(x.idVue);
    string sCant = to_string(x.cant);
    return sIdCli + sep + sIdVue + sep + sCant;
}

Reserva reservaFromString(string s) {
    char sep = 3;
    Reserva x;
    string t0 = getTokenAt(s, sep, 0);
    x.idCli = stoi(t0);
    string t1 = getTokenAt(s, sep, 1);
    x.idVue = stoi(t1);
    string t2 = getTokenAt(s, sep, 2);
    x.cant = stoi(t2);
    return x;
}

string reservaToDebug(Reserva x) {
    stringstream sout;
    sout << "[";
    sout << x.idCli;
    sout << ",";
    sout << x.idVue;
    sout << ",";
    sout << x.cant;
    sout << "]";
    return sout.str();
}

string reservaToDebug(string mssg, Reserva x) {
    stringstream sout;
    sout << mssg << ":[";
    sout << x.idCli;
    sout << ",";
    sout << x.idVue;
    sout << ",";
    sout << x.cant;
    sout << "]";
    return sout.str();
}

Reserva reserva(int idCli, int idVue, int cant) {
    Reserva a;
    a.idCli = idCli;
    a.idVue = idVue;
    a.cant = cant;
    return a;
}

bool reservaEquals(Reserva a, Reserva b) {
    if (a.idCli != b.idCli) return false;
    if (a.idVue != b.idVue) return false;
    if (a.cant != b.cant) return false;
    return true;
}

//---------------
struct RCiudad {
    Ciudad ciudad;
    int cantidadDeVuelos;
};

struct RVuelo {
    Vuelo vuelo;
    int cantidadDeRechazados;
    bool cantidadDeOcupados;
};

struct RCliente {
    int idCli;
    int millasAcumuladas;
};

string rCiudadToString(RCiudad x) {
    char sep = 1;
    string sCiudad = ciudadToString(x.ciudad);
    string sCantidadDeVuelos = to_string(x.cantidadDeVuelos);
    return sCiudad + sep + sCantidadDeVuelos;
}

RCiudad rCiudadFromString(string s) {
    char sep = 1;
    RCiudad x;
    string t0 = getTokenAt(s, sep, 0);
    x.ciudad = ciudadFromString(t0);
    string t1 = getTokenAt(s, sep, 1);
    x.cantidadDeVuelos = stoi(t1);
    return x;
}

string rCiudadToDebug(RCiudad x) {
    stringstream sout;
    sout << "[";
    sout << ciudadToDebug(x.ciudad);
    sout << ",";
    sout << x.cantidadDeVuelos;
    sout << "]";
    return sout.str();
}

string rCiudadToDebug(string mssg, RCiudad x) {
    stringstream sout;
    sout << mssg << ":[";
    sout << ciudadToDebug(x.ciudad);
    sout << ",";
    sout << x.cantidadDeVuelos;
    sout << "]";
    return sout.str();
}

RCiudad rCiudad(Ciudad ciudad, int cantidadDeVuelos) {
    RCiudad a;
    a.ciudad = ciudad;
    a.cantidadDeVuelos = cantidadDeVuelos;
    return a;
}

bool rCiudadEquals(RCiudad a, RCiudad b) {
    if (!ciudadEquals(a.ciudad, b.ciudad)) return false;
    if (a.cantidadDeVuelos != b.cantidadDeVuelos) return false;
    return true;
}

string rVueloToString(RVuelo x) {
    char sep = 2;
    string sVuelo = vueloToString(x.vuelo);
    string sCantidadDeRechazados = to_string(x.cantidadDeRechazados);
    string sCantidadDeOcupados = to_string(x.cantidadDeOcupados);
    return sVuelo + sep + sCantidadDeRechazados + sep + sCantidadDeOcupados;
}

RVuelo rVueloFromString(string s) {
    char sep = 2;
    RVuelo x;
    string t0 = getTokenAt(s, sep, 0);
    x.vuelo = vueloFromString(t0);
    string t1 = getTokenAt(s, sep, 1);
    x.cantidadDeRechazados = stoi(t1);
    string t2 = getTokenAt(s, sep, 2);
    return x;
}

string rVueloToDebug(RVuelo x) {
    stringstream sout;
    sout << "[";
    sout << vueloToDebug(x.vuelo);
    sout << ",";
    sout << x.cantidadDeRechazados;
    sout << ",";
    sout << x.cantidadDeOcupados;
    sout << "]";
    return sout.str();
}

string rVueloToDebug(string mssg, RVuelo x) {
    stringstream sout;
    sout << mssg << ":[";
    sout << vueloToDebug(x.vuelo);
    sout << ",";
    sout << x.cantidadDeRechazados;
    sout << ",";
    sout << x.cantidadDeOcupados;
    sout << "]";
    return sout.str();
}

RVuelo rVuelo(Vuelo vuelo, int cantidadDeRechazados, bool cantidadDeOcupados) {
    RVuelo a;
    a.vuelo = vuelo;
    a.cantidadDeRechazados = cantidadDeRechazados;
    a.cantidadDeOcupados = cantidadDeOcupados;
    return a;
}

bool rVueloEquals(RVuelo a, RVuelo b) {
    if (!vueloEquals(a.vuelo, b.vuelo)) return false;
    if (a.cantidadDeRechazados != b.cantidadDeRechazados) return false;
    if (a.cantidadDeOcupados != b.cantidadDeOcupados) return false;
    return true;
}

string rClienteToString(RCliente x) {
    char sep = 3;
    string sIdCli = to_string(x.idCli);
    string sMillasAcumuladas = to_string(x.millasAcumuladas);
    return sIdCli + sep + sMillasAcumuladas;
}

RCliente rClienteFromString(string s) {
    char sep = 3;
    RCliente x;
    string t0 = getTokenAt(s, sep, 0);
    x.idCli = stoi(t0);
    string t1 = getTokenAt(s, sep, 1);
    x.millasAcumuladas = stoi(t1);
    return x;
}

string rClienteToDebug(RCliente x) {
    stringstream sout;
    sout << "[";
    sout << x.idCli;
    sout << ",";
    sout << x.millasAcumuladas;
    sout << "]";
    return sout.str();
}

string rClienteToDebug(string mssg, RCliente x) {
    stringstream sout;
    sout << mssg << ":[";
    sout << x.idCli;
    sout << ",";
    sout << x.millasAcumuladas;
    sout << "]";
    return sout.str();
}

RCliente rCliente(int idCli, int millasAcumuladas) {
    RCliente a;
    a.idCli = idCli;
    a.millasAcumuladas = millasAcumuladas;
    return a;
}

bool rClienteEquals(RCliente a, RCliente b) {
    if (a.idCli != b.idCli) return false;
    if (a.millasAcumuladas != b.millasAcumuladas) return false;
    return true;
}

#endif
