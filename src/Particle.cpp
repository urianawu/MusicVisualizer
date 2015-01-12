//
//  Particle.cpp
//  Springy
//
//  Created by Uriana on 13-11-1.
//  Copyright (c) 2013 Uriana. All rights reserved.
//

#include "Particle.h"
Particle::Particle()
{
    position = Point3D(0, 0, 0);
    velocity = Vector3D(0, 0, 0);
    mass = 0;
    color = Point3D(0, 0, 0);
    force = Vector3D(0, 0, 0);
    accel = Vector3D(0, 0, 0);
}

Particle::Particle(Point3D theposition, Vector3D thevelocity, float themass, Point3D thecolor)
{
    position = theposition;
    velocity = thevelocity;
    mass = themass;
    color = thecolor;
    force = Vector3D(0, 0, 0);
    accel = Vector3D(0, 0, 0);
}


Vector3D Particle::calculateAccel()
{
    accel = force / mass;
    //printf("%f\t",force.y);
    return accel;
}

void Particle::setForce(Vector3D f)
{
    force = f;
}

void Particle::setPosition(Point3D p)
{
    position = p;
}
void Particle::setVelocity(Vector3D v)
{
    velocity = v;
}
void Particle::setAccel(Vector3D a)
{
    accel = a;
}
void Particle::setMass(float m)
{
    mass = m;
}
void Particle::setColor(Point3D c)
{
    color = c;
}

Point3D Particle::getPosition() const
{
    return position;
}
Vector3D Particle::getVelocity() const
{
    return velocity;
}
Vector3D Particle::getAccel() const
{
    return accel;
}
float Particle::getMass() const
{
    return mass;
}
Point3D Particle::getColor() const
{
    return color;
}
Vector3D Particle::getForce() const
{
    return force;
}