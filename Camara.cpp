#include "Camara.h"

using namespace std;

void Camara::go(float tamX, float tamY, float giroH, float giroV,
                float avanceX, float avanceY, float camUpDown)
{
  
  // gluLookAt (0.0, (-(tamX+2))/10, eyeZ,
  //            0.0+giroH, giroV + centerY, (-(tamX+2))/3,
  //            0.0,upVector, 0.0);

  // cout << "avanceX = " << avanceX << endl;
  // cout << "avanceY = " << avanceY << endl;
  // cout << "camUpDown = " << camUpDown << endl;
  if (tamX == tamY) {
    gluLookAt (0.0, (-(tamX+2))/10, (tamY+2)/10*6,
               0.0+giroH, giroV+(-(tamY+2))/20, (-(tamX+2))/3,
               0.0,1, 0.0); 
  } else if (tamX < tamY) {
    gluLookAt (0.0, (-(tamY+2))/10, (tamY+2)/10*6,
               0.0+giroH, giroV+(-(tamY+2))/20, (-(tamY+2))/3,
               0.0,1, 0.0);
  } else {
    gluLookAt (0.0, (-(tamX+2))/10, (tamX+2)/10*6,
               0.0+giroH, giroV+(-(tamX+2))/20, (-(tamX+2))/3,
               0.0,1, 0.0);
  }
  glTranslatef((-tamX)/2 + avanceX,(-tamY)/2 + avanceY,camUpDown);
}
