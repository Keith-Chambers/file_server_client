#include "server.h"

bool process_client_request(int connfd)
{
    uint64_t message_size = 0;

    if(recv(connfd, &message_size, sizeof(uint64_t), 0) != sizeof(uint64_t))
    {
        //klog(LOG_ERR, "Failed to get message size");
        return false;
    }

    return true;
}

void * handle_connection(void * args)
{
    printf("Connction handler start\n");

    int connfd = *( (int *) args );
    printf("Working..\n");

    int f_block_sz = 0;
    char revbuf[LENGTH]; // Receiver buffer
    memset(revbuf, 0, LENGTH);
    int success = 0;

    printf("Handling connection..\n");

    while(success == 0)
    {
        while((f_block_sz = recv(connfd, revbuf, LENGTH, 0)))
        {
            if(f_block_sz < 0)
            {
                printf("Receive file error.\n");
                break;
            }

            printf("%.*s", f_block_sz, revbuf);

            bzero(revbuf, LENGTH);
        }

        printf("\nok!\n");
        success = 1;
    }

    printf("Dupdy dup. Handling connection..\n");

    return NULL;
}

bool server(void)
{
    printf("Server running..\n");

    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;

    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    // Binding newly created socket to given IP and verification
    if ((bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr))) != 0) {
        printf("socket bind failed...\n");

        //close(sockfd);

        exit(0);
    }
    else
        printf("Socket successfully binded..\n");

#ifdef SS_DEBUG
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &(int){ 1 }, sizeof(int)) < 0)
        printf("warning: setsockopt(SO_REUSEADDR) failed\n");
#endif

    if ((listen(sockfd, 5)) != 0) {
        printf("Listen failed...\n");
        exit(0);
    }
    else
        printf("Server listening..\n");

    len = sizeof(cli);
    pthread_t thread;

    // Accept the data packet from client and verification
    connfd = accept(sockfd, (struct sockaddr *) &cli, &len);
    if (connfd < 0) {
        printf("server acccept failed...\n");
        exit(0);
    }
    else
    {
        printf("server acccept the client...\n");

        if(pthread_create(thread, NULL, handle_connection, &connfd) != 0)
        {
            printf("Failed to spawn new thread\n");
            exit(EXIT_FAILURE);
        }

        printf("Main thread doing main thread stuff\n");
    }

    pthread_join(thread, NULL);

    // After chatting close the socket
    close(sockfd);
}
