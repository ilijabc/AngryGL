/*
	by Ilija
*/


#include "common.h"


bool isCharAlphaNumeric(char c)
{
	if (c >= 'a' && c <= 'z')
		return true;
	if (c >= 'A' && c <= 'Z')
		return true;
	if (c >= '0' && c <= '9')
		return true;
	return false;
}


bool isCharASCII(char c)
{
	if (c >= 32 && c <= 126)
		return true;
	return false;
}

const char* sw_next(const char* s_in, char* s_out, const char sp)
{
    const char *ci = s_in;
    char *co = s_out;
    if (*ci == 0) return 0;
    while (*ci && *ci != sp)
    {
        if (co)
        {
            *co = *ci;
            co++;
        }
        ci++;
    }
    if (co) *co = 0;
    if (*ci == 0) return ci;
    while (*ci && *ci == sp)
        ci++;
    return ci;
}

const char* sw_first(const char* s_in, char* s_out, const char sp)
{
    return sw_next(s_in, s_out, sp);
}


//
// file iterator
//

UTFileIterator::UTFileIterator(const char* path)
{
    #ifdef __WIN32__
    handle = FindFirstFile(path, &data);
    if (handle)
    {
        strcpy(name, data.cFileName);
        is_dir = (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY);
        have_more = true;
    }
    else
    {
        have_more = false;
    }
    #endif
}

void UTFileIterator::next()
{
    #ifdef __WIN32__
    if (!handle)
        return;
    have_more = FindNextFile(handle, &data);
    if (have_more)
    {
        strcpy(name, data.cFileName);
        is_dir = (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY);
    }
    else
    {
        FindClose(handle);
        handle = 0;
    }
    #endif
}

UTFileIterator::~UTFileIterator()
{
    #ifdef __WIN32__
    if (handle)
        FindClose(handle);
    #endif
}

