#include <GL/gl.h>
#include <GL/glut.h>
#include "Parser.h"
#include "Elementos.h"

Juego j;
float tamX = 10.0;
float tamY = 10.0;
float giro = 0;
int mouVenX = 0;
int mouVenY = 0;
double mouJueX = tamX/2;
double mouJueY = tamY/2;
double mouJueZ = 1;

void
display(void)
{
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  /* Coordenad=as del sistema */
  glLoadIdentity();
  //gluLookAt (0.0, (-x)/10.0,(-x)/10*6, 0.0,(-y)/20.0,(-x)/3.0, 0.0, 0.0,-1.0);
  gluLookAt (0.0, (-tamX)/10, (tamY)/10*6,
             0.0+giro, (-tamY)/20, (-tamX)/3,
             0.0, 1.0, 0.0);
  glTranslatef((-tamX)/2,(-tamY)/2,0.0);

  /* Tablero */
  dibujarMira(mouJueX,mouJueY,1.0,0.0,1.0);
  dibujarTablero(tamX,tamY);
  glutPostRedisplay();
  glutSwapBuffers();
  glFlush ();
  return;
}

void
reshape (int w, int h)
{
  float aspectratio;
  aspectratio = (float) w / (float) h;
  glViewport (0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(90.0f, 1, 0.5, 100.0);
  glMatrixMode(GL_MODELVIEW);
}

void
proyectarMouse(int x, int y)
{
  GLint viewport[4];
  GLdouble modelview[16];
  GLdouble projection[16];
  GLfloat winX, winY, winZ;
  GLdouble posX, posY, posZ;
  glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
  glGetDoublev( GL_PROJECTION_MATRIX, projection );
  glGetIntegerv( GL_VIEWPORT, viewport );
  winX = (float)x;
  winY = (float)viewport[3] - (float)y;
  glReadPixels( x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );
  gluUnProject( winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);
  mouJueX = posX;
  mouJueY = posY;
  mouJueZ = posZ;
  printf("(%f,%f,%f) y ",posX,posY,posZ);
}

void
flechas(int key, int x, int y)
{
  switch(key) {
  case GLUT_KEY_LEFT:
    if (giro > -9)
      giro -= 0.1;
    break;
  case GLUT_KEY_RIGHT:
    if (giro < 9)
      giro += 0.1;
    break;
  }
  mouVenX = x;
  mouVenY = y;
  proyectarMouse(x,y);
}

void
moverMouse(int x, int y)
{
  mouVenX = x;
  mouVenY = y;
  proyectarMouse(x,y);
  printf("(%d,%d)\n",x,y);
}

void
accionMouse(int key, int state, int x, int y)
{
  int i = 0;
 switch(key) {
 case GLUT_LEFT_BUTTON:
   switch(state){
   case GLUT_UP:
     proyectarMouse(x,y);
     printf("Dispare en (%d,%d)\n",x,y);
     break;
   }
   break;
 }
}

int
main (int argc, char **argv)
{
  /* Abrir archivo e inicializar estructuras de juego */
  char *archivo = argv[1];
  j = parse(archivo);
  // j.Print();
  /* Inicialización de ventana */
  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB |  GLUT_DEPTH);
  glutInitWindowSize (800, 600);
  glutInitWindowPosition (100, 150);
  glutCreateWindow (argv[0]);
  /* Propiedades de openGL */
  glEnable(GL_DEPTH_TEST);
  glClearDepth (1.0f);
  glClearColor(0,0,0,1.0f);
  glShadeModel(GL_SMOOTH); 
  glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); 
  /* Directivas para graficar */
  glutReshapeFunc(reshape);
  glutDisplayFunc(display);
  glutSpecialFunc(flechas);
  glutMouseFunc(accionMouse);
  glutMotionFunc(moverMouse);
  glutPassiveMotionFunc(moverMouse);
  //glutKeyboardFunc(keyboard);
  glutMainLoop();

  exit (EXIT_SUCCESS);
}
