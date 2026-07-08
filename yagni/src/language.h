#pragma once
#include "yagni/src/small_string.h"
#include <assert.h>
#include <stdio.h>

#define LANGUAGE_INITIAL_CAPACITY (32)

struct language
{
    string_container data;
} typedef language;

static inline language language_init()
{
    language lang = { 0 };
    lang.data = string_container_init(LANGUAGE_INITIAL_CAPACITY);
    return lang;
}

enum lang_read_error
{
    LANG_READ_ERROR_NONE = 0,
    LANG_READ_ERROR_CANT_OPEN,
} typedef lang_read_error;

static inline lang_read_error language_read_file(language* language, const char* filepath)
{
    assert(language);

    FILE* file = fopen(filepath, "r");
    if (file == NULL)
    {
        fprintf(stderr, "error reading language file\n");
        return LANG_READ_ERROR_CANT_OPEN; 
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        unsigned long length = strlen(buffer);
        if (length > 0 && buffer[length - 1] == '\n')
        {
            buffer[length - 1] = '\0';
            length--;
        }

        if (length == 0)
            continue;

        small_string string = small_string_from(buffer);
        string_container_push_back(&language->data, string);
    }

    fclose(file);

    return LANG_READ_ERROR_NONE;
}

static inline char* language_get_text(language* language, unsigned long index)
{
    assert(language);
    assert(index >= 0 && index < language->data.size);

    return language->data.data[index].data;
}