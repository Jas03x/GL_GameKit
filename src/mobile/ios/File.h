//
//  file.h
//  BobosRun
//
//  Created by Jas S on 2016-11-23.
//  Copyright © 2016 Jas S. All rights reserved.
//

#ifndef file_h
#define file_h

#include <stdio.h>
#include <stdlib.h>

#include <string>

#ifdef __OBJC__
    #import <Foundation/Foundation.h>
#endif

namespace File
{
    void init();
    FILE* open(const char* path, const char* mode);
    std::string read(const char* path);
}

#endif /* file_h */
