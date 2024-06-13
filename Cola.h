#ifndef COLA_H
#define COLA_H

#include <iostream>
using namespace std;

#include "Clases.h"

class Cola
{
private:
  /* data */
  Pasajero *primero;
  Pasajero *ultimo;

public:
  Cola(/* args */);
  bool estaVacia();
  Pasajero *getPrimero();
  void encolar(Pasajero *nuevoPasajero);
  void desencolar();
  Pasajero *desencolar2();
  void visualizarCola();
  void generarReporte();
  ~Cola();
};

Cola::Cola(/* args */)
{
  primero = nullptr;
  ultimo = nullptr;
}

bool Cola::estaVacia()
{
  return (primero == nullptr) && (ultimo == nullptr);
}

void Cola::encolar(Pasajero *nuevoPasajero)
{
  nuevoPasajero->setSiguiente(nullptr);
  nuevoPasajero->setAnterior(nullptr);
  if (ultimo == nullptr)
  {
    primero = ultimo = nuevoPasajero;
  }
  else
  {
    ultimo->setSiguiente(nuevoPasajero);
    ultimo = nuevoPasajero;
  }
}

Pasajero *Cola::getPrimero()
{
  return primero;
}

void Cola::desencolar()
{
  if (primero == nullptr)
  {
    cout << "La cola está vacía." << endl;
  }
  Pasajero *temp = primero;
  primero = primero->getSiguiente();
  if (primero == nullptr)
  {
    ultimo = nullptr;
  }
  temp->setSiguiente(nullptr);
  delete temp;
}

Pasajero *Cola::desencolar2()
{
  if (primero == nullptr)
  {
    return nullptr;
  }
  Pasajero *temp = primero;
  primero = primero->getSiguiente();
  if (primero == nullptr)
  {
    ultimo = nullptr;
  }
  temp->setSiguiente(nullptr);
  return temp;
}

void Cola::visualizarCola()
{
  if (Cola::estaVacia())
  {
    cout << "La cola está vacía."
         << endl;
  }
  else
  {
    Pasajero *actual = primero;
    while (actual != nullptr)
    {
      actual->getDatos();
      actual = actual->getSiguiente();
    }
  }
}

void Cola::generarReporte()
{
  if (!Cola::estaVacia())
  {
    ofstream archivo;
    archivo.open("reporteColaPasajeros.dot", ios::out);
    archivo << "digraph G { \n rankdir = LR;\n";

    Pasajero *actual = primero;
    while (actual)
    {
      archivo << "nodo" << actual << " [label=\"" << actual->graficarDatosCola() << "\"];\n";
      if (actual->getSiguiente())
      {
        archivo << "nodo" << actual << " -> nodo" << actual->getSiguiente() << ";\n";
      }
      actual = actual->getSiguiente();
    }

    archivo << "}";
    archivo.close();

    system("dot -Tpng reporteColaPasajeros.dot -o reporteColaPasajeros.png");
    system("start reporteColaPasajeros.png");
  }
}

Cola::~Cola()
{
}

#endif // COLA_H
