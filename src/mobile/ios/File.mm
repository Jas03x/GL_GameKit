//
//  file.cpp
//  BobosRun
//
//  Created by Jas S on 2016-11-23.
//  Copyright © 2016 Jas S. All rights reserved.
//

#include "File.h"

static std::string path;

void File::init()
{
    NSBundle *b = [NSBundle mainBundle];
    NSString *dir = [b resourcePath];
    path = [dir fileSystemRepresentation];
}

FILE* File::open(const char* fpath, const char* mode)
{
    std::string p = path + "/" + fpath;
    FILE* file = fopen(p.c_str(), mode);
    if(file == NULL)
    {
        printf("Error: Could not read file [%s].\n", fpath);
        throw -1;
    }
    
    return file;
}

std::string File::read(const char* path)
{
    FILE* file = File::open(path, "r");
    
    fseek(file, 0, SEEK_END);
    size_t length = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    char* data = new char[length + 1];
    fread(data, 1, length, file);
    fclose(file);
    
    data[length] = '\0';
    std::string str = std::string(data);
    
    delete[] data;
    return str;
}
