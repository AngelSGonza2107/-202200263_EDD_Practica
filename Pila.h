#ifndef PILA_H
#define PILA_H

#include <iostream>
using namespace std;

#include "Clases.h"

class Pila
{
private:
  /* data */
  Pasajero *primero;

public:
  Pila(/* args */);
  bool estaVacia();
  void apilar(Pasajero *pasajero);
  void desapilar();
  Pasajero *desapilar2();
  void visualizarPila();
  void generarReporte();
  ~Pila();
};

Pila::Pila(/* args */)
{
  primero = nullptr;
}

bool Pila::estaVacia()
{
  return primero == nullptr;
}

void Pila::apilar(Pasajero *pasajero)
{
  pasajero->setAnterior(nullptr);
  pasajero->setSiguiente(primero);
  primero = pasajero;
}

void Pila::desapilar()
{
  if (primero == nullptr)
  {
    cout << "La pila está vacía." << endl;
  }
  Pasajero *temp = primero;
  primero = primero->getSiguiente();
  temp->setSiguiente(nullptr);
  delete temp;
}

Pasajero *Pila::desapilar2()
{
  if (primero == nullptr)
  {
    return nullptr;
  }
  Pasajero *temp = primero;
  primero = primero->getSiguiente();
  temp->setSiguiente(nullptr);
  return temp;
}

void Pila::visualizarPila()
{
  if (Pila::estaVacia())
  {
    cout << "La cola está vacía\n"
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

void Pila::generarReporte()
{
  if (!Pila::estaVacia())
  {
    ofstream archivo;
    archivo.open("reporteEquipaje.dot", ios::out);
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

    system("dot -Tpng reporteEquipaje.dot -o reporteEquipaje.png");
    system("start reporteEquipaje.png");
  }
}

Pila::~Pila()
{
}

#endif // PILA_H
