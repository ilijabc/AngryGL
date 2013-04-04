#ifndef COMMON_H
#define COMMON_H

//
//basic types
//
typedef unsigned int 	u32;
typedef signed int 		s32;
typedef float 			f32;
typedef unsigned short	u16;
typedef signed short	s16;
typedef char			c8;
typedef unsigned char	u8;


//
//keys
//

bool isCharAlphaNumeric(char c);
bool isCharASCII(char c);

//
// str
//
const char* sw_next(const char* s_in, char* s_out, const char sp = ' ');
const char* sw_first(const char* s_in, char* s_out, const char sp = ' ');

#define foreach_word(W,S,P) \
    char W[260]; \
    for (const char *s_itr = sw_first(S, W, P); s_itr; s_itr = sw_next(s_itr, W, P))

#ifdef __WIN32__
#include <windows.h>
#endif

struct UTFileIterator
{
    UTFileIterator(const char* path);
    ~UTFileIterator();

    char name[260];
    bool is_dir;
    bool have_more;

    #ifdef __WIN32__
    HANDLE handle;
    WIN32_FIND_DATA data;
    #endif

    void next();
    bool end() { return !have_more; }
};


#endif // COMMON_H
