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

void help()
{
    printf("Usage: ft_ping [options] host\n");
    printf("Options:\n");
    printf("\t-v\tverbose mode\n");
    printf("\t-?\tthis help message\n");

   exit(0);
}

int main(int argc, char *argv[])
{
    int option, v_flag, help_flag;

    option = v_flag = help_flag = 0;
    while ((option = getopt(argc, argv, "v?")) != -1)
    {
        if (option == '?')
            help();
        else if (option == 'v')
            v_flag = 1;
    }

    if (optind == argc)
    {
        dprintf(
            2,
            "ft_ping: missing host operand\n"
            "Try 'ft_ping -?' for more information.\n"
        );
        exit(1);
    }


    struct sigaction config_handlers;

    memset(&config_handlers, '\0', sizeof(config_handlers));
    config_handlers.sa_handler = handler_sigalarm;
    config_handlers.sa_flags = SA_RESTART;

    if (sigaction(SIGALRM, &config_handlers, NULL) == -1)
        FATAL_ERROR("sigaction()");

    memset(&config_handlers, '\0', sizeof(config_handlers));
    config_handlers.sa_handler = handler_sigint;

    if (sigaction(SIGINT, &config_handlers, NULL) == -1)
        FATAL_ERROR("sigaction()");

    ping.pid = getpid() & 0xffff;

    resolve_hostname(argv[optind]);

    printf("PING %s (%s): 56 data bytes\n", ping.canonical_domain_name, ping.remote_host_ip);

    ping.socket_fd = socket(ping.socket_domain, ping.socket_type, ping.socket_protocol);
    if (ping.socket_fd < 0)
        FATAL_ERROR("socket()");

    handler_sigalarm(SIGALRM);
    endless_loop();
}