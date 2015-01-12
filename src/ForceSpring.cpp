//
//  ForceSpring.cpp
//  Springy
//
//  Created by Uriana on 13-11-4.
//  Copyright (c) 2013 Uriana. All rights reserved.
//

#include "ForceSpring.h"
ForceSpring::ForceSpring(Particle pi, Particle pj)
{
    //Spring Force
    Vector3D sf;
    Vector3D xij(pj.getPosition() - pi.getPosition());
    float lij = Magnitude(xij);
    Vector3D uij = xij;
    uij.Normalize();
    
    sf = kij * (lij - lij0) *uij;
    
    //Damper Force
    Vector3D df;
    df = dij * ((pj.getVelocity() - pi.getVelocity()) * uij) *uij;
    
    value = sf + df;
}