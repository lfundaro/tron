#include <GL/gl.h>
#include <GL/glut.h>
#include "Parser.h"
#include "Elementos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "strutil.h"
#include <string>
#include "TriMesh.h"
#include "XForm.h"
#include "GLCamera.h"
#include "ICP.h"
#include <unistd.h>
#include "Camara.h"

using namespace std;

// Globals
vector<TriMesh *> meshes;
vector<xform> xforms;
vector<bool> visible;
vector<string> filenames;

TriMesh::BSphere global_bsph;
xform global_xf;
GLCamera camera;

int current_mesh = -1;

bool draw_edges = false;
bool draw_2side = false;
bool draw_shiny = true;
bool draw_lit = true;
bool draw_falsecolor = false;
bool draw_index = false;
bool white_bg = false;
int point_size = 1, line_width = 1;

/* Comienzo Código Trimesh */
// Signal a redraw
void need_redraw()
{
  glutPostRedisplay();
}


// Clear the screen
void cls()
{
  glDisable(GL_DITHER);
  glDisable(GL_BLEND);
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_NORMALIZE);
  glDisable(GL_LIGHTING);
  glDisable(GL_NORMALIZE);
  glDisable(GL_COLOR_MATERIAL);
  if (white_bg)
    glClearColor(1, 1, 1, 0);
  else
    glClearColor(0.08, 0.08, 0.08, 0);
  glClearDepth(1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}


// Set up lights and materials
void setup_lighting(int id)
{
  Color c(1.0f);
  if (draw_falsecolor)
    c = Color::hsv(-3.88 * id, 0.6 + 0.2 * sin(0.42 * id), 1.0);
  glColor3fv(c);

  if (!draw_lit || meshes[id]->normals.empty()) {
    glDisable(GL_LIGHTING);
    return;
  }

  GLfloat mat_specular[4] = { 0.18, 0.18, 0.18, 0.18 };
  if (!draw_shiny) {
    mat_specular[0] = mat_specular[1] =
      mat_specular[2] = mat_specular[3] = 0.0f;
  }
  GLfloat mat_shininess[] = { 64 };
  GLfloat global_ambient[] = { 0.02, 0.02, 0.05, 0.05 };
  GLfloat light0_ambient[] = { 0, 0, 0, 0 };
  GLfloat light0_diffuse[] = { 0.85, 0.85, 0.8, 0.85 };
  if (current_mesh >= 0 && id != current_mesh) {
    light0_diffuse[0] *= 0.5f;
    light0_diffuse[1] *= 0.5f;
    light0_diffuse[2] *= 0.5f;
  }
  GLfloat light1_diffuse[] = { -0.01, -0.01, -0.03, -0.03 };
  GLfloat light0_specular[] = { 0.85, 0.85, 0.85, 0.85 };
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
  glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE);
  glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, draw_2side);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_NORMALIZE);
}


// Draw triangle strips.  They are stored as length followed by values.
void draw_tstrips(const TriMesh *themesh)
{
  static bool use_glArrayElement = false;
  static bool tested_renderer = false;
  if (!tested_renderer) {
    use_glArrayElement = !!strstr(
                                  (const char *) glGetString(GL_RENDERER), "Intel");
    tested_renderer = true;
  }

  const int *t = &themesh->tstrips[0];
  const int *end = t + themesh->tstrips.size();
  if (use_glArrayElement) {
    while (likely(t < end)) {
      glBegin(GL_TRIANGLE_STRIP);
      int striplen = *t++;
      for (int i = 0; i < striplen; i++)
        glArrayElement(*t++);
      glEnd();
    }
  } else {
    while (likely(t < end)) {
      int striplen = *t++;
      glDrawElements(GL_TRIANGLE_STRIP, striplen, GL_UNSIGNED_INT, t);
      t += striplen;
    }
  }
}


