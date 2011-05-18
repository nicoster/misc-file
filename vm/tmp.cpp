#pragma once

#define M_PI 3.141
#include <math.h>

class Vector3D{
 Vector3D(){x=y=z=0.0;}
 Vector3D(double vx, double vy,double vz=0.0){
  x = vx;
  y = vy;
  z = vz;
 }
 
 double magnitude() const{
  return sqrt(x*x+y*y+z*z);
 }

 double dotP(const Vector3D& v1,const Vector3D& v2) const{
  return (v1.x*v2.x+v1.y*v2.y+v1.z*v2.z);
 }

 // get the vector angle
 double angle() const{
  double ret = 0.0;
  double m = magnitude();

  if (m>1.0e-6) {
   double dp = dotP(*this,Vector3D(1.0,0.0));

   if (dp/m>=1.0) {
    ret = 0.0;
   }
   else if (dp/m<-1.0) {
    ret = M_PI;
   }
   else {
    ret = acos( dp / m);
   }
   if (y<0.0) {
    ret = 2*M_PI - ret;
   }
  }
  return ret;
 }


protected:
 double x;
 double y;
 double z;

};

