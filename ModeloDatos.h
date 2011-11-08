enum tipoObjeto {MAYA, CUBO};

typedef struct Objeto
{
  enum tipoObjeto;
  if (tipoObjeto == MAYA)
    {
      char *rutaArchivo;
      Punto p;
    }
  else    // CUBO 
    {
      Punto p;
      int tamano;
    }
};

typedef struct ListaObjetos
{
  Objeto obj;
  Objeto *next;
};

typedef struct Contrincante
{
  double disparo;
  Trayectoria t;
};

typedef struct ListaContrincantes
{
  Contrincante x;
  Contrincante *next;
};

typedef struct Punto
{
  int x;
  int y;
};

typedef struct ListaPuntos
{
  Punto x;
  Punto *next;
};

typedef struct Trayectoria
{
  int velocidad;
  int numPuntos;
  ListaPuntos *listaPuntos;
};

typedef struct Jugador 
{
  double disparo;
  Trayectoria t;
};

typedef struct Nivel
{
  int id;
  int tiempo;
  Jugador j;
  int numContrincantes;
  ListaContrincantes *listaContrincantes;
  int numObjetos;
  ListaObjetos *listaObjetos;
};

typedef struct ListaNiveles
{
  Nivel x;
  Nivel *next;
};

typedef struct Juego 
{
  int numNiveles;
  ListaNivel *niveles;
};
