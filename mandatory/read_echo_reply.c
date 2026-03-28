#include "ft_ping.h"


void print_bytes(char * arr, size_t bytes)
{
   size_t i = 0;
   
   while (i < bytes)
   {
        printf("byte %ld: %c\n", i, arr[i]);
        i++;
   }
}

void read_echo_reply(char * buffer, size_t size)
{
    struct ip * ip;
    struct icmp * icmp;
    size_t ip_header_size;
    size_t icmp_package_len;
    double rtt;

    ip = (struct ip *) buffer;

    if (ip->ip_p != IPPROTO_ICMP)
        return ;

    ip_header_size = ip->ip_hl << 2;
    icmp = (struct icmp *) (buffer + ip_header_size);

    if ((icmp_package_len = size - ip_header_size) < 8)
        return ;

    if (icmp->icmp_id != ping.pid) 
        return ;

    if (icmp->icmp_type != ICMP_ECHOREPLY) 
        return ;
    if (icmp_package_len < 16)
        return ;

    struct timeval result;
    struct timeval current_time;
    struct timeval * send_time = (struct timeval *) icmp->icmp_data;

    memset(&result, '\0', sizeof (result));

    gettimeofday(&current_time, NULL);
    timersub(&current_time, send_time, &result);
    rtt = (result.tv_sec * 1000.0) + (result.tv_usec / 1000.0);

    ping.rtt_sum += rtt;
    ping.rtt_sum2 += rtt * rtt;

    printf("%ld bytes from %s: icmp_seq=%d ttl=%d time=%.3f ms\n", size, ping.remote_host_ip, icmp->icmp_seq, ip->ip_ttl ,rtt);

    if (ping.min_rtt  == 0.0)
        ping.min_rtt = rtt;
    else
        ping.min_rtt = MIN(rtt, ping.min_rtt);
    ping.max_rtt = MAX(rtt, ping.max_rtt);
   
    ping.packets_received++;
}