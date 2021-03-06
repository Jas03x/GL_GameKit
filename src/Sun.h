#ifndef SUN_H
#define SUN_H

#include "Math3d.h"

namespace Sun
{
    extern glm::vec3 color;
    extern glm::vec3 position;
    
    inline void setPosition(const glm::vec3& pos) { position = pos; }
    inline void setColor(const glm::vec3& col) { color = col; }
    
    inline void set(const glm::vec3& pos, const glm::vec3& col) {
        position = pos;
        color = col;
    }
}

#endif
