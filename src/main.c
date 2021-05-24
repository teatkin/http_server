#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

#define PORT 8080
#define BACKLOG 10
#define BUFSIZ 1024

int main() {
    printf("http_server v0.0.1\n");
    
    /* Create a new IPv4 TCP socket to listen on */
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    
    struct sockaddr_in serv_addr = {
        .sin_family = AF_INET,
        .sin_port = htons(PORT),
        .sin_addr.s_addr = INADDR_ANY
    };
    
    int err = bind(sockfd, (const struct sockaddr *) &serv_addr, sizeof(struct sockaddr_in));
    if (err == -1) {
        perror("bind");
        exit(EXIT_FAILURE);
    }
    
    err = listen(sockfd, BACKLOG);
    if (err == -1) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    while (1) {
        struct sockaddr_in peeraddr;
        socklen_t peerlen;

        int connfd = accept(sockfd, (struct sockaddr *) &peeraddr, &peerlen);
        if (connfd == -1) {
            perror("accept");
        }

        char buf[BUFSIZ] = {'\0'};
        ssize_t recvd = recv(connfd, buf,BUFSIZ, 0);
        if (recvd == -1) {
            perror("recv");
        }

        printf("buf: %s\n", buf);
        ssize_t sent = send(connfd, buf, BUFSIZ, 0);
        if (sent == -1) {
            perror("send");
        }

        close(connfd);
    }
    return 0;
}
