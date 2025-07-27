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
	Object3D(void (*_3DImageFunction)(), float* color);
	Object3D(void (*_3DImageFunction)());
	Object3D(void (*_3DImageFunction)(), float r, float g, float b);
	void getCurrentMatrix();
	void setCurrentMatrix();

	void display();

private:
	
	float r,g,b,alpha;
	float color[4];
	void (*_3DImageFunction)();
	GLfloat currentMatrix[16];
};

Object3D makeBlinky(float r, float g, float b);


#endif
