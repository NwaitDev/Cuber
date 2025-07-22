#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "GeometricalObjects.h"
#include "coords.h"

#ifndef M_PI
#define M_PI 3.14159
#endif

void mySolidDisc(int ns){

  glNormal3f(0,-1,0);
  glBegin(GL_POLYGON);
  float angle = 0;
  float increment = -2*M_PI/ns;
  for(int i = 0; i<ns; ++i){
    glVertex3f(0.5*cos(angle),0,0.5*sin(angle));
    angle+=increment;
  }
  glEnd();
}

void mySolidCylindre(int ns,int nl) {
  mySolidCylindre(ns,nl,360.0f);
}

void mySolidCylindre(int ns,int nl, float revolution) {
  double hauteur = 1;
  double rayon = 0.5;
  GLboolean nm = glIsEnabled(GL_NORMALIZE);
  if ( !nm )
    glEnable(GL_NORMALIZE);
  float normale[4];
  glGetFloatv(GL_CURRENT_NORMAL,normale);
  glPushMatrix();
  for ( int j = 0 ; j < nl ; j++ ) {
    float hi =(float) (hauteur/2-j*hauteur/nl);
    float hf =(float) (hi-hauteur/nl);
    glBegin(GL_QUAD_STRIP);
    for( int i = 0 ; i <= ns / (360.0f / revolution); i++ ) {
      float a =(float) ((2*M_PI*i)/ns);
      float cs =(float) cos(a);
      float sn =(float) -sin(a);
      glNormal3f(cs,0.0F,sn);
      float x =(float) (rayon*cs);
      float z =(float) (rayon*sn);
      glVertex3f(x,hi,z);
      glVertex3f(x,hf,z); }
    glEnd(); }
  glPopMatrix();
  glNormal3f(normale[0],normale[1],normale[2]);
  if ( !nm )
    glDisable(GL_NORMALIZE);
}

void mySolidCylindreInverted(int ns,int nl) {
  mySolidCylindreInverted(ns,nl,360.0f);
}

void mySolidCylindreInverted(int ns,int nl, float revolution) {
  double hauteur = 1;
  double rayon = 0.5;
  GLboolean nm = glIsEnabled(GL_NORMALIZE);
  if ( !nm )
    glEnable(GL_NORMALIZE);
  float normale[4];
  glGetFloatv(GL_CURRENT_NORMAL,normale);
  glPushMatrix();
  //change culling roation 
  glFrontFace(GL_CW);
  for ( int j = 0 ; j < nl ; j++ ) {
    float hi =(float) (hauteur/2-j*hauteur/nl);
    float hf =(float) (hi-hauteur/nl);
    glBegin(GL_QUAD_STRIP);
    for( int i = 0 ; i <= ns / (360.0f / revolution); i++ ) {
      float a =(float) ((2*M_PI*i)/ns);
      float cs =(float) cos(a);
      float sn =(float) -sin(a);
      glNormal3f(-cs,0.0F,-sn);
      float x =(float) (rayon*cs);
      float z =(float) (rayon*sn);
      glVertex3f(x,hi,z);
      glVertex3f(x,hf,z); }
    glEnd();
  }
  //reset culling roation
  glFrontFace(GL_CCW);
  glPopMatrix();
  glNormal3f(normale[0],normale[1],normale[2]);
  if ( !nm )
    glDisable(GL_NORMALIZE);
}

void mySolidCylindre(int ns,int nl,int bases) {
  double hauteur = 1;
  double rayon = 1;
  
  mySolidCylindre(ns,nl);
  GLboolean nm = glIsEnabled(GL_NORMALIZE);
  if ( !nm )
    glEnable(GL_NORMALIZE);
  float normale[4];
  glGetFloatv(GL_CURRENT_NORMAL,normale);
  glPushMatrix();
  if ( bases ) {
    glBegin(GL_POLYGON);
    glNormal3f(0.0F,1.0F,0.0F);
    for( int i = 0 ; i < ns ; i++ ) {
      float a =(float) ((2*M_PI*i)/ns);
      float cs =(float) cos(a);
      float sn =(float) -sin(a);
      float x =(float) (rayon*cs);
      float z =(float) (rayon*sn);
      glVertex3f(x,(float) (hauteur/2.0F),z); }
    glEnd();
    glBegin(GL_POLYGON);
    glNormal3f(0.0F,-1.0F,0.0F);
    for( int i = 0 ; i < ns ; i++ ) {
      float a =(float) ((2*M_PI*i)/ns);
      float cs =(float) cos(a);
      float sn =(float) sin(a);
      float x =(float) (rayon*cs);
      float z =(float) (rayon*sn);
      glVertex3f(x,(float) (-hauteur/2.0F),z); }
    glEnd(); }
  glPopMatrix();
  glNormal3f(normale[0],normale[1],normale[2]);
  if ( !nm )
    glDisable(GL_NORMALIZE);
}

/* Modelisation geometrique d'un rectangle      */
/* parallele aux axes des x et des z :           */
/*  - de longueur 1                       */
/*  - de hauteur 1                              */
void mySolidFace(){
  glBegin(GL_QUADS);

    glVertex3d(0.5F,0.5F,0);
    glVertex3d(-0.5F,0.5F,0);
    glVertex3d(-0.5F,-0.5F,0);
    glVertex3d(0.5F,-0.5F,0);

  glEnd();
}


