#pragma once
#include <ctype.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

static inline void tolower_string(char* string)
{
    unsigned long length = strlen(string);
    for (unsigned long i = 0; i < length; ++i)
        string[i] = tolower((int)string[i]);
}

static inline char* append_filepath(const char* directory, const char* filepath)
{
    int filepathLength = snprintf(NULL, 0, "%s/%s", directory, filepath);

    char* path = (char*)malloc(filepathLength + 1);
    assert(path);

    snprintf(path, filepathLength + 1, "%s/%s", directory, filepath);
    return path;
}