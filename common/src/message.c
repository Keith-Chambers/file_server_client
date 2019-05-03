#include <common/message.h>

/*  type 2 - Set user
 *
 *  char [*] username
 *  char [*] password
 */

Message make_set_user_message(const char * username, const char * password)
{
    uint64_t username_len = strlen(username) + 1;
    uint64_t password_len = strlen(password) + 1;

    uint64_t required_size = username_len + password_len + 1; // +1 for type

    Message message = malloc(required_size);

    if(! message)
    {
        klog(LOG_CRIT, "Failed to allocate memory for set user message");
        return NULL;
    }

    *(message + 0) = SET_USER; // Set message type

    message++; // Move past type element

    memcpy(message, username, username_len);
    memcpy(message + username_len, password, password_len);

    message--; // Move back to beginning of message

    return message;
}

uint64_t calc_message_size(Message message)
{
    switch( *((uint8_t*) message )) // Dereference first byte of message, which holds the type variable as a uint8_t
    {
        case UPLOAD_FILE:
            return calc_upload_file_message_size(message);
        case SET_USER:
            return calc_set_user_message_size(message);
        default:
            assert(false && "Cannot get size of message with invalid type");
    }

    return 0; // Will never get here (Unless asserts are disabled)
}

uint64_t calc_set_user_message_size(Message message)
{
    uint64_t username_len = strlen((const char *) message + 1);
    uint64_t password_len = strlen((const char *) (message + username_len + 1));

    return username_len + password_len + 1;
}

uint64_t calc_upload_file_message_size(Message message)
{
    assert(false && "Implement");

    return 1;
}

/*  type 1 - File upload
 *
 *  char [*] username
 *  char [*] location
 *  File file
 */

Message make_upload_file_message(File file, const char * location, const char * username)
{
    klog(LOG_DEBUG, "Constructing upload file message");

    uint64_t username_len = strlen(username) + 1; // +1 for \0
    uint64_t location_len = strlen(location) + 1;
    uint64_t file_allocation = get_file_allocated_size(file);

    uint64_t required_size = location_len + username_len + file_allocation + 1; // +1 for type
    Message message = malloc(required_size);

    if(! message)
    {
        assert(message && "Failed to allocate message");
        klog(LOG_CRIT, "Failed to allocate memory for upload file message");
        return NULL;
    }

    *( (uint8_t*) message ) = UPLOAD_FILE;

    message++; // Move past type element

    klog(LOG_DEBUG, "Writing to message..");

    memcpy(message, username, username_len);
    memcpy(message + username_len, location, location_len);
    memcpy(message + username_len + location_len, file, file_allocation);

    klog(LOG_DEBUG, "Message successfully written to");

    message--; // Return back to first allocated byte

    return message;
}

void dealloc_upload_file_message(Message message)
{
    assert(false && "Implement");

    uint64_t allocated_size;
}

void deallocate_message(Message message)
{
    switch( *((uint8_t*) message ))
    {
        case UPLOAD_FILE:
            dealloc_upload_file_message(message);
            break;
        default:
            assert(false && "Message to deallocate has invalid type");
    }

    message = NULL;
}
