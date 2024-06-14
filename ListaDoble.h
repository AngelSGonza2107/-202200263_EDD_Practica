#ifndef LISTADOBLE_H
#define LISTADOBLE_H

#include <iostream>
using namespace std;

#include "Clases.h"

class ListaDoble
{
private:
  /* data */
  Pasajero *primero;
  Pasajero *ultimo;

public:
  ListaDoble(/* args */);
  bool estaVacia();
  void insertarInicio(Pasajero *nuevoPasajero);
  void insertarFinal(Pasajero *nuevoPasajero);
  void insertarOrdenado(Pasajero *pasajero);
  void eliminarInicio();
  void eliminarFinal();
  Pasajero *buscarPasajero(string noPasaporte);
  void visualizarLista();
  void generarReporte();
  ~ListaDoble();
};

ListaDoble::ListaDoble(/* args */)
{
  primero = nullptr;
  ultimo = nullptr;
}

bool ListaDoble::estaVacia()
{
  return (primero == nullptr) && (ultimo == nullptr);
}

void ListaDoble::insertarInicio(Pasajero *nuevoPasajero)
{
  if (ListaDoble::estaVacia())
  {
    primero = ultimo = nuevoPasajero;
  }
  else
  {
    primero->setAnterior(nuevoPasajero);  // Se enlaza el primer nodo al nuevo
    nuevoPasajero->setSiguiente(primero); // Se enlaza el nuevo nodo al primero
    primero = nuevoPasajero;              // Se verifica que el nodo creado sea el primero
  }
}

void ListaDoble::insertarFinal(Pasajero *nuevoPasajero)
{
  if (ListaDoble::estaVacia())
  {
    primero = ultimo = nuevoPasajero;
  }
  else
  {
    ultimo->setSiguiente(nuevoPasajero); // Se enlaza el �ltimo nodo al nuevo
    nuevoPasajero->setAnterior(ultimo);  // Se enlaza el nuevo nodo al �ltimo
    ultimo = nuevoPasajero;              // Se verfica que el nodo creado sea el �ltimo
  }
}

void ListaDoble::insertarOrdenado(Pasajero *pasajero)
{
  pasajero->setAnterior(nullptr);
  pasajero->setSiguiente(nullptr);
  if (ListaDoble::estaVacia())
  {
    primero = ultimo = pasajero;
    return;
  }
  Pasajero *actual = primero;
  while (actual != nullptr)
  {
    int vueloActual = stoi(actual->vuelo.substr(1));
    int vueloPasajero = stoi(pasajero->vuelo.substr(1));
    if (vueloActual < vueloPasajero || (actual->vuelo == pasajero->vuelo && actual->asiento < pasajero->asiento))
    {
      pasajero->setSiguiente(actual);
      pasajero->setAnterior(actual->getAnterior());
      if (actual->getAnterior() != nullptr)
      {
        actual->getAnterior()->setSiguiente(pasajero);
      }
      else
      {
        primero = pasajero;
      }
      actual->setAnterior(pasajero);
      return;
    }
    if (actual->getSiguiente() == nullptr)
    {
      actual->setSiguiente(pasajero);
      pasajero->setAnterior(actual);
      ultimo = pasajero;
      return;
    }
    actual = actual->getSiguiente();
  }
}

void ListaDoble::eliminarInicio()
{
  if (ListaDoble::estaVacia())
  {
    cout << "La lista está vacía" << endl;
  }
  else
  {
    if (primero == ultimo)
    {
      delete primero;
      primero = ultimo = nullptr;
    }
    else
    {
      Pasajero *segundo = primero->getSiguiente();
      segundo->setAnterior(nullptr);
      delete primero;
      primero = segundo;
    }
  }
}

void ListaDoble::eliminarFinal()
{
  if (ListaDoble::estaVacia())
  {
    cout << "La lista está vacía" << endl;
  }
  else
  {
    if (primero == ultimo)
    {
      /* code */
      delete primero;
      primero = ultimo = nullptr;
    }
    else
    {
      Pasajero *antepenultimo = ultimo->getAnterior(); // Guardo la refencia del antepenultimo nodo
      delete ultimo;
      antepenultimo->setSiguiente(nullptr);
      ultimo = antepenultimo;
    }
  }
}

Pasajero *ListaDoble::buscarPasajero(string noPasaporte)
{
  Pasajero *actual = primero;
  while (actual != nullptr)
  {
    if (actual->noPasaporte == noPasaporte)
    {
      return actual;
    }
    actual = actual->getSiguiente();
  }
  return nullptr;
}

void ListaDoble::visualizarLista()
{
  if (ListaDoble::estaVacia())
  {
    cout << "La lista está vacía\n"
         << endl;
  }
  else
  {
    Pasajero *actual = ultimo;
    while (actual != nullptr)
    {
      actual->getDatos();
      cout << endl;
      actual = actual->getAnterior();
    }
  }
}

void ListaDoble::generarReporte()
{
  if (!ListaDoble::estaVacia())
  {
    ofstream archivo;
    archivo.open("reportePasajeros.dot", ios::out);
    archivo << "digraph G { \n rankdir = LR;\n";

    Pasajero *actual = primero;
    while (actual)
    {
      archivo << "nodo" << actual << " [label=\"" << actual->graficarDatosListaDoble() << "\"];\n";
      if (actual->getSiguiente())
      {
        archivo << "nodo" << actual << " -> nodo" << actual->getSiguiente() << ";\n";
        archivo << "nodo" << actual->getSiguiente() << " -> nodo" << actual << ";\n";
      }
      actual = actual->getSiguiente();
    }

    archivo << "}";
    archivo.close();

    system("dot -Tpng reportePasajeros.dot -o reportePasajeros.png");
    system("start reportePasajeros.png");
  }
}

ListaDoble::~ListaDoble()
{
}

#endif // LISTADOBLE_H
