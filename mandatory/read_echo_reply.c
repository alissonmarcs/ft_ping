#include "ft_ping.h"


void print_bytes(char * arr, size_t bytes)
{
   int i = 0;
   
   while (i < bytes)
   {
        printf("byte %d: %d\n", i, arr[i]);
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
    print_bytes(buffer, size);
}