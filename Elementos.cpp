#include "Elementos.h"
#include <stdio.h>
#include <math.h>

void 
dibujarLinea(float x, float y,float maxX, float maxY) 
{
  glPushMatrix();
  glLineWidth(2);
  glBegin(GL_LINES);
  if (x == 0.0) {
    glVertex3f(0.0,y,0.0);
    glVertex3f(maxX,y,0.0);
  } else {
    glVertex3f(x,0.0,0.0);
    glVertex3f(x,maxY,0.0);
  }
  glEnd();
  glPopMatrix();
}

void 
dibujarLineas(float x, float y)
{
  int i = 0;
  glColor3f(0.0,1.0,1.0);
  for (i =1; i < x+1; i++){
    dibujarLinea((float)i,0.0,x,y);
  }
  i = 0;
  for (i =1; i < y+1; i++){
    dibujarLinea(0.0,(float)i,x,y);
  }
}

void
dibujarBorde(float x, float y){
  glLineWidth(2);
  glColor3f(1.0,0.0,0.0);
  glPushMatrix();
  glBegin(GL_LINES);
    glVertex3f(0.0,0.0,0.0);
    glVertex3f(0.0,y,0.0);
  glEnd();
  glPopMatrix();
  glPushMatrix();
  glBegin(GL_LINES);
    glVertex3f(0.0,0.0,0.0);
    glVertex3f(x,0.0,0.0);
  glEnd();
  glPopMatrix();
  glPushMatrix();
  glBegin(GL_LINES);
  glVertex3f(x,y,0.0);
    glVertex3f(0.0,y,0.0);
  glEnd();
  glPopMatrix();
  glPushMatrix();
  glBegin(GL_LINES);
    glVertex3f(x,y,0.0);
    glVertex3f(x,0.0,0.0);
  glEnd();
  glPopMatrix();
}

void
dibujarBase(float x, float y)
{
  glPushMatrix();
  glColor3f(0.5,0.5,0.5);
  glBegin(GL_QUADS);
  glVertex3d(0.0,0.0,0.0);
  glVertex3d(x,0.0,0.0);
  glVertex3d(x,y,0.0);
  glVertex3d(0.0,y,0.0);
  glEnd();
  glPopMatrix();
}

void
dibujarContorno(float x, float y)
{
  glPushMatrix();
  glColor3f(1.0,0.0,0.0);
  glTranslatef((x)/2,(y)/2,-0.51);
  glScalef(x+2.0,y+2.0,1.0);
  glutSolidCube(1);
  glPopMatrix();
}

void
dibujarColumnas(float x, float y)
{
  float r = 0.6;
  float g = 0.6;
  float b = 0.6;

  glPushMatrix();
  glColor3f(r,g,b);
  glScalef(1,1,5.0);
  glTranslatef(-0.5,-0.5,0.5);
  glutSolidCube(1);
  glPopMatrix();

  glPushMatrix();
  glColor3f(r,g,b);
  glScalef(1,1,5.0);
  glTranslatef((float) ceil(x) - 0.5+1,-0.5,0.5);
  glutSolidCube(1);
  glPopMatrix();

  glPushMatrix();
  glColor3f(r,g,b);
  glScalef(1,1,5.0);
  glTranslatef(-0.5,(float) ceil(y)-0.5+1,0.5);
  glutSolidCube(1);
  glPopMatrix();

  glPushMatrix();
  glColor3f(r,g,b);
  glScalef(1,1,5.0);
  glTranslatef((float) ceil(x) - 0.5+1,(float) ceil(y)-0.5+1,0.5);
  glutSolidCube(1);
  glPopMatrix();
}

void
dibujarParedes(float x,float y){
  float r = 0.0;
  float g = 5.0;
  float b = 5.0;
  float grosorPared = 0.5;
  float alturaPared = 2.5;

  //Pared Izquierda
  glPushMatrix();
  glColor3f(r,g,b);
  glTranslatef((-grosorPared),y/2,+0.5);
  glScalef(grosorPared,y,alturaPared);
  glutSolidCube(1);
  glPopMatrix();

  //Pared Derecha
  glPushMatrix();
  glColor3f(r,g,b);
  glTranslatef(x+1+(-grosorPared),y/2,+0.5);
  glScalef(grosorPared,y,alturaPared);
  glutSolidCube(1);
  glPopMatrix();

  glPushMatrix();
  glColor3f(r,g,b);
  glTranslatef(x/2,(-grosorPared),+0.5);
  glScalef(x,grosorPared,alturaPared);
  glutSolidCube(1);
  glPopMatrix();

  glPushMatrix();
  glColor3f(r,g,b);
  glTranslatef(x/2,y+1+(-grosorPared),+0.5);
  glScalef(x,grosorPared,alturaPared);
  glutSolidCube(1);
  glPopMatrix();


}

void
dibujarTablero(float x,float y)
{
  dibujarBorde(x,y);
  dibujarLineas(x,y);
  dibujarBase(x,y);
  dibujarContorno(x,y);
  dibujarParedes(x,y);
  dibujarColumnas(x,y);
}

void
dibujarMira(double x, double y, float r, float g, float b)
{
  glPushMatrix();
  glColor3f(r,g,b);
  glScalef(1,1,0.2);
  glTranslatef((float) ceil(x) - 0.5,(float) ceil(y)-0.5,0.5);
  glLineWidth(5);
  glutWireCube(1);
  glPopMatrix();
}
