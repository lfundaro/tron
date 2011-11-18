#include "Camara.h"

void Camara::go(float tamX, float tamY, float giroH, float giroV)
{
  
  gluLookAt (0.0, (-(tamX+2))/10, eyeZ,
             0.0+giroH, giroV + centerY, (-(tamX+2))/3,
             0.0,upVector, 0.0);
}
