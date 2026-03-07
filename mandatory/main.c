#include <stdio.h>
#include <errno.h>
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
    if (inet_aton("8.8.8.8", &ip.sin_addr) == 0)
    {
        write(2, "erro no endereco IP\n", 20);
        exit(42);
    }
    // ip.sin_addr.s_addr = inet_addr("8.8.8.8");
    sock_len = sizeof (struct sockaddr_in);

    ssize_t ret = sendto(socket_fd, buffer, 64, 0, (struct sockaddr *) &ip, sock_len);
    if (ret < 0)
    {
        perror("sendto: ");
        printf("errno: %d", errno);
    }

    char recv_buffer[1024];
    struct sockaddr_in recv_addr;
    socklen_t recv_len = sizeof(recv_addr);

    ssize_t bytes_received = recvfrom(socket_fd, recv_buffer, sizeof(recv_buffer), 0,
                                      (struct sockaddr *)&recv_addr, &recv_len);

    if (bytes_received < 0)
    {
        char *err = "erro ao receber resposta\n";
        write(2, err, strlen(err));
        exit(42);
    }

    printf("Recebidos %ld bytes de %s\n", bytes_received, inet_ntoa(recv_addr.sin_addr));
    read_echo_reply(recv_buffer, bytes_received);
}