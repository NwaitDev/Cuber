#include <GL/freeglut_std.h>
#include <bits/atomic_wide_counter.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <vector>

#include "construction.h"

//makes the use of 3D arrays clearer
#define X 0
#define Y 1
#define Z 2

//makes the use of glFrustum parameters clearer
#define LEFT 0
#define RIGHT 1
#define BOTTOM 2
#define TOP 3 
#define CMIN 4
#define CMAX 5

/* Variables globales                           */

static int lighting = 1;
static int lightsActivation[] = { 1,0,0,0,0,0,0,0 };
static int lights[] = { GL_LIGHT0, GL_LIGHT1, GL_LIGHT2, GL_LIGHT3, GL_LIGHT4, GL_LIGHT5, GL_LIGHT6, GL_LIGHT7};

static int mousePos [2] = { 0,0 };
static int mouseDiff[2] = { 0,0 };
static float angle[3] = {0,0, 0};

static int wTx = 1000;              // horizontal resolution of the window 
static int wTy = 1000;              // vertical resolution of the window
static int wPx = 50;               // horizontal position of the window 
static int wPy = 50;              // vertical position of the window


static float rotationX = 1;
static float rotationY = 1;
static float rotationZ = 1;

static int frameNumber = 0;
static int totalFrameNumber;

/*used for delta-time in anim*/
static int old_t;

static float zoom = -5.0F;

static GLenum currentView = GL_FILL;

static const float noir[] = { 0.0F,0.0F,0.0F,1.0F };
static const float blanc[] = { 1.0F,1.0F,1.0F,1.0F };
static const float gris[] = { 0.7F,0.7F,0.7F,1.0F };
static const float jaune[] = { 1.0F,1.0F,0.0F,1.0F };
static const float rouge[] = { 1.0F,0.0F,0.0F,1.0F };
static const float vert[] = { 0.0F,1.0F,0.0F,1.0F };
static const float bleu[] = { 0.0F,0.0F,1.0F,1.0F };


static std::vector<float> XBlinkyCoords;
static std::vector<float> YBlinkyCoords;
static std::vector<float> ZBlinkyCoords;
static std::vector<float> RBlinkyColor;
static std::vector<float> GBlinkyColor;
static std::vector<float> BBlinkyColor;
static std::vector<int> blinkiesPerFrame;


/* Fonction d'initialisation des parametres     */
/* OpenGL ne changeant pas au cours de la vie   */
/* du programme                                 */

static void init(void) {
  std::ifstream file("data.csv");
  if (!file) {
      throw std::runtime_error("Could not open data.csv");
  }
  const GLfloat shininess[] = { 5.0 };
  glMaterialfv(GL_FRONT,GL_AMBIENT,noir);
  glMaterialfv(GL_FRONT,GL_DIFFUSE,blanc);
  glMaterialfv(GL_FRONT,GL_SPECULAR,gris);
  glMaterialfv(GL_FRONT,GL_SHININESS,shininess);
  glLightfv(GL_LIGHT0,GL_DIFFUSE,blanc);
  glLightfv(GL_LIGHT1,GL_DIFFUSE,jaune);
  glLightfv(GL_LIGHT2,GL_DIFFUSE,bleu);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);
  glEnable(GL_LIGHT2);
  glDepthFunc(GL_LESS);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_NORMALIZE);
  glEnable(GL_AUTO_NORMAL);
  glEnable(GL_LIGHTING);
  old_t = glutGet(GLUT_ELAPSED_TIME);

  std::string line;

  //ignoring the first line (these are just the headers of the columns)
  std::getline(file, line);

  float x,y,z,r,g,b;

  int t = 0;
  int t_minus_1 = 0;
  int countedBlinkies = 0;

  while (std::getline(file, line)) {
      std::istringstream iss(line);

      iss >> x >> y >> z >> r >> g >> b >>t;
      XBlinkyCoords.push_back(x);
      YBlinkyCoords.push_back(y);
      ZBlinkyCoords.push_back(z);
      RBlinkyColor.push_back(r);
      GBlinkyColor.push_back(g);
      BBlinkyColor.push_back(b);
      countedBlinkies++;

      if ( t > t_minus_1 ){
        blinkiesPerFrame.push_back(countedBlinkies);
        countedBlinkies = 0;
        t_minus_1 = t;
      }
  }
  blinkiesPerFrame.push_back(countedBlinkies);
  file.close();
}

static void light(int i) {
    lightsActivation[i] = ~lightsActivation[i];
}


static void scene(void) {

	glPushMatrix();
    glScalef(.2,.2,.2);
    structure(XBlinkyCoords, YBlinkyCoords, ZBlinkyCoords, RBlinkyColor, GBlinkyColor, BBlinkyColor, blinkiesPerFrame, frameNumber);
	glPopMatrix();
}

