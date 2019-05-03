#ifndef MESSAGE_H
#define MESSAGE_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <common/util.h>
#include <common/file.h>

/*
typedef struct Message
{
    uint8_t type; // 0 = invalid
    uint8_t payload;
} Message;
*/

enum MESSAGE_TYPE { INVALID = 0, UPLOAD_FILE, SET_USER };

typedef uint8_t * Message;

/*  type 1 - File upload
 *
 *  char [*] username
 *  char [*] location
 *  File file
 */

/*  type 2 - Set user
 *
 *  char [*] username
 *  char [*] password
 */

Message make_set_user_message(const char * username, const char * password);
Message make_upload_file_message(File file, const char * location, const char * username);
//Message make_upload_file_message(const char * file_name, FILE * file_pointer, const char * location, const char * username);
Message make_list_dir_message(const char * location, const char * username);

uint64_t calc_message_size(Message message);
uint64_t calc_set_user_message_size(Message message);
uint64_t calc_upload_file_message_size(Message message);

void dealloc_upload_file_message(Message message);

void deallocate_message(Message message);

#endif // MESSAGE_H
