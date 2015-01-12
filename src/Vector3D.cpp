//
//  Vector3D.cpp
//  Flocking
//
//  Created by Uriana on 10/10/13.
//  Copyright (c) 2013 Uriana. All rights reserved.
//

#include "Vector3D.h"
Origin3D_ Origin3D;


Vector3D& Vector3D::RotateAboutX(float angle)
{
    float s = sinf(angle);
    float c = cosf(angle);
    
    float ny = c * y - s * z;
    float nz = c * z + s * y;
    
    y = ny;
    z = nz;
    
    return (*this);
}

Vector3D& Vector3D::RotateAboutY(float angle)
{
    float s = sinf(angle);
    float c = cosf(angle);
    
    float nx = c * x + s * z;
    float nz = c * z - s * x;
    
    x = nx;
    z = nz;
    
    return (*this);
}

Vector3D& Vector3D::RotateAboutZ(float angle)
{
    float s = sinf(angle);
    float c = cosf(angle);
    
    float nx = c * x - s * y;
    float ny = c * y + s * x;
    
    x = nx;
    y = ny;
    
    return (*this);
}

Vector3D& Vector3D::RotateAboutAxis(float angle, const Vector3D& axis)
{
    float s = sinf(angle);
    float c = cosf(angle);
    float k = 1.0F - c;
    
    float nx = x * (c + k * axis.x * axis.x) + y * (k * axis.x * axis.y - s * axis.z)
    + z * (k * axis.x * axis.z + s * axis.y);
    float ny = x * (k * axis.x * axis.y + s * axis.z) + y * (c + k * axis.y * axis.y)
    + z * (k * axis.y * axis.z - s * axis.x);
    float nz = x * (k * axis.x * axis.z - s * axis.y) + y * (k * axis.y * axis.z + s * axis.x)
    + z * (c + k * axis.z * axis.z);
    
    x = nx;
    y = ny;
    z = nz;
    
    return (*this);
}