#ifndef FILE_H
#define FILE_H

#ifdef __APPLE__
    #include "TargetConditionals.h"
    #elif TARGET_OS_IPHONE
        #include "../mobile/ios/File.h"
    #else
        #include "../pc/File.h"
    #endif
#else
    #include "../pc/File.h"
#endif
