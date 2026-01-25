#include "ft_ping.h"

char * build_echo_request()
{
    char * echo_request;
    struct icmp *message;

    echo_request = malloc(ECHO_REQUEST_BUFFER_SIZE);
    memset(echo_request, '\0', ECHO_REQUEST_BUFFER_SIZE);
    message = (struct icmp *) echo_request;
    message->icmp_type = ICMP_ECHO;
    message->icmp_code = 0;
    message->icmp_id = getpid() & 0xffff;
    message->icmp_seq = 1;
    message->icmp_cksum = 42;
    gettimeofday((struct timeval *) message->icmp_data, NULL);

    return echo_request;
}