//
//  Particle.h
//  Springy
//
//  Created by Uriana on 13-11-1.
//  Copyright (c) 2013 Uriana. All rights reserved.
//

#ifndef __Springy__Particle__
#define __Springy__Particle__

#include <iostream>
#include "Vector3D.h"

class Particle {
public:
    Particle();
    Particle (Point3D theposition, Vector3D thevelocity, float themass, Point3D thecolor);
    Point3D getPosition() const;
    Vector3D getVelocity() const;
    Vector3D getAccel() const;
    float getMass() const;
    Point3D getColor() const;
    Vector3D getForce() const;

    void setPosition(Point3D p);
    void setVelocity(Vector3D v);
    void setAccel(Vector3D a);
    void setMass(float m);
    void setColor(Point3D c);
    void setForce(Vector3D f);
    
    Vector3D calculateAccel();
    
protected:

    Point3D position;
    Vector3D velocity;
    Vector3D accel;
    float mass;
    Vector3D force;
    Point3D color;
};
#endif /* defined(__Springy__Particle__) */
