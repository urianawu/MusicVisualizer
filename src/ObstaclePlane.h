//
//  ObstaclePlane.h
//  Springy
//
//  Created by Uriana on 13-11-3.
//  Copyright (c) 2013 Uriana. All rights reserved.
//

#ifndef __Springy__ObstaclePlane__
#define __Springy__ObstaclePlane__

#include <iostream>
#include "Obstacle.h"
class ObstaclePlane : public Obstacle {
public:
    Vector3D normal;
    Point3D point;
    
    ObstaclePlane(Vector3D thenormal, Point3D thepoint);
    bool CollisionDetection(Particle p, Particle &p_after);
    void CollisionResponse(float d, Particle &p_after);
    
protected:

    float e;      //elasticity factor
    float miu;    //friction factor
};

#endif /* defined(__Springy__ObstaclePlane__) */
