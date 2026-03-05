#include <stdio.h>

#include "ft_ping.h"

// ICMP_ECHO = 8

int main()
{
    int socket_fd;
    struct sockaddr_in ip;
    socklen_t sock_len;

    socket_fd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (socket_fd < 0)
    {
        char * err = "erro na criacao do sock\n";

        write (2, err, strlen(err));
        exit (42);
    }

    char *buffer = build_echo_request();
    memset (&ip, '\0', sizeof (struct sockaddr_in));
    ip.sin_family = AF_INET;
    ip.sin_port = 0;
    ip.sin_addr.s_addr = inet_addr("8.8.8.8");
    sock_len = sizeof (struct sockaddr_in);

    sendto(socket_fd, buffer, 64, 0, (struct sockaddr *) &ip, sock_len);
}