void mySolidCross(int withbase){

  float hauteur = 1.0F;
  float largeurFace = 0.5F/3.0F;
  float maxDist = 0.5;

  glBegin(GL_QUADS);
    glNormal3f(0,0,-1);

    glVertex3f(largeurFace/2.0F,hauteur/2.0F,-maxDist);
    glVertex3f(largeurFace/2.0F,-hauteur/2.0F,-maxDist);

    glVertex3f(-largeurFace/2.0F,-hauteur/2.0F,-maxDist);
    glVertex3f(-largeurFace/2.0F,hauteur/2.0F,-maxDist);
    
    glNormal3f(-1,0,0);

    glVertex3f(-largeurFace/2.0F,hauteur/2.0F,-maxDist);
    glVertex3f(-largeurFace/2.0F,-hauteur/2.0F,-maxDist);

    glVertex3f(-largeurFace/2.0F,-hauteur/2.0F,-largeurFace/2.0F);
    glVertex3f(-largeurFace/2.0F,hauteur/2.0F,-largeurFace/2.0F);

    glNormal3f(0,0,-1);

    glVertex3f(-largeurFace/2.0F,hauteur/2.0F,-largeurFace/2.0F);
    glVertex3f(-largeurFace/2.0F,-hauteur/2.0F,-largeurFace/2.0F);

    glVertex3f(-maxDist,-hauteur/2.0F,-largeurFace/2.0F);
    glVertex3f(-maxDist,hauteur/2.0F,-largeurFace/2.0F);

    glNormal3f(-1,0,0);

    glVertex3f(-maxDist,hauteur/2.0F,-largeurFace/2.0F);
    glVertex3f(-maxDist,-hauteur/2.0F,-largeurFace/2.0F);

    glVertex3f(-maxDist,-hauteur/2.0F,largeurFace/2.0F);
    glVertex3f(-maxDist,hauteur/2.0F,largeurFace/2.0F);
    
    glNormal3f(0,0,1);

    glVertex3f(-maxDist,hauteur/2.0F,largeurFace/2.0F);
    glVertex3f(-maxDist,-hauteur/2.0F,largeurFace/2.0F);

    glVertex3f(-largeurFace/2.0F,-hauteur/2.0F,largeurFace/2.0F);
    glVertex3f(-largeurFace/2.0F,hauteur/2.0F,largeurFace/2.0F);

    glNormal3f(-1,0,0);

    glVertex3f(-largeurFace/2.0F,hauteur/2.0F,largeurFace/2.0F);
    glVertex3f(-largeurFace/2.0F,-hauteur/2.0F,largeurFace/2.0F);

    glVertex3f(-largeurFace/2.0F,-hauteur/2.0F,maxDist);
    glVertex3f(-largeurFace/2.0F,hauteur/2.0F,maxDist);
    
    glNormal3f(0,0,1);

    glVertex3f(-largeurFace/2.0F,hauteur/2.0F,maxDist);
    glVertex3f(-largeurFace/2.0F,-hauteur/2.0F,maxDist);

    glVertex3f(largeurFace/2.0F,-hauteur/2.0F,maxDist);
    glVertex3f(largeurFace/2.0F,hauteur/2.0F,maxDist);

    glNormal3f(1,0,0);

    glVertex3f(largeurFace/2.0F,hauteur/2.0F,maxDist);
    glVertex3f(largeurFace/2.0F,-hauteur/2.0F,maxDist);
    
    glVertex3f(largeurFace/2.0F,-hauteur/2.0F,largeurFace/2.0F);
    glVertex3f(largeurFace/2.0F,hauteur/2.0F,largeurFace/2.0F);

    glNormal3f(0,0,1);

    glVertex3f(largeurFace/2.0F,hauteur/2.0F,largeurFace/2.0F);
    glVertex3f(largeurFace/2.0F,-hauteur/2.0F,largeurFace/2.0F);

    glVertex3f(maxDist,-hauteur/2.0F,largeurFace/2.0F);
    glVertex3f(maxDist,hauteur/2.0F,largeurFace/2.0F);

    glNormal3f(1,0,0);

    glVertex3f(maxDist,hauteur/2.0F,largeurFace/2.0F);
    glVertex3f(maxDist,-hauteur/2.0F,largeurFace/2.0F);

    glVertex3f(maxDist,-hauteur/2.0F,-largeurFace/2.0F);
    glVertex3f(maxDist,hauteur/2.0F,-largeurFace/2.0F);

    glNormal3f(0,0,-1);

    glVertex3f(maxDist,hauteur/2.0F,-largeurFace/2.0F);
    glVertex3f(maxDist,-hauteur/2.0F,-largeurFace/2.0F);

    glVertex3f(largeurFace/2.0F,-hauteur/2.0F,-largeurFace/2.0F);
    glVertex3f(largeurFace/2.0F,hauteur/2.0F,-largeurFace/2.0F);

    glNormal3f(1,0,0);

    glVertex3f(largeurFace/2.0F,hauteur/2.0F,-largeurFace/2.0F);
    glVertex3f(largeurFace/2.0F,-hauteur/2.0F,-largeurFace/2.0F);

    glVertex3f(largeurFace/2.0F,-hauteur/2.0F,-maxDist);
    glVertex3f(largeurFace/2.0F,hauteur/2.0F,-maxDist);
    
    if (withbase){
      glNormal3f(0,1,0);
      glVertex3f(largeurFace/2,hauteur/2,-maxDist);
      glVertex3f(-largeurFace/2,hauteur/2,-maxDist);
      glVertex3f(-largeurFace/2,hauteur/2,maxDist);
      glVertex3f(largeurFace/2,hauteur/2,maxDist);

      glNormal3f(0,1,0);
      glVertex3f(maxDist,hauteur/2,-largeurFace/2);
      glVertex3f(-maxDist,hauteur/2,-largeurFace/2);
      glVertex3f(-maxDist,hauteur/2,largeurFace/2);
      glVertex3f(maxDist,hauteur/2,largeurFace/2);
      

      glNormal3f(0,-1,0);
      glVertex3f(largeurFace/2,-hauteur/2,-maxDist);
      glVertex3f(largeurFace/2,-hauteur/2,maxDist);
      glVertex3f(-largeurFace/2,-hauteur/2,maxDist);
      glVertex3f(-largeurFace/2,-hauteur/2,-maxDist);


      glVertex3f(maxDist,-hauteur/2,-largeurFace/2);
      glVertex3f(maxDist,-hauteur/2,largeurFace/2);
      glVertex3f(-maxDist,-hauteur/2,largeurFace/2);
      glVertex3f(-maxDist,-hauteur/2,-largeurFace/2);

    }
    

  glEnd();

}

