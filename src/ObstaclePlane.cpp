//
//  ObstaclePlane.cpp
//  Springy
//
//  Created by Uriana on 13-11-3.
//  Copyright (c) 2013 Uriana. All rights reserved.
//

#include "ObstaclePlane.h"

ObstaclePlane::ObstaclePlane(Vector3D thenormal, Point3D thepoint)
{
    e = 0.0f;
	miu = 0.0f;
	normal = thenormal;
    point = thepoint;
    collided = false;
}

bool ObstaclePlane::CollisionDetection(Particle p, Particle &p_after)
{
    Vector3D s_vector_current(0,0,0);
    Vector3D s_vector_next(0,0,0);
    double DotProduct_current = 0;
    double DotProduct_next = 0;
    
    s_vector_current = p.getPosition() - point;
    s_vector_next = p_after.getPosition() - point;
    DotProduct_current = Dot(s_vector_current, normal);
    DotProduct_next = Dot(s_vector_next, normal);
    //printf("%f ",DotProduct_current);
    //printf("DotProduct_next %f\n",DotProduct_next);

    float d = 0;
    if (( DotProduct_current >= 0 && DotProduct_next >= 0) || (DotProduct_current <= 0 && DotProduct_next <= 0))
        d = 0;
    else
        d = fabsf((float)DotProduct_next);
    // distance of xi+1 to the plane

    if (d != 0) {
        //compute new velocity and position
        CollisionResponse( d, p_after);
        return true;
    }
    return false;
}

void ObstaclePlane::CollisionResponse(float d, Particle &p_after)
{
    Vector3D vn;
    float vn_value = 0;
    Point3D p = p_after.getPosition();
    Vector3D v = p_after.getVelocity();
    p_after.setPosition( p + (1+e)*d*normal);
    vn_value = Dot(v, normal);
    vn = fabsf(vn_value) * normal;
    p_after.setVelocity((1+e) * vn + v);

}