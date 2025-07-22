#include <iostream>
#include "coords.h"


//implementation of the parent class : CH3D
CH3D::CH3D(void):x(0.0F),y(0.0F),z(0.0F),w(1.0F){}

CH3D::CH3D(float x, float y, float z, float w):x(x),y(y),z(z),w(w){}

CH3D::CH3D(const CH3D &ch):x(ch.x),y(ch.y),z(ch.z),w(ch.w){}

CH3D::~CH3D(void){}

void CH3D::update(float x,float y,float z){ this->x = x;this->y = y;this->z = z;}



//implementation of a child class : Pos3D
Pos3D::Pos3D(void):CH3D(){}

Pos3D::Pos3D(float x, float y, float z):CH3D(x,y,z,1.0F){}

Pos3D::Pos3D(const Pos3D &p):CH3D(p){}

Pos3D::~Pos3D(void){}

Pos3D Pos3D::operator+(const Pos3D other){
	Pos3D pos(this->x+other.x,this->y+other.y,this->z+other.z);
	return pos;
}

Pos3D Pos3D::operator-(const Pos3D other){
	Pos3D pos(this->x-other.x,this->y-other.y,this->z-other.z);
	return pos;
}

//implementation of a child class : Dir3D
Dir3D::Dir3D(void):CH3D(0,0,-1,0){}

Dir3D::Dir3D(float x, float y, float z):CH3D(x,y,z,0.0F){}

Dir3D::Dir3D(Dir3D &d):CH3D(d){}

Dir3D::Dir3D(const Pos3D &p1, const Pos3D &p2):CH3D(p2.x-p1.x, p2.y-p1.y, p2.z-p1.z, 0.0F){}
Dir3D::Dir3D(float x1, float y1, float z1,float x2, float y2, float z2):CH3D(x2-x1, y2-y1, z2-z1, 0.0F){}
Dir3D::~Dir3D(void){}

float Dir3D::operator*(const Dir3D &d){
	return x*d.x+y*d.y+z*d.z;
};

Dir3D Dir3D::operator^(const Dir3D &d){
	Dir3D pv;
	pv.x = y*d.z - z*d.y;
	pv.y = z*d.x - x*d.z;
	pv.z = x*d.y - y*d.x;
	return pv;
};
