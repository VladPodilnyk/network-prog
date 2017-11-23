#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define BACKLOG         0
#define SOCK_PORT       3001
#define BUF_SIZE        50
#define PROC_LIMIT      5
#define ACKNOWLODGE_MSG "Hello"

#define error_handler(msg) \
    do { printf(">%s \"%s\" error ocurred.\n", msg, strerror(errno)); \
         exit(EXIT_FAILURE); } while(0)

int main()
{
    ssize_t bytes_recived, bytes_send;
    int sock, proc_counter;
    pid_t process_id, ppid;
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

    ppid = getpid();
    // Creating processes
    for (proc_counter = 0; proc_counter < PROC_LIMIT; ++proc_counter)
        if (ppid == getpid())
            fork();

    process_id = getpid(); // retrive current pid

    while (1) {
        sock = accept(tcp_sock, (struct sockaddr *) &client_sock_addr,
                      &client_sock_len);
        if(sock < 0)
            error_handler("While creating socket");

        while ((bytes_recived = recv(sock, buffer, BUF_SIZE, 0)) > 0) {
            printf("Received msg: %i:process %li:bytes %s\n", process_id,
                                                              bytes_recived,
                                                              buffer);
            bytes_send = sendto(sock, ACKNOWLODGE_MSG, sizeof(ACKNOWLODGE_MSG), 0,
                                (struct sockaddr *) &client_sock_addr,
                                sizeof(client_sock_addr));
            if (bytes_send < 0)
                error_handler("While sending data");
            printf("Sent acknowledge msg: %i:process %li:bytes %s\n", process_id,
                                                                      bytes_send,
                                                                      ACKNOWLODGE_MSG);
        }

        if (bytes_recived < 0)
            error_handler("While receiving data");
    }

    close(sock);
    close(tcp_sock);
    waitpid(process_id, NULL, WNOHANG);
    return EXIT_SUCCESS;
}