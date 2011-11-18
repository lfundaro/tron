#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include "ModeloDatos.h"

class Camara
{
 public:
  GLfloat eyeZ;  // Se acerca al objeto en Z
  GLfloat centerX;  // Se mueve hacia los lados
  GLfloat centerY; // Se mueve hacia arriba/abajo.
  GLfloat upVector;

  Camara(GLfloat eZ, GLfloat cX, GLfloat cY) {
    eyeZ = eZ;
    centerX = cX;
    centerY = cY;
    upVector = 1.0;
  }

  void go(float tamX, float tamY, float giroH, float giroV,
          float avanceX, float avanceY, float camUpDown);
  
};
