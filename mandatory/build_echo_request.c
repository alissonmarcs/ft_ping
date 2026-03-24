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

void build_echo_request()
{
    struct icmp *buffer;

    buffer = (struct icmp *) ping.echo_request;
    memset(buffer, '\0', ECHO_REQUEST_SIZE);
    buffer->icmp_type = ICMP_ECHO;
    buffer->icmp_code = 0;
    buffer->icmp_id = ping.pid;
    buffer->icmp_seq = ping.seq;
    ping.seq++;
    memset(buffer->icmp_data, 0xa5, 56);
    gettimeofday((struct timeval *) buffer->icmp_data, NULL);
    buffer->icmp_cksum = 0;
    buffer->icmp_cksum = calculate_check_sum( (uint16_t *) buffer, ECHO_REQUEST_SIZE);
}