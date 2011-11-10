#include <GL/gl.h>
#include <GL/glut.h>
#include "Parser.h"
#include "Elementos.h"

Juego j;
float x = 15.0;
float y = 10.0;

void 
display(void)
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt (0.0, (-x)/10.0,(-x)/10*6, 0.0,(-y)/20.0,(-x)/3.0, 0.0, 0.0,-1.0);
    glTranslatef((-x)/2,(-y)/2,0.0);
    dibujarTablero(x,y);
    glutPostRedisplay();
    glutSwapBuffers();
    glFlush ();
}

void 
reshape (int w, int h)
{
  float aspectratio;
  aspectratio = (float) w / (float) h;
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(90.0f, 1, 0.5, 100.0);
  glMatrixMode(GL_MODELVIEW);
  glViewport (0, 0, (GLsizei) w, (GLsizei) h);
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
  //  glutKeyboardFunc(keyboard);
  glutMainLoop();


  exit (EXIT_SUCCESS);
}
