//
//  EulerIntegration.cpp
//  Springy
//
//  Created by Uriana on 13-11-1.
//  Copyright (c) 2013 Uriana. All rights reserved.
//

#include "EulerIntegration.h"
EulerIntegration::EulerIntegration(float theh)
{
    h = theh;
    
}

void EulerIntegration::update(Particle &p, Particle p_after, World w)
{
    w.applyForce(p);
    p.setAccel(p.calculateAccel());
    
    //printf("%f", p.getAccel().y);
    //integrate to get new state
    p_after.setVelocity(p.getVelocity() + p.getAccel() * h);
	//printf("%f",(p.getVelocity()).z);
    p_after.setPosition(p.getPosition() + p.getVelocity() * h);

	//set color
	float r, g, b, h, s, v;
	//printf("%f\n",((p_after.getPosition().x+2)/3.875)*360);
	if (p.getPosition().y > - 1.9 ){
		h = ((p.getPosition().x + 2)/ 4 )* 360;
		s = (p.getPosition().y + 2.0 / 6.0);
		v = 0.5;
	}
	else{
		h = 360;
		s = 1;
		v = 0.7;
	}
	//printf("%f",h);

	colorSpaceConversion conv;
	conv.HSVtoRGB( &r, &g, &b, h, s, v );
	//printf("%f %f %f\n",r,g,b);
    p_after.setColor(Point3D(r, g, b));
    p_after.setMass(p.getMass());
    
    //check for collision

    w.checkCollision(p, p_after);
    
	//resting
	if(p_after.getPosition().y < -1.9)
		p_after.setPosition(Point3D(p_after.getPosition().x, -2, p_after.getPosition().z));
    //update state
    p = p_after;
    setTime(time + h);
    
}
