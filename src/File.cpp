//
//  File.cpp
//  Bobo
//
//  Created by Jas S on 2017-02-04.
//  Copyright © 2017 Jas S. All rights reserved.
//

#include "File.h"

std::string File::read(const char* path)
{
    FILE* file = File::open(path, "r");

    fseek(file, 0L, SEEK_END);
    unsigned long size = ftell(file);
    rewind(file);

    char* data = new char[length + 1];
    fread(data, 1, size, file);
    fclose(file);

    data[size] = '\0';
    std::string str = std::string(cstr);

    delete[] data;
    return str;
}

FILE* File::open(const char* path, const char* mode)
{
    FILE* file = fopen(path, mode);
    if(!file) {
        printf("Error: Could not open file [%s] for mode [%s].\n", path, mode);
        throw -1;
    }
    return file;
}
