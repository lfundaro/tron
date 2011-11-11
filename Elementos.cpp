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
dibujarTablero(float x,float y)
{
  dibujarBorde(x,y);
  dibujarLineas(x,y);
  dibujarBase(x,y);
}

void
dibujarMira(double x, double y, float r, float g, float b)
{
  glPushMatrix();
  glTranslatef((float) ceil(x) - 0.5,(float) ceil(y)-0.5,0.5);
  glColor3f(r,g,b);
  glutSolidCube(1);
  glPopMatrix();
}