// Draw the mesh
void draw_mesh(int i)
{
  const TriMesh *themesh = meshes[i];

  glPushMatrix();
  glMultMatrixd(xforms[i]);

  glDepthFunc(GL_LESS);
  glEnable(GL_DEPTH_TEST);

  if (draw_2side) {
    glDisable(GL_CULL_FACE);
  } else {
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
  }

  // Vertices
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT,
                  sizeof(themesh->vertices[0]),
                  &themesh->vertices[0][0]);

  // Normals
  if (!themesh->normals.empty() && !draw_index) {
    glEnableClientState(GL_NORMAL_ARRAY);
    glNormalPointer(GL_FLOAT,
                    sizeof(themesh->normals[0]),
                    &themesh->normals[0][0]);
  } else {
    glDisableClientState(GL_NORMAL_ARRAY);
  }

  // Colors
  if (!themesh->colors.empty() && !draw_falsecolor && !draw_index) {
    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(3, GL_FLOAT,
			       sizeof(themesh->colors[0]),
			       &themesh->colors[0][0]);
  } else {
    glDisableClientState(GL_COLOR_ARRAY);
  }

  // Main drawing pass
  if (themesh->tstrips.empty()) {
    // No triangles - draw as points
    glPointSize(point_size);
    glDrawArrays(GL_POINTS, 0, themesh->vertices.size());
    glPopMatrix();
    return;
  }

  if (draw_edges) {
    glPolygonOffset(10.0f, 10.0f);
    glEnable(GL_POLYGON_OFFSET_FILL);
  }

  draw_tstrips(themesh);
  glDisable(GL_POLYGON_OFFSET_FILL);

  // Edge drawing pass
  if (draw_edges) {
    glPolygonMode(GL_FRONT, GL_LINE);
    glLineWidth(line_width);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisable(GL_COLOR_MATERIAL);
    GLfloat global_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat light0_diffuse[] = { 0.8, 0.8, 0.8, 0.0 };
    GLfloat light1_diffuse[] = { -0.2, -0.2, -0.2, 0.0 };
    GLfloat light0_specular[] = { 0.0f, 0.0f, 0.0f, 0.0f };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
    GLfloat mat_diffuse[4] = { 0.0f, 0.0f, 1.0f, 1.0f };
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, mat_diffuse);
    glColor3f(0, 0, 1); // Used iff unlit
    draw_tstrips(themesh);
    glPolygonMode(GL_FRONT, GL_FILL);
  }

  glPopMatrix();
}


// Draw the scene
void redraw()
{
  //camera.setupGL(global_xf * global_bsph.center, global_bsph.r);
  glPushMatrix();
  glMultMatrixd(global_xf);
  //	cls();
  for (int i = 0; i < meshes.size(); i++) {
    if (!visible[i])
      continue;
    setup_lighting(i);
    draw_mesh(i);
  }

  glPopMatrix();
  glutSwapBuffers();
  //	fflush(stdout);
}


// Update global bounding sphere.
void update_bsph()
{
  point boxmin(1e38, 1e38, 1e38);
  point boxmax(-1e38, -1e38, -1e38);
  bool some_vis = false;
  for (int i = 0; i < meshes.size(); i++) {
    if (!visible[i])	
      continue;
    some_vis = true;
    point c = xforms[i] * meshes[i]->bsphere.center;
    float r = meshes[i]->bsphere.r;
    for (int j = 0; j < 3; j++) {
      boxmin[j] = min(boxmin[j], c[j]-r);
      boxmax[j] = max(boxmax[j], c[j]+r);
    }
  }
  if (!some_vis)
    return;
  point &gc = global_bsph.center;
  float &gr = global_bsph.r;
  gc = 0.5f * (boxmin + boxmax);
  gr = 0.0f;
  for (int i = 0; i < meshes.size(); i++) {
    if (!visible[i])	
      continue;
    point c = xforms[i] * meshes[i]->bsphere.center;
    float r = meshes[i]->bsphere.r;
    gr = max(gr, dist(c, gc) + r);
  }
}


// ICP
void do_icp(int n)
{
  camera.stopspin();

  if (current_mesh < 0 || current_mesh >= meshes.size())
    return;
  if (n < 0 || n >= meshes.size())
    return;
  if (!visible[n] || !visible[current_mesh] || n == current_mesh)
    return;
  ICP(meshes[n], meshes[current_mesh], xforms[n], xforms[current_mesh], 2);
  update_bsph();
  need_redraw();
}

/* Fin Código Trimesh */

Juego j;
float tamX = 100.0;
float tamY = 100.0;
float giroH = 0;
float giroV = 0;
int mouVenX = 0;
int mouVenY = 0;
double mouJueX = tamX/2;
double mouJueY = tamY/2;
double mouJueZ = 1;
int nivelActual = 0;
Punto posActualJugador;
vector<Punto> posContrincante;
float zoom = 90.0;
#define ZOOM_FACTOR 1.0
Camara cam = Camara((tamY+2)/10*6,-tamX+2/3, (-tamY+2)/20);
GLfloat camUpDown = 0.0;
GLfloat rot = 0.0;
GLfloat avanceX = 0.0;
GLfloat avanceY = 0.0;

