#include "ft_ping.h"

// ICMP_ECHO = 8

ft_ping ping;

void handler_sigalarm(int sig)
{
    if (sig != SIGALRM)
        return ;
    build_echo_request();
    if (sendto(ping.socket_fd, ping.echo_request, ECHO_REQUEST_SIZE, 0, (struct sockaddr *) &ping.sendto_remote_host, ping.sendto_remote_host_len) < 0)
        FATAL_ERROR("sendto()");
    ping.packets_transmitted++;
    alarm(1);
}

void handler_sigint(int sig)
{
    if (sig != SIGINT)
        return; 
    printf("--- %s ping statistics ---\n", ping.remote_host_ip);

    double package_loss_percent = (1.0 - ( (double) ping.packets_received / ping.packets_transmitted)) * 100;

    double mean = ping.rtt_sum / ping.packets_received;
    double varience = (ping.rtt_sum2 / ping.packets_received) - (mean * mean);
    double stddev = sqrt(varience);

    printf("%d packets transmitted, %d packets received, %d%% packet loss\n", ping.packets_transmitted, ping.packets_received, (int) package_loss_percent);
    printf("round-trip min/avg/max/stddev = %.3f/%.3f/%.3f/%.3f ms\n", ping.min_rtt, mean, ping.max_rtt, stddev);
    exit(0);
}

int main(int argc, char **argv)
{
    struct sigaction config_handler;

    memset(&config_handler, '\0', sizeof(config_handler));
    config_handler.sa_handler = handler_sigalarm;
    config_handler.sa_flags = SA_RESTART;

    if (sigaction(SIGALRM, &config_handler, NULL) == -1)
        FATAL_ERROR("sigaction()");

    memset(&config_handler, '\0', sizeof(config_handler));
    config_handler.sa_handler = handler_sigint;

    if (sigaction(SIGINT, &config_handler, NULL) == -1)
        FATAL_ERROR("sigaction()");

    ping.pid = getpid() & 0xffff;

    (void) argc;
    // ping.remote_host_domain_name = argv[1];

    resolve_hostname(argv[1]);

    printf("PING %s (%s): 56 data bytes\n", ping.canonical_domain_name, ping.remote_host_ip);

    ping.socket_fd = socket(ping.socket_domain, ping.socket_type, ping.socket_protocol);
    if (ping.socket_fd < 0)
        FATAL_ERROR("socket()");

    handler_sigalarm(SIGALRM);
    endless_loop();
}