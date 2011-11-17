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

// void Trayectoria::calcularPendiente()
// {
//   pendiente = (double)
//     (listaPuntos[origen + 1 % numPuntos].getY() - 
//     listaPuntos[origen].getY()) /
//     (listaPuntos[origen + 1 % numPuntos].getX() - 
//      listaPuntos[origen].getX()); 
//   cout << "Calculo pendiente" << endl;
//   cout << "origen 1 = " << origen + 1 % numPuntos << endl;
//   cout << "origen 2 = " << origen << endl;
//   cout << listaPuntos[origen + 1 % numPuntos].getY() << "-" << 
//     listaPuntos[origen].getY() << "/" << listaPuntos[origen + 1 % numPuntos].getX() << "-" << listaPuntos[origen].getX() << " = " << pendiente << endl;

//   return;
// }

// double Trayectoria::yDeLaRecta(Punto posActual)
// {
//   double y_prima = pendiente*posActual.getX() - pendiente*x_1 + y_1;
//   return y_prima;
// }

// double Trayectoria::xDeLaRecta(Punto posActual)
// {
//   double x_prima = (-pendiente*x_1 + y_1 - posActual.getY()) / (-pendiente);
//   return x_prima;
// }

// void Trayectoria::set_x_1(double val)
// {
//   x_1 = val;
// }

// void Trayectoria::set_y_1(double val)
// {
//   y_1 = val;
// }

// void Trayectoria::cambiarOrigen(Punto posActual)
// {
//   set_x_1(listaPuntos[origen].getX());
//   set_y_1(listaPuntos[origen].getY());
//   double y_prima = yDeLaRecta(posActual);
//   double x_prima = xDeLaRecta(posActual);
//   if (fabsf(y_prima - listaPuntos[origen + 1 % numPuntos + 1].getY()) <= 0.001 
//       && fabsf(x_prima - listaPuntos[origen + 1 % numPuntos + 1].getX()) <= 0.001)
//     {
//       // Cambiar origen
//       origen = origen + 1 % numPuntos + 1;
//       set_x_1(listaPuntos[origen].getX());
//       set_y_1(listaPuntos[origen].getY());
//     }
//   return;
// }

// void Trayectoria::calcularTrayectoria(Punto *posActual) 
// {
//   calcularPendiente();
//   cout << "Pendiente" << endl;
//   cout << pendiente << endl;
//   // Cambiar origen ? 
//   cambiarOrigen(*posActual);
//   Punto p_prima(posActual->getX() + 0.0001/*velocidad*1.0/60.0*/, 
//                 posActual->getY() + 0.0001 /*velocidad*1.0/60.0*/);
//   posActual->setX(xDeLaRecta(p_prima));
//   posActual->setY(yDeLaRecta(p_prima));
// }

// void Jugador::dibujarJugador(double *incr)
// {
//   glPushMatrix();
//   glColor3f(0.2,0.9,0.5);
//   // Jugador con un sólo punto en la trayectoria
//   if (t.numPuntos == 1) 
//     {
//       glTranslatef(posActual.getX(), posActual.getY(), 0.0);
//       glutSolidSphere(0.5, 20.0,20.0);
//     }
//   else  // Múltiples puntos
//     {
//       // Punto de origen -- Punto destino ?
//       t.calcularTrayectoria(&posActual);
//       //      cout << posActual.getX() << endl;
//       //      cout << posActual.getY() << endl;
//       glColor3f(1.0,0.0,0.0);
//       glTranslatef(posActual.getX(), posActual.getY(), 0.0);
//       glutSolidSphere(0.5, 20.0,20.0);
//     }
//   glPopMatrix();
// }

