//
//  Integration.cpp
//  Springy
//
//  Created by Uriana on 13-11-1.
//  Copyright (c) 2013 Uriana. All rights reserved.
//

#include "Integration.h"
Integration::Integration()
{
    time = 0;
	h = 0.1f;
}
Integration::Integration(float theh)
{
    time = 0;
	h = theh;
}
float Integration::getTime() const
{
    return time;
}
void Integration::setTime(float thetime)
{
    time = thetime;
}