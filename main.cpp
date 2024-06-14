#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <cstdio>
#include <windows.h>
#include <algorithm>
using namespace std;

#include "ListaCircularDoble.h"
#include "ListaDoble.h"
#include "Cola.h"
#include "Pila.h"
#include "Clases.h"

int opcion;

string linea;
string filename;
string textoAviones;
string textoPasajeros;
string textoMovimientos;

ListaCircularDoble listaDisponibles;
ListaCircularDoble listaMantenimiento;
ListaDoble listaPasajeros;
Cola colaPasajeros;
Pila pilaEquipaje;

void cargarAviones(const string &filename, ListaCircularDoble &listaDisponibles, ListaCircularDoble &listaMantenimiento)
{
  ifstream archivo(filename);
  if (archivo.is_open())
  {
    string linea;

    string vuelo;
    string numeroRegistro;
    string modelo;
    string fabricante;
    int anoFabricacion;
    int capacidad;
    int pesoMaxDespegue;
    string aerolinea;
    string estado;

    while (getline(archivo, linea))
    {
      size_t pos = linea.find(":");
      if (pos != string::npos)
      {
        string key = linea.substr(0, pos);
        string value = linea.substr(pos + 1);

        key.erase(remove(key.begin(), key.end(), ' '), key.end());
        key.erase(remove(key.begin(), key.end(), '\"'), key.end());
        key.erase(remove(key.begin(), key.end(), '\t'), key.end());
        value.erase(0, 1);
        value.erase(remove(value.begin(), value.end(), '\"'), value.end());
        value.erase(remove(value.begin(), value.end(), ','), value.end());

        if (key == "vuelo")
        {
          vuelo = value;
        }
        else if (key == "numero_de_registro")
        {
          numeroRegistro = value;
        }
        else if (key == "modelo")
        {
          modelo = value;
        }
        else if (key == "fabricante")
        {
          fabricante = value;
        }
        else if (key == "ano_fabricacion")
        {
          anoFabricacion = stoi(value);
        }
        else if (key == "capacidad")
        {
          capacidad = stoi(value);
        }
        else if (key == "peso_max_despegue")
        {
          pesoMaxDespegue = stoi(value);
        }
        else if (key == "aerolinea")
        {
          aerolinea = value;
        }
        else if (key == "estado")
        {
          estado = value;
        }
      }
      else if (linea.find("}") != string::npos)
      {
        Avion *nuevoAvion = new Avion(vuelo, numeroRegistro, modelo, fabricante, anoFabricacion, capacidad, pesoMaxDespegue, aerolinea, estado);
        if (estado == "Disponible")
        {
          listaDisponibles.insertarFinal(nuevoAvion);
        }
        else if (estado == "Mantenimiento")
        {
          listaMantenimiento.insertarFinal(nuevoAvion);
        }
      }
    }
    cout << "Archivo de aviones cargado exitosamente." << endl;
    archivo.close();
  }
  else
  {
    cerr << "No se pudo abrir el archivo para leer." << endl;
  }
}

void cargarPasajeros(const string &filename, Cola &colaPasajeros)
{
  ifstream archivo(filename);
  if (archivo.is_open())
  {
    string linea;

    string nombre;
    string nacionalidad;
    string noPasaporte;
    string vuelo;
    int asiento;
    string destino;
    string origen;
    int equipajeFacturado;

    while (getline(archivo, linea))
    {
      size_t pos = linea.find(":");
      if (pos != string::npos)
      {
        string key = linea.substr(0, pos);
        string value = linea.substr(pos + 1);

        key.erase(remove(key.begin(), key.end(), ' '), key.end());
        key.erase(remove(key.begin(), key.end(), '\"'), key.end());
        key.erase(remove(key.begin(), key.end(), '\t'), key.end());
        value.erase(0, 1);
        value.erase(remove(value.begin(), value.end(), '\"'), value.end());
        value.erase(remove(value.begin(), value.end(), ','), value.end());

        if (key == "nombre")
        {
          nombre = value;
        }
        else if (key == "nacionalidad")
        {
          nacionalidad = value;
        }
        else if (key == "numero_de_pasaporte")
        {
          noPasaporte = value;
        }
        else if (key == "vuelo")
        {
          vuelo = value;
        }
        else if (key == "asiento")
        {
          asiento = stoi(value);
        }
        else if (key == "destino")
        {
          destino = value;
        }
        else if (key == "origen")
        {
          origen = value;
        }
        else if (key == "equipaje_facturado")
        {
          equipajeFacturado = stoi(value);
        }
      }
      else if (linea.find("}") != string::npos)
      {
        Pasajero *nuevoPasajero = new Pasajero(nombre, nacionalidad, noPasaporte, vuelo, asiento, destino, origen, equipajeFacturado);
        colaPasajeros.encolar(nuevoPasajero);
      }
    }
    cout << "Archivo de pasajeros cargado exitosamente." << endl;
    archivo.close();
  }
  else
  {
    cerr << "No se pudo abrir el archivo para leer." << endl;
  }
}