/* Fonction executee lors d'un rafraichissement */
/* de la fenetre de dessin                      */

static void display(void) {

  glEnable(GL_LIGHTING);

  //selecting lights to activate
	for (int i = 0; i < 8; ++i) {
    if (lightsActivation[i]) {
    	glEnable(lights[i]);
    }
    else {
    	glDisable(lights[i]);
    }
  }

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glPolygonMode(GL_FRONT_AND_BACK, currentView);
  
  glPushMatrix();
  glTranslatef(0.0F,0.0F,zoom);
  glRotatef(angle[X],1.0F,0.0F,0.0F);
  glRotatef(angle[Y],0.0F,1.0F,0.0F);
  glRotatef(angle[2],0.0F,0.0F,1.0F);
  scene();
  glPopMatrix();
  
  glFlush();
  glutSwapBuffers();
  int error = glGetError();
  if ( error != GL_NO_ERROR )
    printf("Attention erreur %d\n",error);
}

/* Fonction executee lors d'un changement       */
/* de la taille de la fenetre OpenGL            */

static void reshape(int wx,int wy) {
  wTx = wx; 
  wTy = wy; 
  glViewport(0,0,wx,wy); 
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, (float)wx/(float)wy, 0.1, 100.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

/* Fonction executee lorsqu'aucun evenement     */
/* n'est en file d'attente                      */

static void idle(void) {
  if(mouseDiff[X]!=0 || mouseDiff[Y]!=0)
  		glutPostRedisplay();
}

static void idleAnim(void){
  glutPostRedisplay();
}



/* Fonction executee lors de l'appui            */
/* d'une touche alphanumerique du clavier       */

static void keyboard(unsigned char key,int x,int y) {
  printf("K  %4c %4d %4d\n",key,x,y);
  switch(key){
    //espace
    case 0x20:
      currentView = (currentView == GL_FILL) ? GL_LINE : GL_FILL;
      glutPostRedisplay();
      break;

    case '+':
      zoom += 0.5F;
      glutPostRedisplay();
      break;

    case '-':
      zoom -= 0.5F;
      glutPostRedisplay();
      break;
  }
}

/* Fonction executee lors de l'appui            */
/* d'une touche speciale du clavier :           */
/*   - touches de curseur                       */
/*   - touches de fonction                      */

static void special(int specialKey,int x,int y) {
  //printf("S  %4d %4d %4d\n",specialKey,x,y);

  switch (specialKey)
  {
    case GLUT_KEY_F10:
      lighting = ~lighting;
      glutPostRedisplay();
      break;
    case GLUT_KEY_F1:
      light(0);
      glutPostRedisplay();
      break;
    case GLUT_KEY_F2:
      light(1);
      glutPostRedisplay();
      break;
    
    case GLUT_KEY_RIGHT:
      frameNumber+=1;
      if(frameNumber>=blinkiesPerFrame.size()){
        frameNumber=blinkiesPerFrame.size()-1;
      }
      glutPostRedisplay();
      break;

    case GLUT_KEY_LEFT:
      frameNumber-=1;
      if(frameNumber<0){
        frameNumber=0;
      }
      glutPostRedisplay();
      break;
  }
}

/* Fonction executee lors de l'utilisation      */
/* de la souris sur la fenetre                  */

static void mouse(int button,int state,int x,int y) {
}

/* Fonction executee lors du passage            */
/* de la souris sur la fenetre                  */
/* avec un bouton presse                        */

static void mouseMotion(int x, int y) {
    mouseDiff[X] = -x + mousePos[X];
    mouseDiff[Y] = y - mousePos[Y];
    mousePos[X] = x;
    mousePos[Y] = y;
    angle[X] += mouseDiff[Y];
    angle[Y] += mouseDiff[X];
}

/* Fonction executee lors du passage            */
/* de la souris sur la fenetre                  */
/* sans bouton presse                           */
/*
static void passiveMouseMotion(int x,int y) {

}
*/

/* Fonction ex�cut�e automatiquement            */
/* lors de l'ex�cution de la fonction exit()    */

static void clean(void) {
}

/* Fonction principale                          */

int main(int argc,char **argv) {

  atexit(clean);

  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE);
  glutInitWindowSize(wTx,wTy);
  glutInitWindowPosition(wPx,wPy);
  glutCreateWindow("Cuber");
  init();
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(special);
  glutMouseFunc(mouse);
  glutMotionFunc(mouseMotion);
  //glutPassiveMotionFunc(passiveMouseMotion);
  glutReshapeFunc(reshape);
  glutIdleFunc(idle);
  glutDisplayFunc(display);
  glutMainLoop();
  return(0);
}
