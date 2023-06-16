#include <bits/stdc++.h>

#include "../biblioteca/funciones/files.hpp"
#include "../biblioteca/funciones/strings.hpp"
#include "../biblioteca/funciones/tokens.hpp"
#include "../biblioteca/tads/Coll.hpp"
#include "principalMio.hpp"

using namespace std;

Coll<RCiudad>
subirCiudades() {
    Coll<RCiudad> ret = coll<RCiudad>();
    FILE* f = fopen("CIUDADES.dat", "r+b");

    Ciudad c = read<Ciudad>(f);
    while (!feof(f)) {
        RCiudad rc = rCiudad(c, 0);
        collAdd<RCiudad>(ret, rc, rCiudadToString);

        c = read<Ciudad>(f);
    }

    fclose(f);
    return ret;
}

Coll<RVuelo> subirVuelos() {
    Coll<RVuelo> ret = coll<RVuelo>();
    FILE* f = fopen("VUELOS.dat", "r+b");

    Vuelo v = read<Vuelo>(f);
    while (!feof(f)) {
        RVuelo rv = rVuelo(v, 0, 0);
        collAdd<RVuelo>(ret, rv, rVueloToString);

        v = read<Vuelo>(f);
    }

    fclose(f);
    return ret;
}

int cmpRVueloId(RVuelo a, int id) {
    return a.vuelo.idVue - id;
}

int cmpCiudadId(RCiudad a, int id) {
    return a.ciudad.idCiu - id;
}

int cmpRClienteId(RCliente a, int id) {
    return a.idCli - id;
}

void procesarPunto1(Coll<RCiudad>& ciudades, Reserva reserva, Coll<RVuelo> vuelos) {
    int posVuelo = collFind<RVuelo, int>(vuelos, reserva.idVue, cmpRVueloId, rVueloFromString);
    RVuelo vuelo = collGetAt<RVuelo>(vuelos, reserva.idVue, rVueloFromString);

    int posCiudad = collFind<RCiudad>(ciudades, vuelo.vuelo.idDes, cmpCiudadId, rCiudadFromString);
    RCiudad ciudad = collGetAt<RCiudad>(ciudades, posCiudad, rCiudadFromString);

    ciudad.cantidadDeVuelos++;
    collSetAt<RCiudad>(ciudades, ciudad, posCiudad, rCiudadToString);
}

bool aceptoReserva(Reserva reserva, RVuelo vuelo) {
    return reserva.cant + vuelo.cantidadDeOcupados <= vuelo.vuelo.cap;
}

void procesarPunto2(Coll<RVuelo>& vuelos, Reserva reserva) {
    int posVuelo = collFind<RVuelo, int>(vuelos, reserva.idVue, cmpRVueloId, rVueloFromString);
    RVuelo vuelo = collGetAt<RVuelo>(vuelos, posVuelo, rVueloFromString);

    if (aceptoReserva(reserva, vuelo)) {
        vuelo.cantidadDeOcupados += reserva.cant;
    } else {
        vuelo.cantidadDeRechazados += reserva.cant;
    }

    collSetAt<RVuelo>(vuelos, vuelo, posVuelo, rVueloToString);
}

int calcularMillas(RVuelo vuelo, Coll<RCiudad> ciudades) {
    int posOrigen = collFind<RCiudad, int>(ciudades, vuelo.vuelo.idOri, cmpCiudadId, rCiudadFromString);
    int posDestino = collFind<RCiudad, int>(ciudades, vuelo.vuelo.idDes, cmpCiudadId, rCiudadFromString);

    RCiudad ciudadOrigen = collGetAt<RCiudad>(ciudades, posOrigen, rCiudadFromString);
    RCiudad ciudadDestino = collGetAt<RCiudad>(ciudades, posDestino, rCiudadFromString);

    return abs(ciudadOrigen.ciudad.millas - ciudadDestino.ciudad.millas);
}

void procesarPunto3(Coll<RCliente>& clientes, Reserva reserva, Coll<RCiudad> ciudades, Coll<RVuelo> vuelos) {
    int posCliente = collFind<RCliente, int>(clientes, reserva.idCli, cmpRClienteId, rClienteFromString);
    RCliente cliente;

    if (posCliente < 0) {
        cliente = rCliente(reserva.idCli, 0);
        posCliente = collAdd<RCliente>(clientes, cliente, rClienteToString);
    } else {
        cliente = collGetAt<RCliente>(clientes, posCliente, rClienteFromString);
    }

    int posVuelo = collFind<RVuelo, int>(vuelos, reserva.idVue, cmpRVueloId, rVueloFromString);
    RVuelo vuelo = collGetAt<RVuelo>(vuelos, posVuelo, rVueloFromString);

    if (aceptoReserva(reserva, vuelo)) {
        int millas = calcularMillas(vuelo, ciudades);
        cliente.millasAcumuladas += millas;
        collSetAt<RCliente>(clientes, cliente, posCliente, rClienteToString);
    }
}

void mostrarPunto1(Coll<RCiudad> ciudades) {
}

void mostrarPunto2(Coll<RVuelo> vuelos) {
}

void mostrarPunto3(Coll<RCliente> clientes) {
}

/**
 * La operatoria es la siguiente: un pasajero que vuela de una ciudad a otra
acumula una cantidad de millas equivalente a la diferencia entre las millas establecidas para cada una de esas ciudades, multiplicado por la cantidad de plazas reservadas. Esto será así siempre y cuando su reserva sea aceptada.
Sólo se aceptarán las reservas de aquellos pasajeros que requieran una
cantidad de plazas menor o igual a la disponibilidad actual del vuelo en cuestión. De
lo contrario la reserva completa será rechazada.

Se pide informar:
1. Para cada ciudad, cantidad de grupos (familias) que la eligieron de destino
2. Por cada vuelo, cantidad de plazas rechazadas, indicando también si el vuelo
saldrá completo o incompleto.
3. Para cada cliente, total de millas acumuladas.
*/

int main() {
    Coll<RCiudad> ciudades = subirCiudades();
    Coll<RVuelo> vuelos = subirVuelos();

    Coll<RCliente> clientes = coll<RCliente>();

    FILE* f = fopen("RESERVAS.dat", "r+b");
    Reserva r = read<Reserva>(f);
    while (!feof(f)) {
        procesarPunto1(ciudades, r, vuelos);
        procesarPunto2(vuelos, r);
        procesarPunto3(clientes, r, ciudades, vuelos);

        r = read<Reserva>(f);
    }

    mostrarPunto1(ciudades);
    mostrarPunto2(vuelos);
    mostrarPunto3(clientes);

    fclose(f);
    return 0;
}