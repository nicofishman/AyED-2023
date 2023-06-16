#include <bits/stdc++.h>

#include "../biblioteca/funciones/files.hpp"
#include "../biblioteca/funciones/strings.hpp"
#include "../biblioteca/funciones/tokens.hpp"
#include "../biblioteca/tads/Coll.hpp"
#include "principal.hpp"

Coll<REquipo> subirEquipos() {
    FILE* f = fopen("EQUIPOS.dat", "r+b");

    Coll<REquipo> equipos = coll<REquipo>();

    Equipo e = read<Equipo>(f);
    while (!feof(f)) {
        REquipo equipo = rEquipo(e, 0);
        collAdd<REquipo>(equipos, equipo, rEquipoToString);
        e = read<Equipo>(f);
    }

    fclose(f);
    return equipos;
}

int cmpREquipoId(REquipo rEquipo, int id) {
    return rEquipo.equipo.idEq - id;
}

int cmpEstadioNombre(REstadio est, string nombre) {
    return cmpString(est.estadio, nombre);
}

void sumarPuntosAEquipo(int puntos, int id, Coll<REquipo>& equipos) {
    int pos = collFind<REquipo, int>(equipos, id, cmpREquipoId, rEquipoFromString);
    REquipo e = collGetAt<REquipo>(equipos, pos, rEquipoFromString);

    e.puntosGanados = puntos;
    collSetAt<REquipo>(equipos, e, pos, rEquipoToString);
}

void procesarPunto1(Resultado res, Coll<REquipo>& equipos) {
    if (res.codRes < 0) {
        sumarPuntosAEquipo(3, res.idEq1, equipos);
    } else if (res.codRes > 0) {
        sumarPuntosAEquipo(3, res.idEq2, equipos);
    } else {
        sumarPuntosAEquipo(1, res.idEq1, equipos);
        sumarPuntosAEquipo(1, res.idEq2, equipos);
    }
}

void procesarPunto2(Resultado res, Coll<REstadio>& estadios) {
    string estadioNombre = res.estadio;
    int posEstadio = collFind<REstadio, string>(estadios, estadioNombre, cmpEstadioNombre, rEstadioFromString);

    if (posEstadio < 0) {
        REstadio nuevoEstadio = rEstadio(estadioNombre, 0, 0);
        posEstadio = collAdd<REstadio>(estadios, nuevoEstadio, rEstadioToString);
    }

    REstadio estadio = collGetAt<REstadio>(estadios, posEstadio, rEstadioFromString);

    estadio.partidosJugados++;
    if (res.codRes == 0) {
        estadio.partidosEmpatados++;
    }

    collSetAt<REstadio>(estadios, estadio, posEstadio, rEstadioToString);
}

int cmpREquipoREquipo(REquipo e1, REquipo e2) {
    return (e1.equipo.puntos + e1.puntosGanados) - (e2.equipo.puntos + e2.puntosGanados);
}

void mostrarPunto1(Coll<REquipo> equipos) {
    collSort<REquipo>(equipos, cmpREquipoREquipo, rEquipoFromString, rEquipoToString);

    collReset<REquipo>(equipos);

    while (collHasNext<REquipo>(equipos)) {
        REquipo eq = collNext<REquipo>(equipos, rEquipoFromString);
        int puntosTotales = eq.equipo.puntos + eq.puntosGanados;

        std::cout << eq.equipo.nombre << ": " << puntosTotales << endl;
    }
}

void mostrarPunto2(Coll<REstadio> estadios) {
    collReset<REstadio>(estadios);

    while (collHasNext<REstadio>(estadios)) {
        REstadio est = collNext<REstadio>(estadios, rEstadioFromString);

        std::cout << est.estadio << ": " << est.partidosJugados << " PJ, " << est.partidosEmpatados << " PE" << endl;
    }
}

void actualizarPunto3(Coll<REquipo> equipos) {
    FILE* f = fopen("EQUIPOS.dat", "w+b");

    collReset<REquipo>(equipos);

    while (collHasNext<REquipo>(equipos)) {
        REquipo e = collNext<REquipo>(equipos, rEquipoFromString);
        Equipo equipo = e.equipo;
        equipo.puntos += e.puntosGanados;

        write<Equipo>(f, equipo);
    }

    fclose(f);
}

int main() {
    Coll<REquipo> equipos = subirEquipos();
    Coll<REstadio> estadios = coll<REstadio>();

    FILE* f = fopen("RESULTADOS.dat", "r+b");
    Resultado res = read<Resultado>(f);
    while (!feof(f)) {
        procesarPunto1(res, equipos);
        procesarPunto2(res, estadios);

        res = read<Resultado>(f);
    }

    mostrarPunto1(equipos);
    actualizarPunto3(equipos);

    fclose(f);
    return 0;
}