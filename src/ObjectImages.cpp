#include <stdlib.h>
#include <stdio.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <math.h>

#ifndef M_PI
#define M_PI 3.14159235
#endif

#include "ObjectImages.h"
#include "GeometricalObjects.h"



void blinkyImage(){
	glPushMatrix();
	cube();
	glTranslatef(0.0,0.0,0.5);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glScalef(0.4,0.4,0.4);
	
	for(int i = 0; i<4; ++i){
		glPushMatrix();
		glRotatef(45.0+i*90.0, 0.0, 1.0, 0.0);
		glTranslatef(0.9, 0.0, 0.0);
		cylinder(0.5, 360.0);
		glPopMatrix();
	}
	glPopMatrix();
}