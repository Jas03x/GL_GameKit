#ifndef PATH_H
#define PATH_H

#ifdef _WIN32
	#define INT_SHDR(x) "C:\\Users\\Jas\\Documents\\Projects\\Libraries\\GL_GameKit\\src\\Shaders\\" x
	#define INT_DATA(x) "C:\\Users\\Jas\\Documents\\Projects\\Libraries\\GL_GameKit\\src\\Data\\" x
#else
	#define INT_SHDR(x) "/Users/jass/Documents/Libraries/GL_GameKit/src/Shaders/" x
	#define INT_DATA(x) "/Users/jass/Documents/Libraries/GL_GameKit/src/Data/" x
#endif

#endif