// // Dibujar jugadores según su posición actual
// void Nivel::dibujarJugadores(double *incr)
// {
//   // Dibujamos el jugador
//   cout << "Jugador" << endl;
//   cout << "numPuntos = " << j.t.numPuntos << endl;
//   j.dibujarJugador(incr);
//   // Dibujamos contrincantes
//   for(int i = 0; i < numContrincantes; i++) 
//     {
//       cout << "Contrincante = " << i << endl;
//       cout << "Num puntos = " << listaContrincantes[i].t.numPuntos << endl;
//       for(int j = 0; j < listaContrincantes[i].t.numPuntos; j++)
//         {
//           cout << "x = " << listaContrincantes[i].t.listaPuntos[j].getX() << endl;
//           cout << "y = " << listaContrincantes[i].t.listaPuntos[j].getY() << endl;
//         }
//       cout << listaContrincantes[i].posActual.getX() << endl;
//       cout << listaContrincantes[i].posActual.getY() << endl;
//       listaContrincantes[i].dibujarJugador(incr);
//       cout << "Cambio" << endl;
//       cout << listaContrincantes[i].posActual.getX() << endl;
//       cout << listaContrincantes[i].posActual.getY() << endl;

//     }
// }

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
  double d =sqrt(pow(listaPuntos[origen + 1 % numPuntos].getX() - 
                     listaPuntos[origen].getX(),2) +
                 pow(listaPuntos[origen + 1 % numPuntos].getY() - 
                     listaPuntos[origen].getY(),2));
  cout << "Distancia = " << d << endl;
  return velocidad / d;
}

double Trayectoria::ecuacionRectaX()
{
  double diff = normalizarV(/*velocidad*1.0/60.0*/0.1);
  //  cout << "diffX = " << diff << endl;
  double x_prima = listaPuntos[origen].getX() + (lambdaX + diff)*
    (listaPuntos[origen + 1 % numPuntos].getX() - listaPuntos[origen].getX()); 
  cout << "x_prima = " << listaPuntos[origen].getX() << " + (" << lambdaX << "+"
       << diff << ")*(" << listaPuntos[origen + 1 % numPuntos].getX() << " - " <<
    listaPuntos[origen].getX() << ")" << endl;
  cout << "x_prima = " << x_prima << endl;
  actLambdaX(diff);
  return x_prima;
}

double Trayectoria::ecuacionRectaY()
{
  double diff = normalizarV(/*velocidad*1.0/60.0*/0.1);
  //  cout << "diffY = " << diff << endl;
  double y_prima = listaPuntos[origen].getY() + (lambdaY + diff)*
    (listaPuntos[origen + 1 % numPuntos].getY() - listaPuntos[origen].getY()); 
  cout << "y_prima = " << listaPuntos[origen].getY() << " + (" << lambdaY << "+"
       << diff << ")*(" << listaPuntos[origen + 1 % numPuntos].getY() << " - " <<
    listaPuntos[origen].getY() << ")" << endl;
  cout << "y_prima = " << y_prima << endl;
  actLambdaY(diff);
  return y_prima;
}

int Trayectoria::cambiarOrigen(Punto posActual)
{
  if (lambdaX > 1.0 || lambdaY > 1.0) 
    {
      // Cambiar origen
      origen = origen + 1 % numPuntos;
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
  cout << "Posicion Actual" << endl;
  cout << "x = " << posActual->getX() << endl;
  cout << "y = " << posActual->getY() << endl;
  if (cambiarOrigen(*posActual)) lambdaReset();
  calcularNuevaPosicion(posActual);
  // Cambiar origen ? 
  // cout << "Origen = " << origen << endl;
  // if (cambiarOrigen(*posActual)) {
  //   // Se necesita recalcular la posición
  //   cout << "Cambio origen = " << origen << endl;
  //   lambdaReset();
  //   calcularNuevaPosicion(posActual);
  // }
  cout << "Nueva posicion" << endl;
  cout << "x = " << posActual->getX() << endl;
  cout << "y = " << posActual->getY() << endl;
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
  cout << "Jugador" << endl;
  // Dibujamos el jugador
  j.dibujarJugador(incr);
  // Dibujar contrincantes
  for(int i = 0; i < numContrincantes; i++) 
    {
      cout << "Contrincante = " << i << endl;
      listaContrincantes[i].dibujarJugador(incr);
      cout << "Fin" << endl;
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
