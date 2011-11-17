#include "ModeloDatos.h"

using namespace std;

// Getters y setters de trayectoria
double Trayectoria::getVelocidad() 
{
  return velocidad;
}

int Trayectoria::getNumPuntos()
{
  return numPuntos;
}

// Getters y setters de Punto
double Punto::getX()
{
  return x;
}

double Punto::getY()
{
  return y;
}

// Setters de punto
void Punto::setX(double nuevoVal)
{
  x = nuevoVal;
  return;
}

void Punto::setY(double nuevoVal)
{
  y = nuevoVal;
  return;
}

void Trayectoria::actLambdaX(double val)
{
  lambdaX += val;
  return;
}

void Trayectoria::actLambdaY(double val)
{
  lambdaY += val;
  return;
}

double Trayectoria::normalizarV(double velocidad)
{
  double d =sqrt(pow(listaPuntos[(origen + 1) % numPuntos].getX() - 
                     listaPuntos[origen].getX(),2) +
                 pow(listaPuntos[(origen + 1) % numPuntos].getY() - 
                     listaPuntos[origen].getY(),2));
  return velocidad / d;
}

double Trayectoria::ecuacionRectaX()
{
  double diff = normalizarV(/*velocidad*1.0/60.0*/0.2);
  double x_prima = listaPuntos[origen].getX() + (lambdaX + diff)*
    (listaPuntos[(origen + 1) % numPuntos].getX() - listaPuntos[origen].getX()); 
  actLambdaX(diff);
  return x_prima;
}

double Trayectoria::ecuacionRectaY()
{
  double diff = normalizarV(/*velocidad*1.0/60.0*/0.2);
  double y_prima = listaPuntos[origen].getY() + (lambdaY + diff)*
    (listaPuntos[(origen + 1) % numPuntos].getY() - listaPuntos[origen].getY()); 
  actLambdaY(diff);
  return y_prima;
}

int Trayectoria::cambiarOrigen()
{
  if (lambdaX >= 1.0 || lambdaY >= 1.0) 
    {
      // Cambiar origen
      origen = (origen + 1) % numPuntos;
      return 1;
    }
  return 0;
}

void Trayectoria::calcularNuevaPosicion(Punto *posActual)
{
  posActual->setX(ecuacionRectaX());
  posActual->setY(ecuacionRectaY());
  return;
}

void Trayectoria::lambdaReset()
{
  lambdaX = 0.0;
  lambdaY = 0.0;
  return;
}

void Trayectoria::calcularTrayectoria(Punto *posActual) 
{
  if (cambiarOrigen()) {lambdaReset();}
  calcularNuevaPosicion(posActual);
  return;
}

void Jugador::dibujarJugador(double *incr) 
{
  glPushMatrix();
  glColor3f(0.2,0.9,0.5);
  // Jugador con un sólo punto en la trayectoria
  if (t.numPuntos == 1) 
    {
      glTranslatef(posActual.getX(), posActual.getY(), 0.0);
      glutSolidSphere(0.5, 20.0,20.0);
    }
  else  // Múltiples puntos
    {
      // Punto de origen -- Punto destino ?
      t.calcularTrayectoria(&posActual);
      glColor3f(1.0,0.0,0.0);
      glTranslatef(posActual.getX(), posActual.getY(), 0.0);
      glutSolidSphere(0.5, 20.0,20.0);
    }
  glPopMatrix();
}

void Nivel::dibujarJugadores(double *incr)
{
  // Dibujamos el jugador
  j.dibujarJugador(incr);
  // Dibujar contrincantes
  for(int i = 0; i < numContrincantes; i++) 
    {
      listaContrincantes[i].dibujarJugador(incr);
    }
}

// Dibujar trayectoria de jugador
void Jugador::dibujarTrayectoriaJ() 
{
  if (t.numPuntos == 1) { 
    glPushMatrix();
    glColor3f(1.0,0.0,0.0);
    glPointSize(10);
    glBegin(GL_POINTS);
    glVertex3f(t.listaPuntos[0].getX(), t.listaPuntos[0].getY(), 0.0);
    glEnd();
    glPopMatrix();
  }
  else
    {
      glColor3f(1.0,1.0,0.0);
      glPushMatrix();
      glLineWidth(5);
      glBegin(GL_LINE_LOOP);
      for (int i = 0; i < t.numPuntos - 1; i++) 
        {
          glVertex3f(t.listaPuntos[i].getX(), t.listaPuntos[i].getY(), 0.0);
          glVertex3f(t.listaPuntos[i+1].getX(), t.listaPuntos[i+1].getY(), 0.0);
        }
      glEnd();
      glPopMatrix();
    }
  return;
}

// Dibuja trayectoria de contrincante
void Nivel::dibujarTrayectoriaC()
{
  for(int i = 0; i < numContrincantes; i++) 
    {
      listaContrincantes[i].dibujarTrayectoriaJ();
    }
}

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
