#ifndef CLASES_H
#define CLASES_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class Avion
{
private:
  string vuelo;
  string modelo;
  string fabricante;
  int anoFabricacion;
  int capacidad;
  int pesoMaxDespegue;
  string aerolinea;
  string estado;
  Avion *siguiente;
  Avion *anterior;

public:
  string numeroRegistro;
  Avion(string vuelo, string numeroRegistro, string modelo, string fabricante, int anoFabricacion, int capacidad, int pesoMaxDespegue, string aerolinea, string estado);
  Avion *getSiguiente();
  Avion *getAnterior();
  void setSiguiente(Avion *siguiente);
  void setAnterior(Avion *anterior);
  void getDatos();
  string graficarDatos();
  ~Avion();
};

Avion::Avion(string vuelo, string numeroRegistro, string modelo, string fabricante, int anoFabricacion, int capacidad, int pesoMaxDespegue, string aerolinea, string estado)
{
  this->vuelo = vuelo;
  this->numeroRegistro = numeroRegistro;
  this->modelo = modelo;
  this->fabricante = fabricante;
  this->anoFabricacion = anoFabricacion;
  this->capacidad = capacidad;
  this->pesoMaxDespegue = pesoMaxDespegue;
  this->aerolinea = aerolinea;
  this->estado = estado;
  this->siguiente = nullptr;
  this->anterior = nullptr;
}

Avion *Avion::getSiguiente()
{
  return this->siguiente;
}

Avion *Avion::getAnterior()
{
  return this->anterior;
}

void Avion::setSiguiente(Avion *siguiente)
{
  this->siguiente = siguiente;
}

void Avion::setAnterior(Avion *anterior)
{
  this->anterior = anterior;
}

void Avion::getDatos()
{
  cout << "Vuelo: " << this->vuelo << ", No. Registro: " << this->numeroRegistro << ", Modelo: " << this->modelo << ", Fabricante: " << this->fabricante << endl;
}

string Avion::graficarDatos()
{
  stringstream ss;
  ss << "Vuelo: " << this->vuelo << "\n";
  ss << "No. Registro: " << this->numeroRegistro << "\n";
  ss << "Estado: " << this->estado;
  return ss.str();
}

Avion::~Avion()
{
}

class Pasajero
{
private:
  Pasajero *siguiente;
  Pasajero *anterior;

public:
  string nombre;
  string nacionalidad;
  string destino;
  string origen;
  string vuelo;
  string noPasaporte;
  int asiento;
  int equipajeFacturado;
  Pasajero(string nombre, string nacionalidad, string noPasaporte, string vuelo, int asiento, string destino, string origen, int equipajeFacturado);
  Pasajero *getSiguiente();
  Pasajero *getAnterior();
  void setSiguiente(Pasajero *siguiente);
  void setAnterior(Pasajero *anterior);
  bool tieneEquipaje();
  void getDatos();
  string graficarDatosListaDoble();
  string graficarDatosCola();
  string graficarDatosPila();
  ~Pasajero();
};

Pasajero::Pasajero(string nombre, string nacionalidad, string noPasaporte, string vuelo, int asiento, string destino, string origen, int equipajeFacturado)
{
  this->nombre = nombre;
  this->nacionalidad = nacionalidad;
  this->noPasaporte = noPasaporte;
  this->vuelo = vuelo;
  this->asiento = asiento;
  this->destino = destino;
  this->origen = origen;
  this->equipajeFacturado = equipajeFacturado;
  this->siguiente = nullptr;
  this->anterior = nullptr;
}

Pasajero *Pasajero::getSiguiente()
{
  return this->siguiente;
}

Pasajero *Pasajero::getAnterior()
{
  return this->anterior;
}

void Pasajero::setSiguiente(Pasajero *siguiente)
{
  this->siguiente = siguiente;
}

void Pasajero::setAnterior(Pasajero *anterior)
{
  this->anterior = anterior;
}

bool Pasajero::tieneEquipaje()
{
  if (this->equipajeFacturado > 0)
  {
    return true;
  }
  return false;
}

string Pasajero::graficarDatosListaDoble()
{
  stringstream ss;
  ss << "No. Pasaporte: " << this->noPasaporte << "\n";
  ss << "Nombre: " << this->nombre << "\n";
  ss << "Vuelo: " << this->vuelo << "\n";
  ss << "Asiento: " << this->asiento;
  return ss.str();
}

string Pasajero::graficarDatosCola()
{
  stringstream ss;
  ss << "No. Pasaporte: " << this->noPasaporte << "\n";
  ss << "Nombre: " << this->nombre;
  return ss.str();
}

string Pasajero::graficarDatosPila()
{
  stringstream ss;
  ss << "No. Pasaporte: " << this->noPasaporte << "\n";
  ss << "Nombre: " << this->nombre << "\n";
  ss << "Equipaje facturado: " << this->equipajeFacturado;
  return ss.str();
}

void Pasajero::getDatos()
{
  cout << "Nombre: " << this->nombre << ", Nacionalidad: " << this->nacionalidad << ", No. Pasaporte: " << this->noPasaporte << ", Vuelo: " << this->vuelo << endl;
}

Pasajero::~Pasajero()
{
}

#endif // CLASES_H