void innerCross(){
  float hauteur = 1.0F;
  float largeurFaceInterne = 0.5F/3.0F;
  float distMaxInterne = 0.5F;

  GLboolean nm = glIsEnabled(GL_NORMALIZE);
  if ( !nm )
    glEnable(GL_NORMALIZE);
  float normale[4];
  glGetFloatv(GL_CURRENT_NORMAL,normale);
  glPushMatrix();

  // Vertical faces (internal ones) :
  glBegin(GL_QUADS);
    //
    glNormal3f(0,0,1);

    glVertex3f(largeurFaceInterne/2.0F,hauteur/2.0F,-distMaxInterne);
    glVertex3f(-largeurFaceInterne/2.0F,hauteur/2.0F,-distMaxInterne);
    glVertex3f(-largeurFaceInterne/2.0F,-hauteur/2.0F,-distMaxInterne);
    glVertex3f(largeurFaceInterne/2.0F,-hauteur/2.0F,-distMaxInterne);
    

    //
    glNormal3f(1,0,0);

    glVertex3f(-largeurFaceInterne/2.0F,hauteur/2.0F,-distMaxInterne);
    glVertex3f(-largeurFaceInterne/2.0F,hauteur/2.0F,-largeurFaceInterne/2.0F);
    glVertex3f(-largeurFaceInterne/2.0F,-hauteur/2.0F,-largeurFaceInterne/2.0F);
    glVertex3f(-largeurFaceInterne/2.0F,-hauteur/2.0F,-distMaxInterne);

    //
    glNormal3f(0,0,1);

    glVertex3f(-largeurFaceInterne/2.0F,hauteur/2.0F,-largeurFaceInterne/2.0F);
    glVertex3f(-distMaxInterne,hauteur/2.0F,-largeurFaceInterne/2.0F);
    glVertex3f(-distMaxInterne,-hauteur/2.0F,-largeurFaceInterne/2.0F);
    glVertex3f(-largeurFaceInterne/2.0F,-hauteur/2.0F,-largeurFaceInterne/2.0F);

    //

    glNormal3f(1,0,0);

    glVertex3f(-distMaxInterne,hauteur/2.0F,-largeurFaceInterne/2.0F);
    glVertex3f(-distMaxInterne,hauteur/2.0F,largeurFaceInterne/2.0F);
    glVertex3f(-distMaxInterne,-hauteur/2.0F,largeurFaceInterne/2.0F);
    glVertex3f(-distMaxInterne,-hauteur/2.0F,-largeurFaceInterne/2.0F);

    //

    glNormal3f(0,0,-1);

    glVertex3f(-distMaxInterne,hauteur/2.0F,largeurFaceInterne/2.0F);
    glVertex3f(-largeurFaceInterne/2.0F,hauteur/2.0F,largeurFaceInterne/2.0F);
    glVertex3f(-largeurFaceInterne/2.0F,-hauteur/2.0F,largeurFaceInterne/2.0F);
    glVertex3f(-distMaxInterne,-hauteur/2.0F,largeurFaceInterne/2.0F);

    //

    glNormal3f(1,0,0);

    glVertex3f(-largeurFaceInterne/2.0F,hauteur/2.0F,largeurFaceInterne/2.0F);
    glVertex3f(-largeurFaceInterne/2.0F,hauteur/2.0F,distMaxInterne);
    glVertex3f(-largeurFaceInterne/2.0F,-hauteur/2.0F,distMaxInterne);
    glVertex3f(-largeurFaceInterne/2.0F,-hauteur/2.0F,largeurFaceInterne/2.0F);

    //
    glNormal3f(0,0,-1);

    glVertex3f(-largeurFaceInterne/2.0F,hauteur/2.0F,distMaxInterne);
    glVertex3f(largeurFaceInterne/2.0F,hauteur/2.0F,distMaxInterne);
    glVertex3f(largeurFaceInterne/2.0F,-hauteur/2.0F,distMaxInterne);
    glVertex3f(-largeurFaceInterne/2.0F,-hauteur/2.0F,distMaxInterne);

    //
    glNormal3f(-1,0,0);

    glVertex3f(largeurFaceInterne/2.0F,hauteur/2.0F,distMaxInterne);
    glVertex3f(largeurFaceInterne/2.0F,hauteur/2.0F,largeurFaceInterne/2.0F);
    glVertex3f(largeurFaceInterne/2.0F,-hauteur/2.0F,largeurFaceInterne/2.0F);
    glVertex3f(largeurFaceInterne/2.0F,-hauteur/2.0F,distMaxInterne);

    //
    glNormal3f(0,0,-1);

    glVertex3f(largeurFaceInterne/2.0F,hauteur/2.0F,largeurFaceInterne/2.0F);
    glVertex3f(distMaxInterne,hauteur/2.0F,largeurFaceInterne/2.0F);
    glVertex3f(distMaxInterne,-hauteur/2.0F,largeurFaceInterne/2.0F);
    glVertex3f(largeurFaceInterne/2.0F,-hauteur/2.0F,largeurFaceInterne/2.0F);

    //
    glNormal3f(-1,0,0);

    glVertex3f(distMaxInterne,hauteur/2.0F,largeurFaceInterne/2.0F);
    glVertex3f(distMaxInterne,hauteur/2.0F,-largeurFaceInterne/2.0F);
    glVertex3f(distMaxInterne,-hauteur/2.0F,-largeurFaceInterne/2.0F);
    glVertex3f(distMaxInterne,-hauteur/2.0F,largeurFaceInterne/2.0F);

    //
    glNormal3f(0,0,1);

    glVertex3f(distMaxInterne,hauteur/2.0F,-largeurFaceInterne/2.0F);
    glVertex3f(largeurFaceInterne/2.0F,hauteur/2.0F,-largeurFaceInterne/2.0F);
    glVertex3f(largeurFaceInterne/2.0F,-hauteur/2.0F,-largeurFaceInterne/2.0F);
    glVertex3f(distMaxInterne,-hauteur/2.0F,-largeurFaceInterne/2.0F);

    //
    glNormal3f(-1,0,0);

    glVertex3f(largeurFaceInterne/2.0F,hauteur/2.0F,-largeurFaceInterne/2.0F);
    glVertex3f(largeurFaceInterne/2.0F,hauteur/2.0F,-distMaxInterne);
    glVertex3f(largeurFaceInterne/2.0F,-hauteur/2.0F,-distMaxInterne);
    glVertex3f(largeurFaceInterne/2.0F,-hauteur/2.0F,-largeurFaceInterne/2.0F);
  glEnd();
  
  glPopMatrix();
}


