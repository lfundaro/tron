#include "Elementos.h"
#include <stdio.h>
#include <math.h>

void 
dibujarLinea(float x, float y,float maxX, float maxY) 
{
  glPushMatrix();
  glLineWidth(1);
  glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );
  glHint( GL_POLYGON_SMOOTH_HINT, GL_NICEST );
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
  glColor3f(0.0,0.0,0.0);
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
  glBegin(GL_QUADS);
  glNormal3f(0.0,1.0,0.0);
  glColor3f(1.0,1.0,1.0); glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0,0.0,0.0);
  glColor3f(1.0,1.0,1.0); glTexCoord2f(x, 0.0f); glVertex3f(x,0.0,0.0);
  glColor3f(1.0,1.0,1.0); glTexCoord2f(x, y); glVertex3f(x,y,0.0);
  glColor3f(1.0,1.0,1.0); glTexCoord2f(0.0f, y); glVertex3f(0.0,y,0.0);
  glEnd();
  glPopMatrix();
}

void
dibujarContorno(float x, float y)
{
  glPushMatrix();
  glColor3f(0.0,1.0,1.0);
  glTranslatef((x)/2,(y)/2,-0.51);
  glScalef(x+2.0,y+2.0,1.0);
  glutSolidCube(1);
  glPopMatrix();
}

void
dibujarColumnas(float x, float y, float z)
{
  float r = 0.6;
  float g = 0.6;
  float b = 0.6;
  glLineWidth(10);
  glPushMatrix();
  glColor3f(r,g,b);
  glScalef(1,1,z+1);
  glTranslatef(-0.5,-0.5,0.5);
  glutSolidCube(1);
  glColor3f(0.0,0.0,0.0);
  glutWireCube(1);
  glPopMatrix();

  glPushMatrix();
  glColor3f(r,g,b);
  glScalef(1,1,z+1);
  glTranslatef((float) ceil(x) - 0.5+1,-0.5,0.5);
  glutSolidCube(1);
  glColor3f(0.0,0.0,0.0);
  glutWireCube(1);
  glPopMatrix();

  glPushMatrix();
  glColor3f(r,g,b);
  glScalef(1,1,z+1);
  glTranslatef(-0.5,(float) ceil(y)-0.5+1,0.5);
  glutSolidCube(1);
  glColor3f(0.0,0.0,0.0);
  glutWireCube(1);
  glPopMatrix();

  glPushMatrix();
  glColor3f(r,g,b);
  glScalef(1,1,z+1);
  glTranslatef((float) ceil(x) - 0.5+1,(float) ceil(y)-0.5+1,0.5);
  glutSolidCube(1);
  glColor3f(0.0,0.0,0.0);
  glutWireCube(1);
  glPopMatrix();
}

void
dibujarParedes(float x,float y, float z){
  float r = 0.0;
  float g = 5.0;
  float b = 5.0;
  float baseX;
  float baseY;
  float maxX;
  float maxY;

  //Pared Inferior
  baseY = -0.5;
  maxY = -0.5;
  baseX = 0.0;
  maxX = x;
  glPushMatrix();
  glBegin(GL_QUADS);
  glNormal3f(1.0,0.0,0.0);
  glColor3f(1.0,1.0,1.0); glTexCoord2f(0.0f, 0.0f); glVertex3f(baseX,baseY,0.0);
  glColor3f(1.0,1.0,1.0); glTexCoord2f(x, 0.0f); glVertex3f(maxX,baseY,0.0);
  glColor3f(1.0,1.0,1.0); glTexCoord2f(x, 1.0f); glVertex3f(maxX,baseY,z);
  glColor3f(1.0,1.0,1.0); glTexCoord2f(0.0f, 1.0f); glVertex3f(baseX,baseY,z);
  glEnd();
  glPopMatrix();

  //Pared Superior
  baseY = y+0.5;
  maxY = y+0.5;
  baseX = 0.0;
  maxX = x;
  glPushMatrix();
  glBegin(GL_QUADS);
  glNormal3f(-1.0,0.0,0.0);
  glColor3f(1.0,1.0,1.0); glTexCoord2f(0.0f, 0.0f); glVertex3f(baseX,baseY,0.0);
  glColor3f(1.0,1.0,1.0); glTexCoord2f(x, 0.0f); glVertex3f(maxX,baseY,0.0);
  glColor3f(1.0,1.0,1.0); glTexCoord2f(x, 1.0f); glVertex3f(maxX,baseY,z);
  glColor3f(1.0,1.0,1.0); glTexCoord2f(0.0f, 1.0f); glVertex3f(baseX,baseY,z);
  glEnd();
  glPopMatrix();

  //Pared Izquierda
  baseY = 0.0;
  maxY = y;
  baseX = -0.5;
  maxX = -0.5;
  glPushMatrix();
  glBegin(GL_QUADS);
  glNormal3f(-1.0,0.0,0.0);
  glColor3f(1.0,1.0,1.0); glTexCoord2f(0.0f, 0.0f); glVertex3f(baseX,baseY,0.0);
  glColor3f(1.0,1.0,1.0); glTexCoord2f(x, 0.0f); glVertex3f(baseX,maxY,0.0);
  glColor3f(1.0,1.0,1.0); glTexCoord2f(x, 1.0f); glVertex3f(baseX,maxY,z);
  glColor3f(1.0,1.0,1.0); glTexCoord2f(0.0f, 1.0f); glVertex3f(baseX,baseY,z);
  glEnd();
  glPopMatrix();

  //Pared Derecha
  baseY = 0.0;
  maxY = y;
  baseX = x+0.5;
  maxX = x+0.5;
  glPushMatrix();
  glBegin(GL_QUADS);
  glNormal3f(-1.0,0.0,0.0);
  glColor3f(1.0,1.0,1.0); glTexCoord2f(0.0f, 0.0f); glVertex3f(baseX,baseY,0.0);
  glColor3f(1.0,1.0,1.0); glTexCoord2f(x, 0.0f); glVertex3f(baseX,maxY,0.0);
  glColor3f(1.0,1.0,1.0); glTexCoord2f(x, 1.0f); glVertex3f(baseX,maxY,z);
  glColor3f(1.0,1.0,1.0); glTexCoord2f(0.0f, 1.0f); glVertex3f(baseX,baseY,z);
  glEnd();
  glPopMatrix();


/*
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

  */
}

void
dibujarTablero(float x,float y, float z)
{
  dibujarBorde(x,y);
  dibujarContorno(x,y);
  dibujarColumnas(x,y,z);
}

void
dibujarMira(double x, double y, float r, float g, float b)
{
  glPushMatrix();
  glColor3f(r,g,b);
  glLineWidth(5);
  float posX = (float) ceil(x);
  float posY = (float) ceil(y);
  glBegin(GL_LINE_LOOP);
  glNormal3f(1.0,0.0,0.0);
  glVertex3f(posX-1,posY-1,0.1);
  glVertex3f(posX,posY-1,0.1);
  glVertex3f(posX,posY,0.1);
  glVertex3f(posX-1,posY,0.1);
  glEnd();
  /*  glScalef(1,1,0.2);
  glTranslatef((float) ceil(x) - 0.5,(float) ceil(y)-0.5,0.1);
  glutWireCube(1);
 */
  glPopMatrix();
}
