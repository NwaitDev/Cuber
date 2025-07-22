#ifndef OBJECT_3D_H
#define OBJECT_3D_H

#include <GL/gl.h>
#include <cstddef>
#include <cstdlib>
#include <vector>

#include "coords.h"
#include "GeometricalObjects.h"
#include "ObjectImages.h"


class Object3D {
public:
	Object3D(void (*_3DImageFunction)(),float* color);
	Object3D(void (*_3DImageFunction)());
	void getCurrentMatrix();
	void setCurrentMatrix();

	void display();

private:
	
	float *color; //float color[4];
	void (*_3DImageFunction)();
	GLfloat currentMatrix[16];
};

Object3D makeBlinky();


#endif
