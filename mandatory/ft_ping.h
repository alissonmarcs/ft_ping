#ifndef FT_PING_H

# define FT_PING_H

#include <netinet/ip.h>
#include <netinet/ip_icmp.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <arpa/inet.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

# define ECHO_REQUEST_BUFFER_SIZE 1500

char * build_echo_request();
void read_echo_reply(char * buffer, size_t size);

typedef struct ping
{
    int seq;
    pid_t pid;
} ft_ping;


#endif