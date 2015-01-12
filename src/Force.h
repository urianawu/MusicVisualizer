//
//  Force.h
//  Springy
//
//  Created by Uriana on 13-11-1.
//  Copyright (c) 2013 Uriana. All rights reserved.
//

#ifndef __Springy__Force__
#define __Springy__Force__

#include <iostream>
#include "Vector3D.h"
#include "Particle.h"
class Force {
public:
    Vector3D value;
    
    Force();
    Force(Vector3D thevalue);
    void addTo(Particle &p);

};
#endif /* defined(__Springy__Force__) */
