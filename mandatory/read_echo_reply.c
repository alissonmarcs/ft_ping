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

    ip = (struct ip *) buffer;
    ip_header_size = ip->ip_hl << 2;
    icmp = (struct icmp *) buffer + ip_header_size;
    size_t icmp_data_len = size - (ip_header_size + 8);

    struct timeval result;
    struct timeval current_time;
    struct timeval * send_time = (struct timeval *) icmp->icmp_data;

    memset(&result, '\0', sizeof (result));
    gettimeofday(&current_time, NULL);

    timersub(send_time, &current_time, &result);

    // long long result_miliseconds = (result.tv_sec * 1000) + (result.tv_usec / 1000);
    printf("miliseconds: %ld.%ld ms\n", result.tv_sec * 1000, result.tv_usec);
    // print_bytes(buffer, size);
}