void thickCross(){

  float hauteur = 1.0F;
  float largeurFaceInterne = 0.5F/3.0F;
  float largeurFaceExterne = largeurFaceInterne*2;
  float distMaxInterne = 0.5F;
  float distMaxExterne = 0.6F;


  GLboolean nm = glIsEnabled(GL_NORMALIZE);
  if ( !nm )
    glEnable(GL_NORMALIZE);
  float normale[4];
  glGetFloatv(GL_CURRENT_NORMAL,normale);
  glPushMatrix();
  
  glBegin(GL_QUADS);
    
    //vertical faces (external ones):
    //
    glNormal3f(0,0,-1);

    glVertex3f(largeurFaceExterne/2.0F,hauteur/2.0F,-distMaxExterne);
    glVertex3f(largeurFaceExterne/2.0F,-hauteur/2.0F,-distMaxExterne);

    glVertex3f(-largeurFaceExterne/2.0F,-hauteur/2.0F,-distMaxExterne);
    glVertex3f(-largeurFaceExterne/2.0F,hauteur/2.0F,-distMaxExterne);
    

    //
    glNormal3f(-1,0,0);

    glVertex3f(-largeurFaceExterne/2.0F,hauteur/2.0F,-distMaxExterne);
    glVertex3f(-largeurFaceExterne/2.0F,-hauteur/2.0F,-distMaxExterne);

    glVertex3f(-largeurFaceExterne/2.0F,-hauteur/2.0F,-largeurFaceExterne/2.0F);
    glVertex3f(-largeurFaceExterne/2.0F,hauteur/2.0F,-largeurFaceExterne/2.0F);

    //
    glNormal3f(0,0,-1);

    glVertex3f(-largeurFaceExterne/2.0F,hauteur/2.0F,-largeurFaceExterne/2.0F);
    glVertex3f(-largeurFaceExterne/2.0F,-hauteur/2.0F,-largeurFaceExterne/2.0F);

    glVertex3f(-distMaxExterne,-hauteur/2.0F,-largeurFaceExterne/2.0F);
    glVertex3f(-distMaxExterne,hauteur/2.0F,-largeurFaceExterne/2.0F);

    //

    glNormal3f(-1,0,0);

    glVertex3f(-distMaxExterne,hauteur/2.0F,-largeurFaceExterne/2.0F);
    glVertex3f(-distMaxExterne,-hauteur/2.0F,-largeurFaceExterne/2.0F);

    glVertex3f(-distMaxExterne,-hauteur/2.0F,largeurFaceExterne/2.0F);
    glVertex3f(-distMaxExterne,hauteur/2.0F,largeurFaceExterne/2.0F);

    //

    glNormal3f(0,0,1);

    glVertex3f(-distMaxExterne,hauteur/2.0F,largeurFaceExterne/2.0F);
    glVertex3f(-distMaxExterne,-hauteur/2.0F,largeurFaceExterne/2.0F);

    glVertex3f(-largeurFaceExterne/2.0F,-hauteur/2.0F,largeurFaceExterne/2.0F);
    glVertex3f(-largeurFaceExterne/2.0F,hauteur/2.0F,largeurFaceExterne/2.0F);

    //

    glNormal3f(-1,0,0);

    glVertex3f(-largeurFaceExterne/2.0F,hauteur/2.0F,largeurFaceExterne/2.0F);
    glVertex3f(-largeurFaceExterne/2.0F,-hauteur/2.0F,largeurFaceExterne/2.0F);

    glVertex3f(-largeurFaceExterne/2.0F,-hauteur/2.0F,distMaxExterne);
    glVertex3f(-largeurFaceExterne/2.0F,hauteur/2.0F,distMaxExterne);

    //
    glNormal3f(0,0,1);

    glVertex3f(-largeurFaceExterne/2.0F,hauteur/2.0F,distMaxExterne);
    glVertex3f(-largeurFaceExterne/2.0F,-hauteur/2.0F,distMaxExterne);

    glVertex3f(largeurFaceExterne/2.0F,-hauteur/2.0F,distMaxExterne);
    glVertex3f(largeurFaceExterne/2.0F,hauteur/2.0F,distMaxExterne);

    //
    glNormal3f(1,0,0);

    glVertex3f(largeurFaceExterne/2.0F,hauteur/2.0F,distMaxExterne);
    glVertex3f(largeurFaceExterne/2.0F,-hauteur/2.0F,distMaxExterne);
    
    glVertex3f(largeurFaceExterne/2.0F,-hauteur/2.0F,largeurFaceExterne/2.0F);
    glVertex3f(largeurFaceExterne/2.0F,hauteur/2.0F,largeurFaceExterne/2.0F);

    //
    glNormal3f(0,0,1);

    glVertex3f(largeurFaceExterne/2.0F,hauteur/2.0F,largeurFaceExterne/2.0F);
    glVertex3f(largeurFaceExterne/2.0F,-hauteur/2.0F,largeurFaceExterne/2.0F);

    glVertex3f(distMaxExterne,-hauteur/2.0F,largeurFaceExterne/2.0F);
    glVertex3f(distMaxExterne,hauteur/2.0F,largeurFaceExterne/2.0F);

    //
    glNormal3f(1,0,0);

    glVertex3f(distMaxExterne,hauteur/2.0F,largeurFaceExterne/2.0F);
    glVertex3f(distMaxExterne,-hauteur/2.0F,largeurFaceExterne/2.0F);

    glVertex3f(distMaxExterne,-hauteur/2.0F,-largeurFaceExterne/2.0F);
    glVertex3f(distMaxExterne,hauteur/2.0F,-largeurFaceExterne/2.0F);

    //
    glNormal3f(0,0,-1);

    glVertex3f(distMaxExterne,hauteur/2.0F,-largeurFaceExterne/2.0F);
    glVertex3f(distMaxExterne,-hauteur/2.0F,-largeurFaceExterne/2.0F);

    glVertex3f(largeurFaceExterne/2.0F,-hauteur/2.0F,-largeurFaceExterne/2.0F);
    glVertex3f(largeurFaceExterne/2.0F,hauteur/2.0F,-largeurFaceExterne/2.0F);

    //
    glNormal3f(1,0,0);

    glVertex3f(largeurFaceExterne/2.0F,hauteur/2.0F,-largeurFaceExterne/2.0F);
    glVertex3f(largeurFaceExterne/2.0F,-hauteur/2.0F,-largeurFaceExterne/2.0F);

    glVertex3f(largeurFaceExterne/2.0F,-hauteur/2.0F,-distMaxExterne);
    glVertex3f(largeurFaceExterne/2.0F,hauteur/2.0F,-distMaxExterne);
    
  glEnd();
    // Vertical faces (internal ones) :
    
    innerCross();

    //horizontal faces (base)
    
    //face du bas (désolé j'ai mis les normales à l'envers parce que j'ai tourné dans le sens indirect pour mes facettes)

    glFrontFace(GL_CW);

    glBegin(GL_QUADS);

    glNormal3f(0,-1,0);
    glVertex3f(-largeurFaceExterne/2,-hauteur/2,distMaxExterne);
    glVertex3f(largeurFaceExterne/2,-hauteur/2,distMaxExterne);
    glVertex3f(largeurFaceExterne/2,-hauteur/2,distMaxInterne);
    glVertex3f(-largeurFaceExterne/2,-hauteur/2,distMaxInterne);
    
    glVertex3f(largeurFaceExterne/2,-hauteur/2,distMaxInterne);
    glVertex3f(largeurFaceExterne/2,-hauteur/2,largeurFaceInterne/2);
    glVertex3f(largeurFaceInterne/2,-hauteur/2,largeurFaceInterne/2);
    glVertex3f(largeurFaceInterne/2,-hauteur/2,distMaxInterne);

    glVertex3f(largeurFaceExterne/2,-hauteur/2,largeurFaceExterne/2);
    glVertex3f(distMaxExterne,-hauteur/2,largeurFaceExterne/2);
    glVertex3f(distMaxExterne,-hauteur/2,largeurFaceInterne/2);
    glVertex3f(largeurFaceExterne/2,-hauteur/2,largeurFaceInterne/2);

    glVertex3f(distMaxExterne,-hauteur/2,largeurFaceInterne/2);
    glVertex3f(distMaxExterne,-hauteur/2,-largeurFaceExterne/2);
    glVertex3f(distMaxInterne,-hauteur/2,-largeurFaceExterne/2);
    glVertex3f(distMaxInterne,-hauteur/2,largeurFaceInterne/2);

    glVertex3f(largeurFaceInterne/2,-hauteur/2,-largeurFaceInterne/2);
    glVertex3f(distMaxInterne,-hauteur/2,-largeurFaceInterne/2);
    glVertex3f(distMaxInterne,-hauteur/2,-largeurFaceExterne/2);
    glVertex3f(largeurFaceInterne/2,-hauteur/2,-largeurFaceExterne/2);

    glVertex3f(largeurFaceInterne/2,-hauteur/2,-largeurFaceInterne/2);
    glVertex3f(largeurFaceExterne/2,-hauteur/2,-largeurFaceInterne/2);
    glVertex3f(largeurFaceExterne/2,-hauteur/2,-distMaxExterne);
    glVertex3f(largeurFaceInterne/2,-hauteur/2,-distMaxExterne);
    // la moitié ! on y est presque

    glVertex3f(largeurFaceExterne/2,-hauteur/2,-distMaxExterne);
    glVertex3f(-largeurFaceExterne/2,-hauteur/2,-distMaxExterne);
    glVertex3f(-largeurFaceExterne/2,-hauteur/2,-distMaxInterne);
    glVertex3f(largeurFaceExterne/2,-hauteur/2,-distMaxInterne);
    
    glVertex3f(-largeurFaceExterne/2,-hauteur/2,-distMaxInterne);
    glVertex3f(-largeurFaceExterne/2,-hauteur/2,-largeurFaceInterne/2);
    glVertex3f(-largeurFaceInterne/2,-hauteur/2,-largeurFaceInterne/2);
    glVertex3f(-largeurFaceInterne/2,-hauteur/2,-distMaxInterne);

    glVertex3f(-largeurFaceExterne/2,-hauteur/2,-largeurFaceExterne/2);
    glVertex3f(-distMaxExterne,-hauteur/2,-largeurFaceExterne/2);
    glVertex3f(-distMaxExterne,-hauteur/2,-largeurFaceInterne/2);
    glVertex3f(-largeurFaceExterne/2,-hauteur/2,-largeurFaceInterne/2);

    glVertex3f(-distMaxExterne,-hauteur/2,-largeurFaceInterne/2);
    glVertex3f(-distMaxExterne,-hauteur/2,largeurFaceExterne/2);
    glVertex3f(-distMaxInterne,-hauteur/2,largeurFaceExterne/2);
    glVertex3f(-distMaxInterne,-hauteur/2,-largeurFaceInterne/2);

    glVertex3f(-largeurFaceInterne/2,-hauteur/2,largeurFaceInterne/2);
    glVertex3f(-distMaxInterne,-hauteur/2,largeurFaceInterne/2);
    glVertex3f(-distMaxInterne,-hauteur/2,largeurFaceExterne/2);
    glVertex3f(-largeurFaceInterne/2,-hauteur/2,largeurFaceExterne/2);

    glVertex3f(-largeurFaceInterne/2,-hauteur/2,largeurFaceInterne/2);
    glVertex3f(-largeurFaceExterne/2,-hauteur/2,largeurFaceInterne/2);
    glVertex3f(-largeurFaceExterne/2,-hauteur/2,distMaxExterne);
    glVertex3f(-largeurFaceInterne/2,-hauteur/2,distMaxExterne);

    glEnd();

    glFrontFace(GL_CCW);

    glBegin(GL_QUADS);

    //face du haut (désolé j'ai mis les normales à l'envers parce que j'ai tourné dans le sens indirect pour mes facettes)
    glNormal3f(0,1,0);
    glVertex3f(-largeurFaceExterne/2,hauteur/2,distMaxExterne);
    glVertex3f(largeurFaceExterne/2,hauteur/2,distMaxExterne);
    glVertex3f(largeurFaceExterne/2,hauteur/2,distMaxInterne);
    glVertex3f(-largeurFaceExterne/2,hauteur/2,distMaxInterne);
    
    glVertex3f(largeurFaceExterne/2,hauteur/2,distMaxInterne);
    glVertex3f(largeurFaceExterne/2,hauteur/2,largeurFaceInterne/2);
    glVertex3f(largeurFaceInterne/2,hauteur/2,largeurFaceInterne/2);
    glVertex3f(largeurFaceInterne/2,hauteur/2,distMaxInterne);

    glVertex3f(largeurFaceExterne/2,hauteur/2,largeurFaceExterne/2);
    glVertex3f(distMaxExterne,hauteur/2,largeurFaceExterne/2);
    glVertex3f(distMaxExterne,hauteur/2,largeurFaceInterne/2);
    glVertex3f(largeurFaceExterne/2,hauteur/2,largeurFaceInterne/2);

    glVertex3f(distMaxExterne,hauteur/2,largeurFaceInterne/2);
    glVertex3f(distMaxExterne,hauteur/2,-largeurFaceExterne/2);
    glVertex3f(distMaxInterne,hauteur/2,-largeurFaceExterne/2);
    glVertex3f(distMaxInterne,hauteur/2,largeurFaceInterne/2);

    glVertex3f(largeurFaceInterne/2,hauteur/2,-largeurFaceInterne/2);
    glVertex3f(distMaxInterne,hauteur/2,-largeurFaceInterne/2);
    glVertex3f(distMaxInterne,hauteur/2,-largeurFaceExterne/2);
    glVertex3f(largeurFaceInterne/2,hauteur/2,-largeurFaceExterne/2);

    glVertex3f(largeurFaceInterne/2,hauteur/2,-largeurFaceInterne/2);
    glVertex3f(largeurFaceExterne/2,hauteur/2,-largeurFaceInterne/2);
    glVertex3f(largeurFaceExterne/2,hauteur/2,-distMaxExterne);
    glVertex3f(largeurFaceInterne/2,hauteur/2,-distMaxExterne);
    // la moitié ! on y est presque

    glVertex3f(largeurFaceExterne/2,hauteur/2,-distMaxExterne);
    glVertex3f(-largeurFaceExterne/2,hauteur/2,-distMaxExterne);
    glVertex3f(-largeurFaceExterne/2,hauteur/2,-distMaxInterne);
    glVertex3f(largeurFaceExterne/2,hauteur/2,-distMaxInterne);
    
    glVertex3f(-largeurFaceExterne/2,hauteur/2,-distMaxInterne);
    glVertex3f(-largeurFaceExterne/2,hauteur/2,-largeurFaceInterne/2);
    glVertex3f(-largeurFaceInterne/2,hauteur/2,-largeurFaceInterne/2);
    glVertex3f(-largeurFaceInterne/2,hauteur/2,-distMaxInterne);

    glVertex3f(-largeurFaceExterne/2,hauteur/2,-largeurFaceExterne/2);
    glVertex3f(-distMaxExterne,hauteur/2,-largeurFaceExterne/2);
    glVertex3f(-distMaxExterne,hauteur/2,-largeurFaceInterne/2);
    glVertex3f(-largeurFaceExterne/2,hauteur/2,-largeurFaceInterne/2);

    glVertex3f(-distMaxExterne,hauteur/2,-largeurFaceInterne/2);
    glVertex3f(-distMaxExterne,hauteur/2,largeurFaceExterne/2);
    glVertex3f(-distMaxInterne,hauteur/2,largeurFaceExterne/2);
    glVertex3f(-distMaxInterne,hauteur/2,-largeurFaceInterne/2);

    glVertex3f(-largeurFaceInterne/2,hauteur/2,largeurFaceInterne/2);
    glVertex3f(-distMaxInterne,hauteur/2,largeurFaceInterne/2);
    glVertex3f(-distMaxInterne,hauteur/2,largeurFaceExterne/2);
    glVertex3f(-largeurFaceInterne/2,hauteur/2,largeurFaceExterne/2);

    glVertex3f(-largeurFaceInterne/2,hauteur/2,largeurFaceInterne/2);
    glVertex3f(-largeurFaceExterne/2,hauteur/2,largeurFaceInterne/2);
    glVertex3f(-largeurFaceExterne/2,hauteur/2,distMaxExterne);
    glVertex3f(-largeurFaceInterne/2,hauteur/2,distMaxExterne);


  glEnd();
  glPopMatrix();
  glNormal3f(normale[0],normale[1],normale[2]);
  if ( !nm )
    glDisable(GL_NORMALIZE);
}

