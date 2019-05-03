#ifndef FILE_H
#define FILE_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <inttypes.h>
#include <assert.h>

#include <common/util.h>

/*  DO NOT DELETE: Defined structure for File type

typedef struct File
{
    uint64_t name_length;
    uint64_t data_size;

    const char * name;
    void * data;

} File; */

typedef uint8_t * File;

bool load_file(File * file_ptr, const char * name, FILE * file_pointer);
void destroy_file(File * file);
const char * get_file_name(File file);
DataBlock get_file_contents(File file);
size_t get_file_allocated_size(File file);

void output_file_log_string(FILE * file_descriptor, File file);

#endif // FILE_H
