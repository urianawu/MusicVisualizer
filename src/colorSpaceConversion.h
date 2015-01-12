//
//  colorSpaceConversion.h
//  DigitalImage
//
//  Created by Uriana on 10/23/13.
//  Copyright (c) 2013 Uriana. All rights reserved.
//

#ifndef __DigitalImage__colorSpaceConversion__
#define __DigitalImage__colorSpaceConversion__

#include <iostream>
class colorSpaceConversion
{
public:
    // r,g,b values are from 0 to 1
    // h = [0,360], s = [0,1], v = [0,1]
    //		if s == 0, then h = -1 (undefined)
    void RGBtoHSV( float r, float g, float b, float *h, float *s, float *v );
    void HSVtoRGB( float *r, float *g, float *b, float h, float s, float v );
};

#endif /* defined(__DigitalImage__colorSpaceConversion__) */
