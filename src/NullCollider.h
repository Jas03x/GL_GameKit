//
//  NullCollider.h
//  CarDemo
//
//  Created by Jas S on 2017-07-01.
//  Copyright © 2017 Jas S. All rights reserved.
//

#ifndef NullCollider_h
#define NullCollider_h

#include "Math3d.h"
#include "Collider.h"

class NullCollider : public Collider
{
private:
    
public:
    NullCollider(){}
    void destroy(){}
};

#endif /* NullCollider_h */
