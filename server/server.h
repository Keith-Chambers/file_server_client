#ifndef SERVER_H
#define SERVER_H

#include <stdio.h>
#include <stdbool.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#define PORT 12345
#define MAX 80

#define LENGTH 1000

#define SS_DEBUG

// Member order is important here!
typedef struct FileInfo
{
    size_t name_length;
    size_t data_size;

    const char * name;
    void * data;
};

/*
bool run(void)
{
    char file_buffer[512];
    char* file_name = "list.txt";

    FILE *file_open = fopen(file_name, "w");

    if(file_open == NULL)
      printf("File %s Cannot be opened file on server.\n", file_name);
    else {
      bzero(file_buffer, 512);
      int block_size = 0;
      int i=0;

      while((block_size = recv(cs, file_buffer, 512, 0)) > 0) {
         printf("Data Received %d = %d\n",i,block_size);
         int write_sz = fwrite(file_buffer, sizeof(char), block_size, file_open);
         bzero(file_buffer, 512);
         i++;
      }

    }
    printf("Transfer Complete!\n");
    fclose(file_open);
}
*/

// How to handle loading a request in chucks
// Just load the first byte, then send it to a subsystem which will load everything in one chuck
// Well, you need to store the data to be able to determinate what the size is. Maybe I should include that as the first element


bool process_client_request(int connfd);
void * handle_connection(void * args);
bool server(void);


#endif // SERVER_H
