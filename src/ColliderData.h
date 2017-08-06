//
//  ColliderData.h
//  Automata
//
//  Created by Jas S on 2017-08-05.
//  Copyright © 2017 Jas S. All rights reserved.
//

#ifndef ColliderData_h
#define ColliderData_h

typedef struct ColliderData
{
    btCollisionShape* shape;
    glm::vec3 position;
}ColliderData;

#endif /* ColliderData_h */
