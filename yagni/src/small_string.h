#pragma once
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#define SMALL_STRING_CONTAINER_MULTIPLIER (2)

struct small_string
{
    char* data;
    unsigned long length;
} typedef small_string;

static inline small_string small_string_init(unsigned long length)
{
    small_string string = { 0 };
    string.length = length;
    
    string.data = (char*)malloc((length + 1) * sizeof(char));
    assert(string.data);

    string.data[length] = '\0';

    return string;
}

static inline small_string small_string_from(const char* source)
{
    small_string str = small_string_init(strlen(source));
    memcpy(str.data, source, strlen(source));
    return str;
}

static inline void small_string_free(small_string string)
{
    free(string.data);
    string.data = NULL;
    string.length = 0;
}

struct string_container
{
    small_string* data;
    unsigned long size;
    unsigned long capacity;
} typedef string_container;

static inline string_container string_container_init(unsigned int capacity)
{
    string_container container = { 0 };

    container.size = 0;
    container.capacity = capacity;
    
    container.data = (small_string*)malloc(container.capacity * sizeof(small_string));
    assert(container.data);
    
    return container;
}

static inline void string_container_push_back(string_container* container, small_string string)
{
    if (container->size >= container->capacity)
    {
        container->capacity *= SMALL_STRING_CONTAINER_MULTIPLIER;
        container->data = (small_string*)realloc(container->data, container->capacity * sizeof(small_string));
        assert(container->data);
    }

    container->data[container->size] = string;
    ++container->size;
}

static inline void string_container_free(string_container* container)
{
    for (unsigned long i = 0; i < container->size; ++i)
        small_string_free(container->data[i]);
    
    free(container->data);
    container->data = NULL;

    container->size = 0;
    container->capacity = 0;
}