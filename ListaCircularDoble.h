#ifndef LISTACIRCULARDOBLE_H
#define LISTACIRCULARDOBLE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
using namespace std;

#include "Clases.h"
#include "ListaCircularDoble.h"

class ListaCircularDoble
{
private:
  /* data */
  Avion *primero;
  Avion *ultimo;
  int tamano;

public:
  ListaCircularDoble(/* args */);
  bool estaVacia();
  void insertarInicio(Avion *nuevoAvion);
  void insertarFinal(Avion *nuevoAvion);
  void eliminarInicio();
  void eliminarFinal();
  Avion *buscarAvion(string numeroRegistro);
  Avion *eliminarAvion(Avion *avion);
  void visualizarListaDoble();
  void moverAvion(ListaCircularDoble &otraLista, Avion *avion);
  void generarReporteDispo();
  void generarReporteMante();
  int obtenerTamano();
  ~ListaCircularDoble();
};

ListaCircularDoble::ListaCircularDoble(/* args */)
{
  primero = nullptr;
  ultimo = nullptr;
  tamano = 0;
}

bool ListaCircularDoble::estaVacia()
{
  return (primero == nullptr) && (ultimo == nullptr);
}

void ListaCircularDoble::insertarInicio(Avion *nuevoAvion)
{
  if (ListaCircularDoble::estaVacia())
  {
    nuevoAvion->setAnterior(nuevoAvion);
    nuevoAvion->setSiguiente(nuevoAvion); // El primer nodo se apunta a si mismo
    primero = ultimo = nuevoAvion;
  }
  else
  {
    nuevoAvion->setSiguiente(primero); // Se enlaza el nuevo nodo al primero
    nuevoAvion->setAnterior(ultimo);
    ultimo->setSiguiente(nuevoAvion); // Se enlaza el ultimo nodo al nuevo
    primero->setAnterior(nuevoAvion);
    primero = nuevoAvion; // Se verifica que el nodo creado sea el primero
  }
  ++tamano;
}

void ListaCircularDoble::insertarFinal(Avion *nuevoAvion)
{
  nuevoAvion->setAnterior(nullptr);
  nuevoAvion->setSiguiente(nullptr);
  if (ListaCircularDoble::estaVacia())
  {
    nuevoAvion->setAnterior(nuevoAvion);
    nuevoAvion->setSiguiente(nuevoAvion);
    primero = ultimo = nuevoAvion;
  }
  else
  {
    nuevoAvion->setSiguiente(primero);
    nuevoAvion->setAnterior(ultimo);
    ultimo->setSiguiente(nuevoAvion);
    primero->setAnterior(nuevoAvion);
    ultimo = nuevoAvion;
  }
  ++tamano;
}

void ListaCircularDoble::eliminarInicio()
{
  if (ListaCircularDoble::estaVacia())
  {
    cout << "La lista está vacía." << endl;
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
      Avion *temp = primero->getSiguiente();
      ultimo->setSiguiente(temp);
      delete primero;
      primero = temp;
      primero->setAnterior(ultimo);
    }
    --tamano;
  }
}

Avion *ListaCircularDoble::buscarAvion(string numeroRegistro)
{
  if (primero == nullptr)
    return nullptr;
  Avion *actual = primero;
  do
  {
    if (actual->numeroRegistro == numeroRegistro)
    {
      return actual;
    }
    actual = actual->getSiguiente();
  } while (actual != primero);
  return nullptr;
}

Avion *ListaCircularDoble::eliminarAvion(Avion *avion)
{
  if (primero == nullptr || avion == nullptr)
    return nullptr;
  if (avion->getSiguiente() == avion)
  {
    primero = ultimo = nullptr;
  }
  else
  {
    Avion *anterior = avion->getAnterior();
    Avion *siguiente = avion->getSiguiente();
    anterior->setSiguiente(siguiente);
    siguiente->setAnterior(anterior);
    if (avion == primero)
    {
      primero = siguiente;
    }
  }
  --tamano;
  return avion;
}

void ListaCircularDoble::eliminarFinal()
{
  if (ListaCircularDoble::estaVacia())
  {
    cout << "La lista está vacía." << endl;
  }
  else
  {
    Avion *temp = primero;
    if (primero == ultimo)
    {
      delete primero;
      primero = ultimo = nullptr;
    }
    else
    {
      do
      {
        if (temp->getSiguiente() == ultimo)
        {
          delete ultimo;
          temp->setSiguiente(primero);
          primero->setAnterior(temp);
          ultimo = temp;
          break;
        }
        temp = temp->getSiguiente();
      } while (temp != primero);
    }
    --tamano;
  }
}

void ListaCircularDoble::moverAvion(ListaCircularDoble &otraLista, Avion *avion)
{
  if (avion != nullptr)
  {
    Avion *avion2 = this->eliminarAvion(avion);
    otraLista.insertarFinal(avion2);
  }
}

void ListaCircularDoble::visualizarListaDoble()
{
  if (ListaCircularDoble::estaVacia())
  {
    cout << "La lista está vacía."
         << endl;
  }
  else
  {
    Avion *actual = primero;
    do
    {
      actual->getDatos();
      actual = actual->getSiguiente();
    } while (actual != primero);
  }
}

void ListaCircularDoble::generarReporteDispo()
{
  if (!ListaCircularDoble::estaVacia())
  {
    ofstream archivo;
    archivo.open("reporteDisponibles.dot", ios::out);
    archivo << "digraph G { \n rankdir = LR;\n";

    if (primero)
    {
      Avion *actual = primero;
      do
      {
        archivo << "nodo" << actual << " [label=\"" << actual->graficarDatos() << "\"];\n";
        actual = actual->getSiguiente();
      } while (actual != primero);

      actual = primero;
      do
      {
        archivo << "nodo" << actual << " -> nodo" << actual->getSiguiente() << ";\n";
        archivo << "nodo" << actual->getSiguiente() << " -> nodo" << actual << ";\n";
        actual = actual->getSiguiente();
      } while (actual != primero);
    }

    archivo << "}";
    archivo.close();

    system("dot -Tpng reporteDisponibles.dot -o reporteDisponibles.png");
    system("start reporteDisponibles.png");
  }
}

void ListaCircularDoble::generarReporteMante()
{
  if (!ListaCircularDoble::estaVacia())
  {
    ofstream archivo;
    archivo.open("reporteMantenimiento.dot", ios::out);
    archivo << "digraph G { \n rankdir = LR;\n";

    if (primero)
    {
      Avion *actual = primero;
      do
      {
        archivo << "nodo" << actual << " [label=\"" << actual->graficarDatos() << "\"];\n";
        actual = actual->getSiguiente();
      } while (actual != primero);

      actual = primero;
      do
      {
        archivo << "nodo" << actual << " -> nodo" << actual->getSiguiente() << ";\n";
        archivo << "nodo" << actual->getSiguiente() << " -> nodo" << actual << ";\n";
        actual = actual->getSiguiente();
      } while (actual != primero);
    }

    archivo << "}";
    archivo.close();

    system("dot -Tpng reporteMantenimiento.dot -o reporteMantenimiento.png");
    system("start reporteMantenimiento.png");
  }
}

int ListaCircularDoble::obtenerTamano()
{
  return tamano;
}

ListaCircularDoble::~ListaCircularDoble()
{
}

#endif // LISTACIRCULARDOBLE_H
