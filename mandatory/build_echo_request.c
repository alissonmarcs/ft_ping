#include "ft_ping.h"

uint16_t
calculate_check_sum (uint16_t * addr, int len)
{
    int nleft = len;

    uint32_t sum = 0;
    uint16_t *w = addr;
    uint16_t answer = 0;

    while (nleft > 1) {
        sum += *w++;
        nleft -= 2;
    }

    if (nleft == 1) {
        * (unsigned char *) (&answer) = * (unsigned char *) w;
        sum += answer;
    }
    
    sum = (sum >> 16) + (sum & 0xffff);
    sum += (sum >> 16);
    answer = ~sum;
    return (answer);
}

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
    gettimeofday((struct timeval *) message->icmp_data, NULL);
    message->icmp_cksum = 0;
    message->icmp_cksum = calculate_check_sum( (uint16_t *) echo_request, 64);

    return echo_request;
}