void
display(void)
{
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  /* Coordenad=as del sistema */
  glLoadIdentity();
  cam.go(tamX, tamY, giroH, giroV);
  //gluLookAt (0.0, (-x)/10.0,(-x)/10*6, 0.0,(-y)/20.0,(-x)/3.0, 0.0, 0.0,-1.0);
  // if (tamX == tamY) {
  // gluLookAt (0.0, (-(tamX+2))/10, (tamY+2)/10*6,
  //            0.0+giroH, giroV+(-(tamY+2))/20, (-(tamX+2))/3,
  //            0.0,1, 0.0);
  // } else if (tamX < tamY) {
  // gluLookAt (0.0, (-(tamY+2))/10, (tamY+2)/10*6,
  //            0.0+giroH, giroV+(-(tamY+2))/20, (-(tamY+2))/3,
  //            0.0,1, 0.0);
  // } else {
  // gluLookAt (0.0, (-(tamX+2))/10, (tamX+2)/10*6,
  //            0.0+giroH, giroV+(-(tamX+2))/20, (-(tamX+2))/3,
  //            0.0,1, 0.0);
  // }

  glTranslatef((-tamX)/2 + avanceX,(-tamY)/2 + avanceY,camUpDown);
  glRotatef(rot, 0.0,0.0,camUpDown);

  /* Tablero */
  dibujarMira(mouJueX,mouJueY,1.0,1.0,0.0);
  dibujarTablero(tamX,tamY);
  //  redraw();
  // Dibujar trayectoria de Jugador
  j.listaNiveles[nivelActual].j.dibujarTrayectoriaJ();
  j.listaNiveles[nivelActual].dibujarTrayectoriaC();
  // Dibujar jugadores en posición inicial
  j.listaNiveles[nivelActual].dibujarJugadores();
  // Dibujar obstáculos
  j.listaNiveles[nivelActual].dibujarObstaculos();
  // Dibujar discos
  j.listaNiveles[nivelActual].dibujarDiscos();
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
  //  gluPerspective(90.0f, 1, 0.5, 100.0);
  gluPerspective(zoom, 1, 0.5, 100.0);
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
  //  printf("(%f,%f,%f) y ",posX,posY,posZ);
}

void
flechas(int key, int x, int y)
{
  switch(key) {
  case GLUT_KEY_LEFT:
    //    if (giroH > -9)
      giroH -= 2.0;
    break;
  case GLUT_KEY_RIGHT:
    //    if (giroH < 9)
      giroH += 2.0;
    break;
  case GLUT_KEY_DOWN:
    //    if (giroV > -9)
      giroV -= 2.0;
    break;
  case GLUT_KEY_UP:
    //    if (giroV < 9)
      giroV += 2.0;
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
  //  printf("(%d,%d)\n",x,y);
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
      //     printf("Dispare en (%d,%d)\n",x,y);
      break;
    }
    break;
  }
}

void teclaPausa()
{
  sleep(5);
}

void teclaZoomIn()
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  zoom -= ZOOM_FACTOR;
  gluPerspective(zoom, 1, 0.5, 100.0);
  glMatrixMode(GL_MODELVIEW);
}

void teclaZoomOut()
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  zoom += ZOOM_FACTOR;
  gluPerspective(zoom, 1, 0.5, 100.0);
  glMatrixMode(GL_MODELVIEW);
}

void teclaCamUp()
{
  camUpDown -= 0.5;
}

void teclaCamDown()
{
  camUpDown += 0.5;
}

void teclaRotIzq()
{
  rot -= 3.0;
}

void teclaRotDer()
{
  rot += 3.0;
}

void teclaTrasXIzq()
{
  avanceX += 0.5; 
}

void teclaTrasXDer()
{
  avanceX -= 0.5;
}

void teclaTrasYDer()
{
  avanceY -= 0.5;
}

void teclaTrasYIzq()
{
  avanceY += 0.5;
}

void
keyboard (unsigned char key, int x, int y) 
{
  switch (key)
    {
    case 'P': case 'p':
      teclaPausa();
      glutPostRedisplay();
      break;
    case 'I': case 'i':
      teclaZoomIn();
      break;
    case 'O': case 'o':
      teclaZoomOut();
      break;
    case 'U': case 'u': 
      teclaCamUp();
      break;
    case 'D': case 'd':
      teclaCamDown();
      break;
    case 'A': case 'a':
      teclaRotIzq();
      break;
    case 'S': case 's':
      teclaRotDer();
      break;
    case 'F': case 'f': 
      teclaTrasXIzq();
      break;
    case 'G': case 'g':
      teclaTrasXDer();
      break;
    case 'B': case 'b': 
      teclaTrasYIzq();
      break;
    case 'N': case 'n':
      teclaTrasYDer();
      break;
    default:
      printf("Didnt match\n");
      break;
    }
  return;
}

int
main (int argc, char **argv)
{
  /* Abrir archivo e inicializar estructuras de juego */
  char *archivo = argv[1];
  j = parse(archivo);
  /* Límites del juego */
  for(int i = 0; i < j.numNiveles; i++)
    {
      j.listaNiveles[i].setLimite((double) tamX, (double) tamY);
    }
  /* Inicialización de ventana */
  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB |  GLUT_DEPTH);
  glutInitWindowSize (1280,800);
  glutInitWindowPosition (100, 150);


  /* Cargar figura .ply */ 

  // const char *filename = argv[2];
  // TriMesh *themesh = TriMesh::read(filename);
  // // if (!themesh)
  // //   usage(argv[0]);
  // themesh->need_normals();
  // themesh->need_tstrips();
  // themesh->need_bsphere();
  // meshes.push_back(themesh);
  // xforms.push_back(xform());
  // visible.push_back(true);
  // filenames.push_back(filename);
  

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
  glutKeyboardFunc(keyboard);
  //glutKeyboardFunc(keyboard);
  glutMainLoop();

  exit (EXIT_SUCCESS);
}