void mySolidGear(int nbTooth){
  cylinder(0.2);
  float increment = -M_PI/(float)nbTooth;
  float partialIncr = increment/3;
  float angle = 0.0F;
  float x,z;
  glBegin(GL_QUADS);
  for(int i = 0; i < nbTooth;++i){
    
    x = cos(angle)*1;
    z = sin(angle)*1;
    glNormal3f(cos(angle+partialIncr/2),0,sin(angle+partialIncr/2));
    glVertex3f(x,0.5,z);
    glVertex3f(x,-0.5,z);
    angle+=partialIncr;
    x = cos(angle)*1;
    z = sin(angle)*1;
    glVertex3f(x,-0.5,z);
    glVertex3f(x,0.5,z);

    glNormal3f(-cos(angle+M_PI/2-partialIncr/2),0,-sin(angle+M_PI/2-partialIncr/2));
    glVertex3f(x,-0.5,z);
    glVertex3f(x,0.5,z);
    angle+=partialIncr;
    x = cos(angle)*0.5;
    z = sin(angle)*0.5;
    glVertex3f(x,0.5,z);
    glVertex3f(x,-0.5,z);

    glNormal3f(cos(angle+partialIncr/2),0,sin(angle+partialIncr/2));
    glVertex3f(x,0.5,z);
    glVertex3f(x,-0.5,z);
    angle+=increment;
    x = cos(angle)*0.5;
    z = sin(angle)*0.5;
    glVertex3f(x,-0.5,z);
    glVertex3f(x,0.5,z);

    glNormal3f(-cos(angle-M_PI/2+partialIncr/2),0,-sin(angle-M_PI/2+partialIncr/2));
    glVertex3f(x,-0.5,z);
    glVertex3f(x,0.5,z);
    angle+=partialIncr;
    x = cos(angle)*1;
    z = sin(angle)*1;
    glVertex3f(x,0.5,z);
    glVertex3f(x,-0.5,z);
  }
  
  glEnd();

  
  
  glBegin(GL_QUADS);
  angle = -partialIncr;
  for(int i = 0; i < nbTooth;++i){
    glNormal3f(0,1,0);
    x = cos(angle)*0.5;
    z = sin(angle)*0.5;
    glVertex3f(x,0.5,z);

    angle+=partialIncr;
    x = cos(angle)*1;
    z = sin(angle)*1;
    glVertex3f(x,0.5,z);

    angle+=partialIncr;
    x = cos(angle)*1;
    z = sin(angle)*1;
    glVertex3f(x,0.5,z);

    angle+=partialIncr;
    x = cos(angle)*0.5;
    z = sin(angle)*0.5;
    glVertex3f(x,0.5,z);

    angle+=increment;
  }
  angle=-partialIncr;
  for(int i = 0; i < nbTooth;++i){
    glNormal3f(0,-1,0);
    x = cos(angle)*0.5;
    z = sin(angle)*0.5;
    glVertex3f(x,-0.5,z);

    angle+=partialIncr;
    x = cos(angle)*1;
    z = sin(angle)*1;
    glVertex3f(x,-0.5,z);

    angle+=partialIncr;
    x = cos(angle)*1;
    z = sin(angle)*1;
    glVertex3f(x,-0.5,z);

    angle+=partialIncr;
    x = cos(angle)*0.5;
    z = sin(angle)*0.5;
    glVertex3f(x,-0.5,z);

    angle+=increment;
  }
  glEnd();
}

