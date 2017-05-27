//
//  File.hpp
//  Bobo
//
//  Created by Jas S on 2017-02-04.
//  Copyright © 2017 Jas S. All rights reserved.
//

#ifndef File_hpp
#define File_hpp

#include <stdio.h>
#include <stdlib.h>

#include <string>

namespace File
{
    std::string read(const char* path);
    FILE* open(const char* path, const char* mode);
}

#endif /* File_hpp */
