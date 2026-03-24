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

#include <sys/epoll.h>

# define ECHO_REQUEST_SIZE 64
# define FATAL_ERROR(msg) fatal_error (msg, __FILE__, __LINE__)

void read_echo_reply(char * buffer, size_t size);
void endless_loop();
void fatal_error (const char *msg, const char *file, long line);

void build_echo_request();
void handler(int sig);
struct addrinfo * resolve_hostname(char * hostname);

typedef struct ping
{
    int seq;
    pid_t pid;
    int socket_fd;
    int socket_domain;
    int socket_type;
    int socket_protocol;
    char echo_reply[ECHO_REQUEST_SIZE];
    char echo_request[ECHO_REQUEST_SIZE];
    struct sockaddr_in sendto_remote_host;
    socklen_t sendto_remote_host_len;

} ft_ping;

extern ft_ping ping;


#endif