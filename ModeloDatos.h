#ifndef MODELODATOS_H
#define MODELODATOS_H

#include <vector>

using namespace std;

enum tipoObjeto {MAYA, CUBO, NODEF};

class Punto
{
 public:
  int x;
  int y;

  // Constructor por defecto
  Punto() 
    {
      x = 0;
      y = 0;
    }

  // Constructor
  Punto(int a, int b)
    {
      x = a;
      y = b;
    }
};

class Trayectoria
{
 public:
  int velocidad;
  int numPuntos;
  vector<Punto> listaPuntos;

  // Constructor por defecto
  Trayectoria()
    {
      velocidad = 0;
      numPuntos = 0;
      listaPuntos = vector<Punto>();
    }

  Trayectoria(int vel, int npuntos, int tamLista)
    {
      velocidad = vel;
      numPuntos = npuntos;
      listaPuntos = vector<Punto>(tamLista, Punto());
    }
};

class Objeto
{
 public:
  enum tipoObjeto tipo;

  Objeto()
    {
      tipo = NODEF;
    }

  Objeto(enum tipoObjeto t) 
    {
      tipo = t;
    }
};

class ObjetoMaya: public Objeto
{
 public:
  char *rutaArchivo;
  Punto p;

 ObjetoMaya() : Objeto(), rutaArchivo(NULL), p(Punto()) {}

  ObjetoMaya(enum tipoObjeto t, char *nArchivo, 
             Punto x) : Objeto(t), rutaArchivo(nArchivo),
    p(x) {}
};

class ObjetoCubo: public Objeto
{
 public:
  int tamano;
  Punto p;
  
 ObjetoCubo() : Objeto(), tamano(0), p(Punto()) {}

 ObjetoCubo(enum tipoObjeto t, int tam, Punto x) :
  Objeto(t), tamano(tam), p(x) {}
};

class Jugador
{
 public:
  double disparo;
  Trayectoria t;

  Jugador() 
    {
      disparo = 0.0;
      t = Trayectoria();
    }

  Jugador(double d, Trayectoria tr)
    {
      disparo = d;
      t = tr;
    }
};

class Contrincante : public Jugador
{
 public:

 Contrincante() : Jugador() {}

 Contrincante(double d, Trayectoria tr) : Jugador(d,tr) {}
};

class Nivel
{
 public:
  int id;
  int tiempo;
  Jugador j;
  int numContrincantes;
  vector<Contrincante> listaContrincantes;
  int numObjetos;
  vector<Objeto> listaObjetos;

  Nivel() 
    {
      id = 0;
      tiempo = 0;
      j = Jugador();
      numContrincantes = 0;
      listaContrincantes = vector<Contrincante>();
      numObjetos = 0;
      listaObjetos = vector<Objeto>();
    }
  
  Nivel(int ident, int t, Jugador jug, int nContr, 
        int nObjetos)
    {
      id = ident;
      tiempo = t;
      jug = j;
      numContrincantes = nContr;
      listaContrincantes = vector<Contrincante>(nContr, Contrincante());
      listaObjetos = vector<Objeto>(numObjetos, Objeto());
    }
};

class Juego
{
 public:
  int numNiveles;
  vector<Nivel> listaNiveles;

  Juego()
    {
      numNiveles = 0;
      listaNiveles = vector<Nivel>();
    }

  Juego(int nNiveles)
    {
      numNiveles = nNiveles;
      listaNiveles = vector<Nivel>(nNiveles, Nivel());
    }
};

#endif


/* struct Nivel */
/* { */
/*   int id; */
/*   int tiempo; */
/*   Jugador j; */
/*   int numContrincantes; */
/*   ListaContrincantes *listaContrincantes; */
/*   int numObjetos; */
/*   ListaObjetos *listaObjetos; */
/* }; */


/* struct Jugador  */
/* { */
/*   double disparo; */
/*   Trayectoria t; */
/* }; */


/* struct ListaNiveles */
/* { */
/*   Nivel x; */
/*   ListaNiveles *next; */
/* }; */

/* struct Juego  */
/* { */
/*   int numNiveles; */
/*   ListaNiveles *niveles; */
/* }; */


/* struct ObjetoMaya  */
/* { */
/*   enum tipoObjeto tipo; */
/*   char *rutaArchivo; */
/*   Punto p; */
/* }; */

/* struct ObjetoCubo */
/* { */
/*   enum tipoObjeto tipo; */
/*   Punto p; */
/*   int tamano; */
/* }; */

/* union Objeto */
/* { */
/*   struct ObjetoMaya om; */
/*   struct ObjetoCubo oc; */
/* }; */

/* struct ListaObjetos */
/* { */
/*   Objeto obj; */
/*   Objeto *next; */
/* }; */


/* struct Contrincante */
/* { */
/*   double disparo; */
/*   Trayectoria t; */
/* }; */


/* struct ListaContrincantes */
/* { */
/*   Contrincante x; */
/*   Contrincante *next; */
/* }; */



/* struct Punto */
/* { */
/*   int x; */
/*   int y; */
/* }; */



/* struct Trayectoria */
/* { */
/*   int velocidad; */
/*   int numPuntos; */
/*   vector<Punto> listaPuntos; */
/* }; */
