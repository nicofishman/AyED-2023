#ifndef _MAINHPP
#define _MAINHPP
#include <iostream>
#include <iostream>
#include <sstream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include "../biblioteca/funciones/strings.hpp"
#include "../biblioteca/funciones/tokens.hpp"
#include "../biblioteca/tads/Coll.hpp"
using namespace std;

struct Producto
{
	int idProd;
	char descr[20];
	double precio;
	int idRub;
};

struct Rubro
{
	int idRub;
	char descr[20];
	double promo;
};

struct Item
{
	Producto prodcuto;
	int cant;
};

struct Compra
{
	int idCli;
	Coll<Item> items;
};

string productoToString(Producto x)
{
	char sep = 1;
	string sIdProd=to_string(x.idProd);
	string sDescr=x.descr;
	string sPrecio=to_string(x.precio);
	string sIdRub=to_string(x.idRub);
	return sIdProd+sep+sDescr+sep+sPrecio+sep+sIdRub;
}

Producto productoFromString(string s)
{
	char sep = 1;
	Producto x;
	string t0 = getTokenAt(s,sep,0);
	x.idProd=stoi(t0);
	string t1 = getTokenAt(s,sep,1);
	strcpy(x.descr,t1.c_str());
	string t2 = getTokenAt(s,sep,2);
	x.precio=stod(t2);
	string t3 = getTokenAt(s,sep,3);
	x.idRub=stoi(t3);
	return x;
}

string productoToDebug(Producto x)
{
	stringstream sout;
	sout<< "[";
	sout << x.idProd;
	sout << ",";
	sout << x.descr;
	sout << ",";
	sout << x.precio;
	sout << ",";
	sout << x.idRub;
	sout<< "]";
	return sout.str();
}

string productoToDebug(string mssg,Producto x)
{
	stringstream sout;
	sout<< mssg<<":[";
	sout << x.idProd;
	sout << ",";
	sout << x.descr;
	sout << ",";
	sout << x.precio;
	sout << ",";
	sout << x.idRub;
	sout<< "]";
	return sout.str();
}

Producto producto(int idProd,string descr,double precio,int idRub)
{
	Producto a;
	a.idProd = idProd;
	strcpy(a.descr,descr.c_str());
	a.precio = precio;
	a.idRub = idRub;
	return a;
}

bool productoEquals(Producto a,Producto b)
{
	if(a.idProd!=b.idProd) return false;
	if(a.precio!=b.precio) return false;
	if(a.idRub!=b.idRub) return false;
	return true;
}

string rubroToString(Rubro x)
{
	char sep = 2;
	string sIdRub=to_string(x.idRub);
	string sDescr=x.descr;
	string sPromo=to_string(x.promo);
	return sIdRub+sep+sDescr+sep+sPromo;
}

Rubro rubroFromString(string s)
{
	char sep = 2;
	Rubro x;
	string t0 = getTokenAt(s,sep,0);
	x.idRub=stoi(t0);
	string t1 = getTokenAt(s,sep,1);
	strcpy(x.descr,t1.c_str());
	string t2 = getTokenAt(s,sep,2);
	x.promo=stod(t2);
	return x;
}

string rubroToDebug(Rubro x)
{
	stringstream sout;
	sout<< "[";
	sout << x.idRub;
	sout << ",";
	sout << x.descr;
	sout << ",";
	sout << x.promo;
	sout<< "]";
	return sout.str();
}

string rubroToDebug(string mssg,Rubro x)
{
	stringstream sout;
	sout<< mssg<<":[";
	sout << x.idRub;
	sout << ",";
	sout << x.descr;
	sout << ",";
	sout << x.promo;
	sout<< "]";
	return sout.str();
}

Rubro rubro(int idRub,string descr,double promo)
{
	Rubro a;
	a.idRub = idRub;
	strcpy(a.descr,descr.c_str());
	a.promo = promo;
	return a;
}

bool rubroEquals(Rubro a,Rubro b)
{
	if(a.idRub!=b.idRub) return false;
	if(a.promo!=b.promo) return false;
	return true;
}

string itemToString(Item x)
{
	char sep = 3;
	string sProdcuto=productoToString(x.prodcuto);
	string sCant=to_string(x.cant);
	return sProdcuto+sep+sCant;
}

Item itemFromString(string s)
{
	char sep = 3;
	Item x;
	string t0 = getTokenAt(s,sep,0);
	x.prodcuto=productoFromString(t0);
	string t1 = getTokenAt(s,sep,1);
	x.cant=stoi(t1);
	return x;
}

string itemToDebug(Item x)
{
	stringstream sout;
	sout<< "[";
	sout << productoToDebug(x.prodcuto);
	sout << ",";
	sout << x.cant;
	sout<< "]";
	return sout.str();
}

string itemToDebug(string mssg,Item x)
{
	stringstream sout;
	sout<< mssg<<":[";
	sout << productoToDebug(x.prodcuto);
	sout << ",";
	sout << x.cant;
	sout<< "]";
	return sout.str();
}

Item item(Producto prodcuto,int cant)
{
	Item a;
	a.prodcuto = prodcuto;
	a.cant = cant;
	return a;
}

bool itemEquals(Item a,Item b)
{
	if(!productoEquals(a.prodcuto,b.prodcuto)) return false;
	if(a.cant!=b.cant) return false;
	return true;
}

string compraToString(Compra x)
{
	char sep = 4;
	string sIdCli=to_string(x.idCli);
	string sItems=collToString<Item>(x.items);
	return sIdCli+sep+sItems;
}

Compra compraFromString(string s)
{
	char sep = 4;
	Compra x;
	string t0 = getTokenAt(s,sep,0);
	x.idCli=stoi(t0);
	string t1 = getTokenAt(s,sep,1);
	x.items = collFromString<Item>(t1);
	return x;
}

string compraToDebug(Compra x)
{
	stringstream sout;
	sout<< "[";
	sout << x.idCli;
	sout << ",";
	collReset<Item>(x.items);
	int n=collSize<Item>(x.items);
	sout << "{";
	for(int i=0; i<n; i++)
	{
		Item q = collGetAt<Item>(x.items,i,itemFromString);
		sout << itemToDebug(q) << ((i<n-1)?",":"");
	}
	sout << "}";
	sout<< "]";
	return sout.str();
}

string compraToDebug(string mssg,Compra x)
{
	stringstream sout;
	sout<< mssg<<":[";
	sout << x.idCli;
	sout << ",";
	collReset<Item>(x.items);
	int n=collSize<Item>(x.items);
	sout << "{";
	for(int i=0; i<n; i++)
	{
		Item q = collGetAt<Item>(x.items,i,itemFromString);
		sout << itemToDebug(q) << ((i<n-1)?",":"");
	}
	sout << "}";
	sout<< "]";
	return sout.str();
}

Compra compra(int idCli,Coll<Item> items)
{
	Compra a;
	a.idCli = idCli;
	a.items = items;
	return a;
}

bool compraEquals(Compra a,Compra b)
{
	if(a.idCli!=b.idCli) return false;
	if(collToString<Item>(a.items)!=collToString<Item>(b.items)) return false;
	return true;
}

#endif
