#include "ft_ping.h"

// ICMP_ECHO = 8

ft_ping ping;

void handler(int sig)
{
    (void) sig;
    printf("OII\n");
    alarm(1);
}

int main()
{
    // struct sigaction config_handler;

    // memset(&config_handler, '\0', sizeof(config_handler));
    // config_handler.sa_handler = handler;

    // sigaction(SIGALRM, &config_handler, NULL);

    // handler(42);

    // while (1)
    //     ;

    ping.pid = getpid() & 0xffff;
    ping.seq = 1;

    printf("ft_ping pid: %d\n", ping.pid);

    int socket_fd;
    struct sockaddr_in remote_host;
    socklen_t remote_host_len;
    memset(&remote_host, '\0', sizeof (struct sockaddr_in));

    socket_fd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (socket_fd < 0)
        FATAL_ERROR("socket()");

    if (inet_aton("127.0.0.1", &remote_host.sin_addr) == 0)
        FATAL_ERROR("inet_aton()");
    remote_host_len = sizeof (struct sockaddr_in);

    while (42)
    {
        build_echo_request_v2();

        if (sendto(socket_fd, ping.echo_request, ECHO_REQUEST_SIZE, 0, (struct sockaddr *) &remote_host, remote_host_len) < 0)
            FATAL_ERROR("sendto()");

        size_t bytes_received;
        if ((bytes_received = recvfrom(socket_fd, ping.echo_reply, ECHO_REQUEST_SIZE, 0, NULL, NULL)) < 0) 
            FATAL_ERROR("recvfrom()");
        read_echo_reply(ping.echo_reply, bytes_received);
        sleep(1);
    }


    // ft_ping ping;

    // memset(&ping, '\0', sizeof (ft_ping));

    // int socket_fd;

    // char *buffer = build_echo_request();

    // struct addrinfo hints;
    // memset(&hints, '\0', sizeof (struct addrinfo));
    // hints.ai_family = AF_INET;
    // hints.ai_socktype = SOCK_RAW;
    // hints.ai_flags = 0;
    // hints.ai_protocol = IPPROTO_ICMP;

    // struct addrinfo *result = NULL;
    // int getaddrinfo_ret;
    // char * host_name = "google.com";

    // getaddrinfo_ret = getaddrinfo(host_name, NULL, &hints, &result);
    // if (getaddrinfo_ret < 0)
    // {
    //     perror("getaddrinfo");
    //     printf("error: %s\n", gai_strerror(errno));
    //     exit(42);
    // }

    // struct addrinfo *current;
    // for (current = result; current != NULL; current = current->ai_next)
    // {
    //     if (current->ai_family == AF_INET)
    //     {
    //        break; 
    //     }
    //     else
    //     {
    //         printf("familia nao suportada: %d\n", current->ai_family);
    //     }

    // }
    // if (current == NULL)
    // {
    //     printf("nao encontramos ip para o host\n");
    //     exit(42);
    // }
    // struct addrinfo *dest_node = current;

    // // printf("dest_node->ai_socktype == : %d\n") 


    // socket_fd = socket(dest_node->ai_family, dest_node->ai_socktype, dest_node->ai_protocol);
    // if (socket_fd < 0)
    // {
    //     char * err = "erro na criacao do sock\n";

    //     write (2, err, strlen(err));
    //     exit (42);
    // }


    // struct sockaddr * dest_addr = current->ai_addr; 
    // socklen_t dest_addr_len = current->ai_addrlen;

    // ssize_t ret = sendto(socket_fd, buffer, 64, 0,  dest_addr, dest_addr_len);
    // if (ret < 0)
    // {
    //     perror("sendto");
    //     printf("errno: %d\n", errno);
    //     exit(42);
    // }

    // printf("AQUII\n");

    // char recv_buffer[1024];
    // struct sockaddr_in recv_addr;
    // socklen_t recv_len = sizeof(recv_addr);

    // ssize_t bytes_received = recvfrom(socket_fd, recv_buffer, sizeof(recv_buffer), 0,
    //                                   (struct sockaddr *)&recv_addr, &recv_len);

    // if (bytes_received < 0)
    // {
    //     char *err = "erro ao receber resposta\n";
    //     write(2, err, strlen(err));
    //     exit(42);
    // }

    // printf("Recebidos %ld bytes de %s\n", bytes_received, inet_ntoa(recv_addr.sin_addr));
    // read_echo_reply(recv_buffer, bytes_received);
}