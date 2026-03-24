
#include "ft_ping.h"

void endless_loop()
{
    ssize_t bytes_received;
    while ("I LOVE 42 FOREVER !!!!")
    {
        if ((bytes_received = recvfrom(ping.socket_fd, ping.echo_reply, ECHO_REQUEST_SIZE, 0, NULL, NULL)) < 0) 
            FATAL_ERROR("recvfrom()");
        read_echo_reply(ping.echo_reply, bytes_received);
    }
}