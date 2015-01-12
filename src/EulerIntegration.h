//
//  EulerIntegration.h
//  Springy
//
//  Created by Uriana on 13-11-1.
//  Copyright (c) 2013 Uriana. All rights reserved.
//

#ifndef __Springy__EulerIntegration__
#define __Springy__EulerIntegration__

#include <iostream>
#include "Integration.h"
#include "colorSpaceConversion.h"
class EulerIntegration : public Integration {
public:
    void update(Particle &p, Particle p_after, World w);
    EulerIntegration(float theh);
    
    
};
#endif /* defined(__Springy__EulerIntegration__) */
