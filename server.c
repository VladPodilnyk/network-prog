#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define SOCK_PORT       3001
#define BUF_SIZE        50
#define ACKNOWLODGE_MSG "Hello"

#define error_handler(msg) \
    do { printf(">%s \"%s\" error ocurred.\n", msg, strerror(errno)); \
         exit(EXIT_FAILURE); } while(0)

int main()
{
    ssize_t bytes_received, bytes_send;
    char buffer[BUF_SIZE];
    struct sockaddr_in sock_addr, client_sock_addr;
    int udp_sock = socket(AF_INET, SOCK_DGRAM, 0);
    socklen_t client_sock_len = sizeof(client_sock_addr);
    if (udp_sock < 0)
        error_handler("While creating socket");

    memset(&client_sock_addr, 0, sizeof(struct sockaddr_in));

    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = ntohs(SOCK_PORT);
    sock_addr.sin_addr.s_addr = ntohl(INADDR_ANY);

    if (bind(udp_sock, (struct sockaddr *) &sock_addr ,sizeof(sock_addr)) < 0)
        error_handler("While binding socket");

    while (1) {
        bytes_received = recvfrom(udp_sock, buffer, BUF_SIZE, 0, 
                                 (struct sockaddr *) &client_sock_addr, 
                                 &client_sock_len);
        if (bytes_received < 0)
            error_handler("While receiving data");
        printf("Received msg: %li:bytes %s\n", bytes_received, buffer);

        if (bytes_received != 0) {
            bytes_send = sendto(udp_sock, ACKNOWLODGE_MSG, sizeof(ACKNOWLODGE_MSG), 0,
                                (struct sockaddr *) &client_sock_addr,
                                client_sock_len);
            if (bytes_send < 0)
                error_handler("While sending data");
            printf("Sent acknowledge msg: %li:bytes %s\n", bytes_send, 
                                                           ACKNOWLODGE_MSG);
        }
    }

    close(udp_sock);
    return EXIT_SUCCESS;
}