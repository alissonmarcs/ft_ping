#include "ft_ping.h"

// ICMP_ECHO = 8

ft_ping ping;

void handler(int sig)
{
    if (sig != SIGALRM)
        return ;
    build_echo_request();
    if (sendto(ping.socket_fd, ping.echo_request, ECHO_REQUEST_SIZE, 0, (struct sockaddr *) &ping.sendto_remote_host, ping.sendto_remote_host_len) < 0)
        FATAL_ERROR("sendto()");
    alarm(1);
}

int main()
{
    struct sigaction config_handler;

    memset(&config_handler, '\0', sizeof(config_handler));
    config_handler.sa_handler = handler;
    config_handler.sa_flags = SA_RESTART;

    if (sigaction(SIGALRM, &config_handler, NULL) == -1)
        FATAL_ERROR("sigaction()");

    ping.pid = getpid() & 0xffff;
    ping.seq = 1;

    resolve_hostname("google.com");

    ping.socket_fd = socket(ping.socket_domain, ping.socket_type, ping.socket_protocol);
    if (ping.socket_fd < 0)
        FATAL_ERROR("socket()");

    handler(SIGALRM);
    endless_loop();
}