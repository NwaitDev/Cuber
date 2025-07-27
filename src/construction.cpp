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
// -----------------------  Bulding the structure  
//********************************************************************************

void structure(
        std::vector<float> xs,
        std::vector<float> ys,
        std::vector<float> zs,
        std::vector<float> rs,
        std::vector<float> gs,
        std::vector<float> bs,
        std::vector<int> blinkiesPerFrame,
        int frameNumber
    ){
    int startFrame=0;
    for(int i = 0; i< frameNumber; ++i){
        startFrame+=blinkiesPerFrame[i];
    }
    for (int i = 0; i<blinkiesPerFrame[frameNumber]; ++i){
        glPushMatrix();
            glTranslatef(xs[startFrame+i], ys[startFrame+i], zs[startFrame+i]);
            makeBlinky(rs[startFrame+i], gs[startFrame+i], bs[startFrame+i]).display();
        glPopMatrix();
    }
}