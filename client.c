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
#define CLIENT_MSG      "Hello, server, I'm here."

#define error_handler(msg) \
    do { printf(">%s \"%s\" error ocurred.\n", msg, strerror(errno)); \
         exit(EXIT_FAILURE); } while(0)


int main()
{
    ssize_t bytes_send, bytes_received;
    struct sockaddr_in sock_addr, serv_sock_addr;
    int udp_sock = socket(AF_INET, SOCK_DGRAM, 0);
    char buffer[BUF_SIZE];
    socklen_t addr_len;

    if (udp_sock < 0)
        error_handler("While creating socket");

    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = htons(SOCK_PORT);
    sock_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    bytes_send = sendto(udp_sock, CLIENT_MSG, sizeof(CLIENT_MSG), 0,
                        (struct sockaddr *) &sock_addr,
                        sizeof(sock_addr));
    if (bytes_send < 0)
        error_handler("While sending data");
    printf("Data sent: %li %s\n", bytes_send, CLIENT_MSG);

    bytes_received = recvfrom(udp_sock, buffer, BUF_SIZE, 0, 
                              (struct sockaddr *) &serv_sock_addr, 
                              &addr_len);

    if (bytes_received < 0)
            error_handler("While receiving data");
    printf("Data received: %li %s\n", bytes_received, buffer);

    close(udp_sock);
    return EXIT_SUCCESS;
}