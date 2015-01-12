//
//  Integration.h
//  Springy
//
//  Created by Uriana on 13-11-1.
//  Copyright (c) 2013 Uriana. All rights reserved.
//

#ifndef __Springy__Integration__
#define __Springy__Integration__

#include <iostream>
#include "Particle.h"
#include "World.h"
class Integration {
public:
    Integration();
    Integration(float theh);
    
    float getTime() const;
    void setTime(float thetime);
    
    //virtual ~Integration(){}
    virtual void update(Particle &p, Particle p_after, World w) = 0;
    
protected:
    float time;
    float h;
    
};
#endif /* defined(__Springy__Integration__) */
