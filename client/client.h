#ifndef CLIENT_H
#define CLIENT_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <memory.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <syslog.h>

#include <common/util.h>
#include <common/file.h>
#include <common/message.h>

typedef struct FileInfo
{
    size_t name_length;
    size_t data_size;

    const char * name;
    void * data;

} FileInfo;

int create_server_connection(const char * server_ip, const uint16_t server_port);
bool send_message(int connection_handle, Message message);

/*
bool send_file(const char * filepath)
{
    FILE * transfer_fp = fopen(filepath, "r+");

    if(! transfer_fp)
    {
        printf("Failed to open %s\n", filepath);
        return false;
    }

    size_t file_size = calc_file_size(transfer_fp);

    if(file_size == 0)
    {
        printf("Error: Cannot transfer file of size 0\n");
        return false;
    }

    int sockfd; // Socket file descriptor
    struct sockaddr_in remote_addr;
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        printf("ERROR: Failed to obtain Socket Descriptor!\n");
        return (0);
    }

    remote_addr.sin_family = AF_INET;
    remote_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &remote_addr.sin_addr);

    memset(&(remote_addr.sin_zero), 0, 8);

    if (connect(sockfd, (struct sockaddr *)&remote_addr, sizeof(struct sockaddr)) == -1)
    {
        printf ("ERROR: Failed to connect to the host!\n");
        return (0);
    }
    else printf("[client] connected to server at port %d...ok!\n", PORT);

    char sdbuf[LENGTH];
    bzero(sdbuf, LENGTH);
    int f_block_sz;

    // Send meta data first
    FileInfo file_info;
    file_info.name = filepath;
    file_info.name_length = strlen(filepath);
    file_info.data_size = file_size;

    if(send(sockfd, sdbuf, f_block_sz, 0) < 0)

    while((f_block_sz = fread(sdbuf, sizeof(char), LENGTH, transfer_fp))>0)
    {
        if(send(sockfd, sdbuf, f_block_sz, 0) < 0)
        {
            printf("ERROR: Failed to send file %s.\n", "asdsad");
            break;
        }

        bzero(sdbuf, LENGTH);
    }
    printf("ok!\n");
    close(sockfd);

    printf("Transfer complete\n");

    return true;
}
*/


#endif // CLIENT_H
