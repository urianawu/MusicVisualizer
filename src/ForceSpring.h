//
//  ForceSpring.h
//  Springy
//
//  Created by Uriana on 13-11-4.
//  Copyright (c) 2013 Uriana. All rights reserved.
//

#ifndef __Springy__ForceSpring__
#define __Springy__ForceSpring__

#include <iostream>
#include "Force.h"

class ForceSpring : public Force {
public:
    ForceSpring(Particle pi, Particle pj);
    
protected:
    float kij = 0.1;  //spring constant
    float dij = 0.1;  //damper constant
    float lij0 = 1;    //rest distance
};
#endif /* defined(__Springy__ForceSpring__) */
