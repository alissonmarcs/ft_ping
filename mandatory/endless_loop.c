
#include "ft_ping.h"

void endless_loop()
{
    ssize_t bytes_received;

    while (1)
    {
        if ((bytes_received = recvfrom(ping.socket_fd, ping.raw_echo_reply, ECHO_REQUEST_SIZE, 0, NULL, NULL)) < 0) 
            FATAL_ERROR("recvfrom()");
        read_echo_reply(ping.raw_echo_reply, bytes_received);
    }
}