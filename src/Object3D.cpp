#include <vector>
#include <iostream>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <math.h>

#ifndef M_PI
#define M_PI 3.14159235
#endif

#include "Object3D.h"

//different colors of the bricks
 [[maybe_unused]] float rouge[4] = { 1.0F,0.0F,0.0F,0.5F };
 [[maybe_unused]] float vert[4] = { 0.0F,1.0F,0.0F,0.5F };
 [[maybe_unused]] float bleu[4] = { 0.0F,0.0F,1.0F,0.5F };
 [[maybe_unused]] float blanc[4] = { 0.9F,0.9F,0.9F,0.5F };
 [[maybe_unused]] float beige[4] = { 0.8F,0.6F,0.4F,0.5F };
 [[maybe_unused]] float noir[4] = { 0.1F,0.1F,0.1F,0.5F };
 [[maybe_unused]] float bleufonce[4] = { 34.0F/255.0F, 104.0F/255.0F, 192.0F/255.0F,0.5F };
 [[maybe_unused]] float gris[4] = { 0.5F,0.5F,0.5F,0.5F };
 [[maybe_unused]] float marron[4] = { 155.0F/255.0F, 138.0F/255.0F, 112.0F/255.0F,0.5F };
 [[maybe_unused]] float bleuclair[4] = { 110.0F/255.0F, 182.0F/255.0F, 209.0F/255.0F,0.5F };

//useful functions



float compute_angle( Dir3D vector1, Dir3D vector2) {
    float angle;
    float dot_product = vector1*vector2;
    float magnitude1 = sqrt(vector1*vector1);
    float magnitude2 = sqrt(vector2*vector2);
    angle = acos(dot_product / (magnitude1 * magnitude2));
    return angle;
}

void funcToTest(){
    std::cout<<"Hello World ! \n";
}

//************************************************************************************
//----------------------------------Defining the classes to work with-----------------
//************************************************************************************


Object3D::Object3D(void (*_3DImageFunction)(), float* color) : color(color),_3DImageFunction(_3DImageFunction){}

Object3D::Object3D(void (*_3DImageFunction)()) : color(vert), _3DImageFunction(_3DImageFunction) {}


void Object3D::getCurrentMatrix(){
    glGetFloatv(GL_MODELVIEW_MATRIX, this->currentMatrix); // retrieve the current modelview matrix and save it to currentMatrix
}

void Object3D::setCurrentMatrix(){
    glLoadIdentity();
    glMultMatrixf(this->currentMatrix);
}

void Object3D::display(){
    glMaterialfv(GL_FRONT,GL_DIFFUSE,this->color);
	_3DImageFunction();
}

//*****************************************************
//____________Wrapping the images in objects___________
//*****************************************************

Object3D makeBlinky(){
    return Object3D(blinkyImage);
}