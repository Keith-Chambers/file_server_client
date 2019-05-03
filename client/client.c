#include "client.h"

int create_server_connection(const char * server_ip, const uint16_t server_port)
{
    int connection_handle;
    struct sockaddr_in server_address;

    if(-1 == (connection_handle = socket(AF_INET, SOCK_STREAM, 0)))
        return 0;

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(server_port);

    inet_pton(AF_INET, server_ip, &server_address.sin_addr);

    memset(&(server_address.sin_zero), 0, 8);

    if(-1 == connect(connection_handle, (struct sockaddr *)&server_address, sizeof(struct sockaddr)))
    {
        printf ("Error: Failed to connect to server!\n");
        return 0;
    }

    return connection_handle;
}

bool send_message(int connection_handle, Message message)
{
    if(connection_handle <= 0)
        return false;

    uint64_t message_size = calc_message_size(message);

    if(send(connection_handle, &message_size, sizeof (uint64_t), 0) < 0)
    {
        printf("ERROR: Failed to send message size.\n");
        return false;
    }

    if(send(connection_handle, (uint8_t *) message, calc_message_size(message), 0) < 0)
    {
        printf("ERROR: Failed to send message.\n");
        return false;
    }

    return true;
}