void drawCircle(float radius, float thickness, float revolution){
    // Define the number of vertices for the outer and inner circles
    int numVerticesOuter = 60;
    int numVerticesInner = 60;

    // Calculate the angle between each vertex
    float angle = 2 * M_PI / numVerticesOuter;

    // Calculate the radius for the inner circle
    float innerRadius = radius - thickness;

	struct Position{
		float x;
		float y;
	};

	// list of vertices
	Position verticiesOuter [numVerticesOuter];
	Position verticiesInner [numVerticesInner];

    // outer circle
    for (int i = 0; i < numVerticesOuter; i++)
    {
        float theta = i * angle;
        float vx = radius * cos(theta);
        float vy = radius * sin(theta);
        verticiesOuter[i].x = vx;
		    verticiesOuter[i].y = vy;
    }

    // inner circle
    for (int i = 0; i < numVerticesInner; i++)
    {
        float theta = i * angle;
        float vx = innerRadius * cos(theta);
        float vy = innerRadius * sin(theta);
        verticiesInner[i].x = vx;
		    verticiesInner[i].y = vy;
    }

	// draw the border with triangles
	glBegin(GL_TRIANGLE_STRIP);

  int i = 0;
	for (; i < numVerticesInner / (360 / revolution); i++)
	{
		//set the normal for the outer circle
		glNormal3f(0,0,-1);

		//link the outer circle to the inner circle
		glVertex3f(verticiesOuter[i].x, verticiesOuter[i].y, 0);
		glVertex3f(verticiesInner[i].x, verticiesInner[i].y, 0);
	}
  if (i == numVerticesInner){
    glVertex2f(verticiesOuter[0].x, verticiesOuter[0].y);
    glVertex2f(verticiesInner[0].x, verticiesInner[0].y);
  }

	glEnd();
}



