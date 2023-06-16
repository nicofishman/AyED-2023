#include <bits/stdc++.h>

#include "../biblioteca/funciones/files.hpp"
#include "../biblioteca/funciones/strings.hpp"
#include "../biblioteca/funciones/tokens.hpp"
#include "../biblioteca/tads/Coll.hpp"
#include "principal.hpp"

Coll<Producto> subirProductos() {
	FILE *f = fopen("PRODUCTOS.dat", "r+b");

	Coll<Producto> productos = coll<Producto>();
	Producto p = read<Producto>(f);

	while (!feof(f)) {
		collAdd<Producto>(productos, p, productoToString);
		read<Producto>(f);
	}

	fclose(f);

	return productos;
}

Coll<Rubro> subirRubros() {
	FILE *f = fopen("RUBROS.dat", "r+b");

	Coll<Rubro> rubros = coll<Rubro>();
	Rubro r = read<Rubro>(f);

	while (!feof(f)) {
		collAdd<Rubro>(rubros, r, rubroToString);
		read<Rubro>(f);
	}

	fclose(f);

	return rubros;
}

int cmpItemItem(Item i1, Item i2) {
	return cmpString(i1.prodcuto.descr, i2.prodcuto.descr);
}

void emitirTickets(Coll<Compra> compras, Coll<Producto> productos, Coll<Rubro> rubros) {

	collReset<Compra>(compras);
	Compra com = collNext<Compra>(compras, compraFromString);
	while (!collHasNext<Compra>(compras)) {
		collSort<Item>(com.items, cmpItemItem, itemFromString, itemToString);

		Compra com = collNext<Compra>(compras, compraFromString);
	}

}

int main() {
	Coll<Producto> productos = subirProductos();
	Coll<Rubro> rubros = subirRubros();

	Coll<Compra> compras = coll<Compra>();

	emitirTickets(compras, productos, rubros);
}
