#include "Object3D.h"

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <math.h>

#ifndef M_PI
#define M_PI 3.14159235
#endif

#include "construction.h"


//********************************************************************************
// -------------------------------------------- BUILDING THE LEGO THING WOOWOWOWOW
//********************************************************************************

void structure(std::vector<float> xs, std::vector<float> ys, std::vector<float> zs){
    size_t i = 0;
    while ((xs.size()>i) && (ys.size()>i) && (zs.size()>i)) {
        glPushMatrix();
            glTranslatef(xs[i], ys[i], zs[i]);
            makeBlinky().display();
        glPopMatrix();
        i++;
    }
}