#ifndef MODELODATOS_H
#define MODELODATOS_H

#include <vector>
#include <stdlib.h>
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include <time.h>

#define RAD_INT_TORUS 1.0
#define RAD_EXT_TORUS 2.0

using namespace std;

enum tipoObjeto {MAYA, CUBO, ESFERA, NODEF};

class Punto
{
 public:
  double x;
  double y;

  // Constructor por defecto
  Punto() 
    {
      x = 0;
      y = 0;
    }

  // Constructor
  Punto(double a, double b)
    {
      x = a;
      y = b;
    }
  
  double getX();
  double getY();
  void setX(double val);
  void setY(double val);
  void Print();
};

class Disco 
{
 public:
  int tiroDirecto; 
  int vida; 
  int enCurso;
  Punto posActual;

  Disco() 
    {
      tiroDirecto = 1;
      vida = 15;
      enCurso = 0;
      posActual = Punto();
    }
  
  Disco(Punto pos) 
    {
      tiroDirecto = 1;
      vida = 15;
      enCurso = 0;
      posActual = pos;
    }

  void decVida();
  void cambiarModo();
  void dibujarDisco(Punto posActual);
};

class Trayectoria
{
 public:
  double velocidad;
  int numPuntos;
  vector<Punto> listaPuntos;
  int origen;
  double pendiente;
  double x_1;
  double y_1;
  double lambdaX;
  double lambdaY;
  time_t timeStamp;

  // Constructor por defecto
  Trayectoria()
    {
      velocidad = 0.0;
      numPuntos = 0;
      listaPuntos = vector<Punto>();
      origen = 0;
      x_1 = 0.0;
      y_1 = 0.0;
      lambdaX = 0.0;
      lambdaY = 0.0;
      time(&timeStamp);
    }

  Trayectoria(double vel, int npuntos, vector<Punto> lstPuntos)
    {
      velocidad = vel;
      numPuntos = npuntos;
      listaPuntos = lstPuntos;
      origen = 0;
      x_1 = listaPuntos[origen].getX();
      y_1 = listaPuntos[origen].getY();
      lambdaX = 0.0;
      lambdaY = 0.0;
      time(&timeStamp);
    }

  void set_x_1(double val);
  void set_y_1(double val);
  void actLambdaX(double val);
  void actLambdaY(double val);
  void lambdaReset();
  double ecuacionRectaX();
  double ecuacionRectaY();
  int cambiarOrigen();
  void calcularNuevaPosicion(Punto *posActual);
  double normalizarD(double desplazamiento);
  void ecuacionRecta(Punto *posActual);
  void calcularPendiente();
  double getVelocidad();
  int getNumPuntos();
  void calcularTrayectoria(Punto *p);
  double calcDesp(double velocidad);
  void Print();
};

class Objeto
{
 public:
  enum tipoObjeto tipo;
  int vida;

  Objeto()
    {
      tipo = NODEF;
      vida = 3;
    }

  Objeto(enum tipoObjeto t, int v) 
    {
      tipo = t;
      vida = v;
    }

  virtual void Print();
  virtual void dibujarEsfera();
  virtual void dibujarCubo();
  virtual void dibujarMaya();
  void decVida();
};

class ObjetoMaya: public Objeto
{
 public:
  char *rutaArchivo;
  Punto p;

 ObjetoMaya() : Objeto(), rutaArchivo(NULL), p(Punto()) {}

 ObjetoMaya(enum tipoObjeto t, int vidas, char *nArchivo, 
             Punto x) : Objeto(t,vidas), rutaArchivo(nArchivo),
    p(x) {}

  ~ObjetoMaya() {free(rutaArchivo);}

  virtual void Print();
  void dibujarMaya();
};

class ObjetoCubo: public Objeto
{
 public:
  int tamano;
  Punto p;
  
 ObjetoCubo() : Objeto(), tamano(0), p(Punto()) {}

 ObjetoCubo(enum tipoObjeto t, int vidas, int tam, Punto x) :
  Objeto(t,vidas), tamano(tam), p(x) {}

  virtual void Print();
  void dibujarCubo();
};

class ObjetoEsfera: public Objeto
{
 public:
  Punto p;
  double radio;

 ObjetoEsfera() : Objeto(), p(Punto()), radio(0.0) {}
 
 ObjetoEsfera(enum tipoObjeto t, int vidas, Punto pto, double rad) :
  Objeto(t,vidas), p(pto), radio(rad) {}

  virtual void Print();
  void dibujarEsfera();
};

class Jugador
{
 public:
  double disparo;
  Trayectoria t;
  Punto posActual;

  Jugador() 
    {
      disparo = 0.0;
      t = Trayectoria();
      posActual = Punto();
    }

  Jugador(double d, Trayectoria tr, Punto ini)
    {
      disparo = d;
      t = tr;
      posActual = ini;
    }

  void Print();

  void dibujarJugador();
  void dibujarTrayectoriaJ();
};

class Nivel
{
 public:
  int id;
  int tiempo;
  Jugador j;
  int numContrincantes;
  vector<Jugador> listaContrincantes;
  int numObjetos;
  vector<Objeto*> listaObjetos;
  vector<Disco> listaDiscos;
  Punto limitesJuego;

  Nivel() 
    {
      id = 0;
      tiempo = 0;
      j = Jugador();
      numContrincantes = 0;
      listaContrincantes = vector<Jugador>();
      numObjetos = 0;
      listaObjetos = vector<Objeto*>();
      listaDiscos = vector<Disco>(numContrincantes + 1, Disco());
      limitesJuego = Punto();
    }
  
  Nivel(int ident, int t, Jugador jug, int nContr,
        vector<Jugador> listContr, int nObjetos,
        vector<Objeto*> listObj)
    {
      id = ident;
      tiempo = t;
      j = jug;
      numContrincantes = nContr;
      listaContrincantes = listContr;
      numObjetos = nObjetos;
      listaObjetos = listObj;
      limitesJuego = Punto();
      // Inicializar los discos
      // Jugador 
      listaDiscos.push_back(Disco(j.posActual));
      // Contrincantes
      for(int i = 0; i < numContrincantes; i++) 
        {
          listaDiscos.push_back(Disco(listaContrincantes[i].posActual));
        }
    }

  void dibujarTrayectoriaC();
  void dibujarJugadores();
  void dibujarObstaculos();
  void dibujarDiscos();
  void setLimite(double x, double y);
  void Print();
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

  Juego(int nNiveles, vector<Nivel> lstNivel)
    {
      numNiveles = nNiveles;
      listaNiveles = lstNivel;
    }

  void Print();
};

#endif
