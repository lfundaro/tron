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

double Trayectoria::normalizarD(double desplazamiento)
{
  double d =sqrt(pow(listaPuntos[(origen + 1) % numPuntos].getX() - 
                     listaPuntos[origen].getX(),2) +
                 pow(listaPuntos[(origen + 1) % numPuntos].getY() - 
                     listaPuntos[origen].getY(),2));
  return velocidad / d;
}

double Trayectoria::calcDesp(double velocidad)
{
  double desp = velocidad*1.0/60.0;
  time_t now;
  time(&now);
  double difft = difftime(now,timeStamp);
  if (difft >= 1.0) 
    {
      cout.precision(15);
      cout << "diferenciaT = " << difft << endl;
      desp = velocidad*(difft);
      cout << "desplazamiento " << desp << endl;
      time(&timeStamp);
    }
  return desp;
}

void Trayectoria::ecuacionRecta(Punto *posActual)
{
  cout.precision(15);
  cout << "velocidad = " << velocidad << endl;
  double desplazamiento = calcDesp(velocidad/**1/60.0*/);
  if (desplazamiento > 0.0) {
    double norm = normalizarD(desplazamiento);
    double y_prima = listaPuntos[origen].getY() + (lambdaY + norm)*
      (listaPuntos[(origen + 1) % numPuntos].getY() - listaPuntos[origen].getY()); 
    actLambdaY(norm);
    double x_prima = listaPuntos[origen].getX() + (lambdaX + norm)*
      (listaPuntos[(origen + 1) % numPuntos].getX() - listaPuntos[origen].getX()); 
    actLambdaX(norm);
    posActual->setX(x_prima);
    posActual->setY(y_prima);
  }
  return;
}

int Trayectoria::cambiarOrigen()
{
  if (lambdaX >= 1.0 || lambdaY >= 1.0) 
    {
      origen = (origen + 1) % numPuntos;
      return 1;
    }
  return 0;
}

void Trayectoria::calcularNuevaPosicion(Punto *posActual)
{
  ecuacionRecta(posActual);
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
  cout << "Jugador" << endl;
  j.dibujarJugador(incr);
  // Dibujar contrincantes
  for(int i = 0; i < numContrincantes; i++) 
    {
      cout << "Contrincante = " << i << endl;
      listaContrincantes[i].dibujarJugador(incr);
    }
}

void Objeto::dibujarMaya() {}

void Objeto::dibujarCubo() {}

void Objeto::dibujarEsfera() {}

void ObjetoMaya::dibujarMaya() {}

void ObjetoEsfera::dibujarEsfera()
{
  glPushMatrix();
  glColor3f(0.0,0.8,0.4);
  glTranslatef(p.getX(), p.getY(), 0.0);
  glutSolidSphere(radio, 20, 20);
  glPopMatrix();
  return;
}

void ObjetoCubo::dibujarCubo()
{
  glPushMatrix();
  glColor3f(0.0,0.0,1.0);
  glTranslatef(p.getX(), p.getY(), 0.0);
  glScalef(tamano, tamano, 1.0);
  glutSolidCube(1.0);
  glPopMatrix(); 
  return;
}

//Dibujar obstaculos
void Nivel::dibujarObstaculos()
{
  for(int i = 0; i < numObjetos; i++) 
    {
      enum tipoObjeto t = listaObjetos[i]->tipo;
      if (t == CUBO)
        {
          ObjetoCubo *objC = (dynamic_cast <ObjetoCubo*> (listaObjetos[i]));
          objC->dibujarCubo();
        }
      else if (t == ESFERA) 
        {
          ObjetoEsfera *objF = (dynamic_cast <ObjetoEsfera*> (listaObjetos[i]));
          objF->dibujarEsfera();
        }
      else if (t == MAYA) 
        continue;
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
  for(vector<Objeto*>::iterator it = listaObjetos.begin();
      it != listaObjetos.end(); ++it)
    {
      (*it)->Print();
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