void cargarMovimientos(const string &filename, ListaCircularDoble &listaDisponibles, ListaCircularDoble &listaMantenimiento)
{
  ifstream file(filename);
  if (file.is_open())
  {
    string linea;
    while (getline(file, linea))
    {
      stringstream ss(linea);
      string comando, accion, numeroRegistro;

      getline(ss, comando, ',');

      if (comando == "MantenimientoAviones")
      {
        getline(ss, accion, ',');
        getline(ss, numeroRegistro, ';');
        if (accion == "Ingreso")
        {
          Avion *test = listaDisponibles.buscarAvion(numeroRegistro);
          if (test != nullptr)
          {
            test->estado = "Mantenimiento";
            listaDisponibles.moverAvion(listaMantenimiento, test);
            cout << "Avion " << numeroRegistro << " movido a Mantenimiento." << endl;
          }
          else
          {
            cout << "No fue posible encontrar el avion " << numeroRegistro << " en la lista de aviones disponibles." << endl;
          }
        }
        else if (accion == "Salida")
        {
          Avion *test = listaMantenimiento.buscarAvion(numeroRegistro);
          if (test != nullptr)
          {
            test->estado = "Disponible";
            listaMantenimiento.moverAvion(listaDisponibles, test);
            cout << "Avion " << numeroRegistro << " movido a Disponible." << endl;
          }
          else
          {
            cout << "No fue posible encontrar el avion " << numeroRegistro << " en la lista de aviones en mantenimiento." << endl;
          }
        }
      }
      else if (comando == "IngresoEquipajes;")
      {
        if (!colaPasajeros.estaVacia())
        {
          Pasajero *pasajero = colaPasajeros.desencolar2();
          if (pasajero->equipajeFacturado > 0)
          {
            Pasajero *pasajero2 = new Pasajero(pasajero->nombre, pasajero->nacionalidad, pasajero->noPasaporte, pasajero->vuelo, pasajero->asiento, pasajero->destino, pasajero->origen, pasajero->equipajeFacturado);
            pilaEquipaje.apilar(pasajero2);
          }
          listaPasajeros.insertarOrdenado(pasajero);
        }
      }
    }
    cout << "Movimientos cargados exitosamente al sistema." << endl;
    file.close();
  }
  else
  {
    cerr << "Error al abrir el archivo de movimientos. " << endl;
  }
}

void consultarPasajero(ListaDoble &listaPasajeros)
{
  if (listaPasajeros.estaVacia())
  {
    cout << "La lista de pasajeros está vacía." << endl;
    return;
  }

  string noPasaporte;
  cout << "Ingrese el número de pasaporte: ";
  cin >> noPasaporte;

  Pasajero *pasajero = listaPasajeros.buscarPasajero(noPasaporte);
  if (pasajero)
  {
    cout << "Nombre: " << pasajero->nombre << endl;
    cout << "Pasaporte: " << pasajero->noPasaporte << endl;
    cout << "Número de Vuelo: " << pasajero->vuelo << endl;
    cout << "Número de Asiento: " << pasajero->asiento << endl;
    cout << "Tiene Equipaje: " << (pasajero->tieneEquipaje() ? "Sí" : "No") << endl;
  }
  else
  {
    cout << "No se encontró un pasajero con ese número de pasaporte." << endl;
  }
}

void generarReportes(ListaCircularDoble &listaDisponibles, ListaCircularDoble &listaMantenimiento, ListaDoble &listaPasajeros, Cola &colaPasajeros, Pila &pilaEquipaje)
{
  listaDisponibles.generarReporteDispo();
  listaMantenimiento.generarReporteMante();
  listaPasajeros.generarReporte();
  colaPasajeros.generarReporte();
  pilaEquipaje.generarReporte();
}

void mostrarMenu()
{
  cout << endl;
  cout << "---------- MENU ----------" << endl;
  cout << "  1. Carga de aviones" << endl;
  cout << "  2. Carga de pasajeros" << endl;
  cout << "  3. Carga de movimientos" << endl;
  cout << "  4. Consultar pasajero" << endl;
  cout << "  5. Visualizar reportes" << endl;
  cout << "  6. Salir \n"
       << endl;
  cout << "Elija la opcion que desee realizar: ";
}

int main()
{
  int opcion;
  do
  {
    mostrarMenu();
    cin >> opcion;

    switch (opcion)
    {
    case 1:
    {
      cout << "Ingrese la ruta del archivo JSON para la carga de aviones: ";
      string rutaAviones;
      cin >> rutaAviones;
      cargarAviones(rutaAviones, listaDisponibles, listaMantenimiento);
    }
    break;
    case 2:
    {
      cout << "Ingrese la ruta del archivo JSON para la carga de pasajeros: ";
      string rutaPasajeros;
      cin >> rutaPasajeros;
      cargarPasajeros(rutaPasajeros, colaPasajeros);
    }
    break;
    case 3:
    {
      cout << "Ingrese la ruta del archivo para la carga de movimientos: ";
      string rutaMovimientos;
      cin >> rutaMovimientos;
      cargarMovimientos(rutaMovimientos, listaDisponibles, listaMantenimiento);
    }
    break;
    case 4:
    {
      consultarPasajero(listaPasajeros);
    }
    break;
    case 5:
    {
      generarReportes(listaDisponibles, listaMantenimiento, listaPasajeros, colaPasajeros, pilaEquipaje);
    }
    break;
    case 6:
      cout << "Saliendo..." << endl;
      exit(EXIT_SUCCESS);
      break;
    default:
      cout << " -- La opcion elegida no es valida. \n"
           << endl;
      Sleep(600);
      break;
    }
    cin.clear();
  } while (opcion != 6);
  return 0;
}
