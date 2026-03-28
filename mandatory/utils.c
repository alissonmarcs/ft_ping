#include "ft_ping.h"

void fatal_error (const char *msg, const char *file, long line)
{
  fprintf (stderr, "Fatal error: %s in %s:%ld: %s\n", msg, file, line, strerror (errno));
  exit (EXIT_FAILURE);
}

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

void setup_signal_handlers()
{
    struct sigaction handlers;

    memset(&handlers, '\0', sizeof(handlers));
    handlers.sa_handler = handler_sigalarm;
    handlers.sa_flags = SA_RESTART;

    if (sigaction(SIGALRM, &handlers, NULL) == -1)
        FATAL_ERROR("sigaction()");

    memset(&handlers, '\0', sizeof(handlers));
    handlers.sa_handler = handler_sigint;

    if (sigaction(SIGINT, &handlers, NULL) == -1)
        FATAL_ERROR("sigaction()");

}

void help()
{
    printf("Usage: ft_ping [options] host\n");
    printf("Options:\n");
    printf("\t-v\tverbose mode\n");
    printf("\t-?\tthis help message\n");

   exit(0);
}