void cylinder(float borderSize, float revolution){
	glPushMatrix();
	mySolidCylindre(50, 50, revolution);


  glPushMatrix();

    glRotatef(revolution,0,1,0);

    glPushMatrix();
    glTranslatef(0,0.5,0);
    glRotatef(90,1,0,0);
    drawCircle(0.5,borderSize/2, revolution);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,-0.5,0);
    glRotatef(-90,1,0,0);
    glRotatef(360 - revolution,0,0,1);
    drawCircle(0.5,borderSize/2, revolution);
    glPopMatrix();

  glPopMatrix();
  if(borderSize > 0 && borderSize < 1){
    glScalef(1 - borderSize, 1, 1 - borderSize);
	  mySolidCylindreInverted(50, 50, revolution);
  }
	glPopMatrix();
}

void cylinder(float borderSize){
  cylinder(borderSize, 360);
}


void cube(){
	glutSolidCube(1);
}

void thickSpiral3d(int nbSpires){
  GLboolean nm = glIsEnabled(GL_NORMALIZE);
  if ( !nm )
    glEnable(GL_NORMALIZE);
  float normale[4];
  glGetFloatv(GL_CURRENT_NORMAL,normale);


  float thickness = 1.0/(3*nbSpires);
  int ptsPerSpire = 50;
  int nbPts = nbSpires*ptsPerSpire;
  float incr = 2*M_PI/ptsPerSpire;
  float dy = 1.0F/nbPts;
  
  float angle = 0;
  float y = -0.5;
  float nextAngle = incr;

  Pos3D pos(cos(angle)*0.5,y,sin(angle)*0.5);
  Pos3D nextPos(cos(nextAngle),y+dy,sin(nextAngle));

  glBegin(GL_TRIANGLES);
    
    Dir3D commonVec0(pos.x,pos.y,pos.z,nextPos.x,nextPos.y,nextPos.z);
      
    Dir3D upperVec0(pos.x,pos.y,pos.z,nextPos.x*0.5,pos.y+thickness,nextPos.z*0.5);
    Dir3D upperNormal0 = upperVec0^commonVec0;
    glNormal3f(upperNormal0.x,upperNormal0.y,upperNormal0.z);

    glVertex3f(nextPos.x,nextPos.y,nextPos.z);
    glVertex3f(pos.x,pos.y,pos.z);
    glVertex3f(nextPos.x*0.5,nextPos.y+thickness,nextPos.z*0.5);
    
    Dir3D downerVec0(pos.x,pos.y,pos.z,nextPos.x*0.5,pos.y-thickness,nextPos.z*0.5);
    Dir3D downerNormal0 = commonVec0^downerVec0;
    glNormal3f(downerNormal0.x,downerNormal0.y,downerNormal0.z);

    glVertex3f(nextPos.x,nextPos.y,nextPos.z);
    glVertex3f(nextPos.x*0.5,nextPos.y-thickness,nextPos.z*0.5);
    glVertex3f(pos.x,pos.y,pos.z);
    
  glEnd();

  glBegin(GL_QUADS);
    for(int i = 0; i < nbPts-2; ++i){
      pos.x = nextPos.x;
      pos.y = nextPos.y;
      pos.z = nextPos.z;
      angle = nextAngle;
      nextAngle+=incr;
      y+=dy;
      nextPos.x= cos(nextAngle);
      nextPos.y= y;
      nextPos.z= sin(nextAngle);
      
      Dir3D commonVec(pos.x,pos.y,pos.z,nextPos.x,nextPos.y,nextPos.z);
      
      Dir3D upperVec(pos.x,pos.y,pos.z,pos.x*0.5,pos.y+thickness,pos.z*0.5);
      Dir3D upperNormal = upperVec^commonVec;
      glNormal3f(upperNormal.x,upperNormal.y,upperNormal.z);
      glVertex3f(pos.x,pos.y,pos.z);
      glVertex3f(nextPos.x,nextPos.y,nextPos.z);
      glVertex3f(nextPos.x*0.5,nextPos.y+thickness,nextPos.z*0.5);
      glVertex3f(pos.x*0.5,pos.y+thickness,pos.z*0.5);
      
      Dir3D downerVec(pos.x,pos.y,pos.z,pos.x*0.5,pos.y-thickness,pos.z*0.5);
      Dir3D downerNormal = commonVec^downerVec;
      glNormal3f(downerNormal.x,downerNormal.y,downerNormal.z);
      glVertex3f(pos.x,pos.y,pos.z);
      glVertex3f(pos.x*0.5,pos.y-thickness,pos.z*0.5);
      glVertex3f(nextPos.x*0.5,nextPos.y-thickness,nextPos.z*0.5);
      glVertex3f(nextPos.x,nextPos.y,nextPos.z);
      
    }
  glEnd();
  
  pos.x = nextPos.x;
  pos.y = nextPos.y;
  pos.z = nextPos.z;
  angle = nextAngle;
  nextAngle+=incr;
  nextPos.x= cos(nextAngle)*0.5;
  nextPos.y= y;
  nextPos.z= sin(nextAngle*0.5);    

  glBegin(GL_TRIANGLES);
    
    Dir3D commonVec1(pos.x,pos.y,pos.z,nextPos.x,nextPos.y,nextPos.z);
      
    Dir3D upperVec1(pos.x,pos.y,pos.z,pos.x*0.5,pos.y+thickness,pos.z*0.5);
    Dir3D upperNormal1 = upperVec1^commonVec1;
    glNormal3f(upperNormal1.x,upperNormal1.y,upperNormal1.z);

    glVertex3f(nextPos.x,nextPos.y,nextPos.z);
    glVertex3f(pos.x,pos.y,pos.z);
    glVertex3f(pos.x*0.5,pos.y+thickness,pos.z*0.5);

    Dir3D downerVec1(pos.x,pos.y,pos.z,pos.x*0.5,pos.y-thickness,pos.z*0.5);
    Dir3D downerNormal1 = commonVec1^downerVec1;
    glNormal3f(downerNormal1.x,downerNormal1.y,downerNormal1.z);

    glVertex3f(nextPos.x,nextPos.y,nextPos.z);
    glVertex3f(pos.x*0.5,pos.y-thickness,pos.z*0.5);
    glVertex3f(pos.x,pos.y,pos.z);
  glEnd();
  
  glNormal3f(normale[0],normale[1],normale[2]);
  if ( !nm )
    glDisable(GL_NORMALIZE);
}