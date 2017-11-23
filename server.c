#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define BACKLOG         20
#define SOCK_PORT       3000
#define BUF_SIZE        50
#define ACKNOWLODGE_MSG "Hello"

#define error_handler(msg) \
    do { printf(">%s \"%s\" error ocurred.\n", msg, strerror(errno)); \
         exit(EXIT_FAILURE); } while(0)

int main()
{
    ssize_t bytes_recived, bytes_send;
    int sock;
    char buffer[BUF_SIZE];
    struct sockaddr_in sock_addr, client_sock_addr;
    int tcp_sock = socket(AF_INET, SOCK_STREAM, 0);
    socklen_t client_sock_len;
    if (tcp_sock < 0)
        error_handler("While creating socket");

    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = ntohs(SOCK_PORT);
    sock_addr.sin_addr.s_addr = ntohl(INADDR_ANY);

    if (bind(tcp_sock, (struct sockaddr *) &sock_addr ,sizeof(sock_addr)) < 0)
        error_handler("While binding socket");

    if (listen(tcp_sock, BACKLOG) < 0)
        error_handler("While making listening socket");

    while (1) {
        sock = accept(tcp_sock, (struct sockaddr *) &client_sock_addr,
                      &client_sock_len);
        if(sock < 0)
            error_handler("While creating socket");

        while ((bytes_recived = recv(sock, buffer, BUF_SIZE, 0)) > 0) {
            printf("Received msg: %li:bytes %s\n", bytes_recived, buffer);
            bytes_send = sendto(sock, ACKNOWLODGE_MSG, sizeof(ACKNOWLODGE_MSG), 0,
                                (struct sockaddr *) &client_sock_addr,
                                sizeof(client_sock_addr));
            if (bytes_send < 0)
                error_handler("While sending data");
            printf("Sent acknowledge msg: %li:bytes %s\n", bytes_send, ACKNOWLODGE_MSG);
        }

        if (bytes_recived < 0)
            error_handler("While receiving data");
    }

    close(sock);
    close(tcp_sock);
    return EXIT_SUCCESS;
}