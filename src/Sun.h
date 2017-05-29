#ifndef SUN_H
#define SUN_H

#include "GLM.h"

namespace Sun
{
    extern glm::vec3 color;
    extern glm::vec3 position;
    
    inline void setPosition(const glm::vec3& pos) { position = pos; }
    inline void setColor(const glm::vec3& col) { color = col; }
}

#endif
