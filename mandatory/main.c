#include <stdio.h>

#include "ft_ping.h"

// ICMP_ECHO = 8

int main()
{
    int fd = open("demo", O_RDWR | O_TRUNC | O_CREAT);
    int len_echo_request = 56 + 8;
    char * buffer = build_echo_request();
    write(fd, buffer, len_echo_request);
}