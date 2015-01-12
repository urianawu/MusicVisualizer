//
//  Force.cpp
//  Springy
//
//  Created by Uriana on 13-11-1.
//  Copyright (c) 2013 Uriana. All rights reserved.
//

#include "Force.h"

Force::Force()
{
    value = Vector3D(0,0,0);
}

Force::Force(Vector3D thevalue)
{
    value = thevalue;
}

void Force::addTo(Particle &p)
{
    Vector3D f = p.getForce();
    p.setForce( f + value);
    
}