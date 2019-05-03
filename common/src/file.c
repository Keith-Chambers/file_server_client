#include <common/file.h>

// Defined offsets to make assignments more readable
static const uint16_t NAME_LEN_OFFSET = 0;
static const uint16_t DATA_SIZE_OFFSET = sizeof(uint64_t) * 1;
static const uint16_t FILE_NAME_OFFSET = sizeof(uint64_t) * 2;

void output_file_log_string(FILE * file_descriptor, File file)
{
    const char * file_name = get_file_name(file);
    DataBlock file_contents = get_file_contents(file);

    fprintf(file_descriptor, "---\nName (%lu) : %s\nContent (%lu) : %s\nAllocated : %lu\n---\n",
            strlen(file_name), file_name, file_contents.size, (const char *)file_contents.data, get_file_allocated_size(file));
}

bool load_file(File * file_ptr, const char * name, FILE * file_pointer)
{
    klog(LOG_DEBUG, "Loading file -> %s\n", name);

    File file; // uint8_t *

    // Calculate size;
    if(file_pointer == NULL)
        return false;

    int64_t file_size = calc_file_size(file_pointer);
    uint64_t file_name_length = strlen(name);

    // Defined offsets to make assignments more readable
    const uint64_t FILE_CONTENTS_OFFSET = sizeof(uint64_t) * 2 + file_name_length + 1;

    if(file_size <= 0)
        return false;

    uint64_t required_size = sizeof(uint64_t) * 2 + ((uint64_t) file_size) + file_name_length + 1; // + 1 for \0

    klog(LOG_DEBUG, "Allocating %lu bytes for file\n", required_size);

    file = malloc(required_size);

    if(! file )
        return false;

    // name_length
    *( (uint64_t *)(file + NAME_LEN_OFFSET)) = (uint64_t) file_name_length + 1;

    klog(LOG_DEBUG, "File name length : %lu", *( (uint64_t *)(file + NAME_LEN_OFFSET)));

    // data_size
    *( (uint64_t *)(file + DATA_SIZE_OFFSET)) = (uint64_t) file_size;

    klog(LOG_DEBUG, "File contents size : %lu", *( (uint64_t *)(file + DATA_SIZE_OFFSET)));

    // name
    strncpy((void *) (file + FILE_NAME_OFFSET), name, file_name_length);
    *((char *)(file + FILE_NAME_OFFSET + file_name_length)) = '\0'; // Terminate string

    assert( get_file_name(file) == (const char *)(file + FILE_NAME_OFFSET) && "Assert Error: Derived file_name address not valid" );
    assert( file_name_length == strlen((const char *)(file + FILE_NAME_OFFSET)) && "Assert Error: Derived file_name_length incorrect" );

    printf("'%s'\n", get_file_name(file));

    printf("Assertions passed\n");

    if(fread(file + FILE_CONTENTS_OFFSET, 1, (uint64_t) file_size, file_pointer) != (uint64_t) file_size)
    {
        free(file);
        return false;
    }

    *file_ptr = file;

    output_file_log_string(stderr, file);

    return true;
}

void destroy_file(File * file)
{
    if(*file == NULL)
        return;

    free(*file);
    *file = NULL;
}

const char * get_file_name(File file)
{
    return (const char *)(file + FILE_NAME_OFFSET);
}

DataBlock get_file_contents(File file)
{
    uint64_t file_size = *((uint64_t *) (file + DATA_SIZE_OFFSET));
    uint64_t file_name_len = *((uint64_t *) (file + NAME_LEN_OFFSET));
    const uint64_t FILE_CONTENTS_OFFSET = sizeof(uint64_t) * 2 + file_name_len;

    DataBlock result = {
      .size = file_size,
      .data = file + FILE_CONTENTS_OFFSET
    };

    return result;
}

size_t get_file_allocated_size(File file)
{
    klog(LOG_DEBUG, "Getting file allocation size");

    printf("Here..\n");
    printf("sizeof(uint64_t) -> %lu\n", sizeof(uint64_t) );
    printf("sizeof(uint64_t) * 2 -> %lu\n", sizeof(uint64_t) * 2);

    uint64_t header_size = sizeof(uint64_t) * 2;

    uint64_t file_name_size = *((uint64_t *) (file + NAME_LEN_OFFSET));
    printf("File Name Size : %lu\n", file_name_size);
    uint64_t file_contents_size = *((uint64_t *) (file + DATA_SIZE_OFFSET));
    printf("File Contents Size : %lu\n", file_contents_size);

    // sizeof(name_length + data_size) + name_length + data_size;
    return header_size + file_name_size + file_contents_size;
}
