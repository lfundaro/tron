#include "ModeloDatos.h"

using namespace std;

void Punto::Print() 
{
  cout << "Punto" << endl;
  cout << "x = " << x << endl;
  cout << "y = " << y << endl;
}

void Trayectoria::Print()
{
  cout << "Trayectoria" << endl;
  cout << "velocidad = " << velocidad << endl;
  cout << "numPuntos = " << numPuntos << endl;
  for(vector<Punto>::iterator it = listaPuntos.begin();
      it != listaPuntos.end(); ++it)
    {
      (*it).Print();
    }
}

void Objeto::Print()
{
  cout << "Objeto" << endl;
  cout << "Tipo = " << tipo << endl;
}

void ObjetoMaya::Print()
{
  cout << "ObjetoMaya" << endl;
  cout << "archivo = " << rutaArchivo << endl;
  p.Print();
}

void ObjetoCubo::Print()
{
  cout << "ObjetoCubo" << endl;
  cout << "tamaño = " << tamano << endl;
  p.Print();
}

void ObjetoEsfera::Print()
{
  cout << "ObjetoEsfera" << endl;
  p.Print();
  cout << "radio = " << radio << endl;
}

void Jugador::Print()
{
  cout << "Jugador" << endl;
  cout << "disparo = " << disparo << endl;
  t.Print();
}

void Nivel::Print()
{
  cout << "Nivel" << endl;
  cout << "ID = " << id << endl;
  cout << "Tiempo = " << tiempo << endl;
  j.Print();
  cout << "numContrincantes = " << numContrincantes << endl;
  cout << "Contrincantes" << endl;
  for(vector<Jugador>::iterator it = listaContrincantes.begin();
      it != listaContrincantes.end(); ++it)
    {
      (*it).Print();
    }
  cout << "NumObjetos = " << numObjetos << endl;
  for(vector<Objeto>::iterator it = listaObjetos.begin();
      it != listaObjetos.end(); ++it)
    {
      (*it).Print();
    }
}

void Juego::Print()
{
  cout << "Juego" << endl;
  cout << "NumNiveles = " << numNiveles << endl;
  for(vector<Nivel>::iterator it = listaNiveles.begin();
      it != listaNiveles.end(); ++it)
    {
      (*it).Print();
    }
}
