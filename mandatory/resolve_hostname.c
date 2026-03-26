#include "ft_ping.h"

void resolve_hostname(char * hostname)
{
    struct addrinfo hints;
    struct addrinfo *result = NULL;
    struct addrinfo *current = NULL;

    memset(&hints, '\0', sizeof (struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_RAW;
    hints.ai_flags = 0;
    hints.ai_protocol = IPPROTO_ICMP;

    if (getaddrinfo(hostname, NULL, &hints, &result) < 0)
        FATAL_ERROR("getaddrinfo()");

    current = result;
    while (current != NULL)
    {
        if (current->ai_family == AF_INET)
           break; 
        current = current->ai_next;
    }

    if (current == NULL)
        FATAL_ERROR("getaddrinfo() arrived at end of linked list");

    ping.socket_domain = current->ai_family;
    ping.socket_type = current->ai_socktype;
    ping.socket_protocol = current->ai_protocol;

    memcpy(&ping.sendto_remote_host, current->ai_addr, current->ai_addrlen);
    ping.sendto_remote_host_len = current->ai_addrlen;
    if (inet_ntop(AF_INET, &ping.sendto_remote_host.sin_addr, ping.remote_host_ip, INET_ADDRSTRLEN) == NULL) 
        FATAL_ERROR("inet_ntop");
    freeaddrinfo(result);
}