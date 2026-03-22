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

#include <signal.h>
#include <stdio.h>
#include <errno.h>

# define ECHO_REQUEST_BUFFER_SIZE 1500

char * build_echo_request();
void read_echo_reply(char * buffer, size_t size);
void endless_loop();

typedef struct ping
{
    int seq;
    pid_t pid;
    int socket;
    char recv_buffer[100];
    char sendto_buffer[100];

} ft_ping;

extern ft_ping ping;


#endif