#ifndef PATH_H
#define PATH_H

#ifdef _WIN32
#define INT_SHDR(x) "C:\\Users\\Jas\\Documents\\Projects\\GameKit\\src\\Shaders\\" x
#define ASST_PATH "../MyApp/Assets/"
#else
#define INT_SHDR(x) "/Users/Jas/Documents/GameKit/src/Shaders/" x
#define ASST_PATH "/Users/Jas/Documents/BobosPuzzle/BobosPuzzle/Assets/"
#endif

#endif
