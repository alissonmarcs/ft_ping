#ifndef FT_PING_H

#define FT_PING_H

#include <netinet/ip.h>
#include <netinet/ip_icmp.h>

#include <arpa/inet.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <unistd.h>

#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <errno.h>
#include <signal.h>
#include <stdio.h>

#include <math.h>
#include <sys/epoll.h>

#define ECHO_REQUEST_SIZE 64
#define FATAL_ERROR(msg) fatal_error (msg, __FILE__, __LINE__)

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

void read_echo_reply (char *buffer, size_t size);
void endless_loop ();
void fatal_error (const char *msg, const char *file, long line);
void build_echo_request ();
void handler (int sig);
void resolve_hostname (char *hostname);
void handler_sigalarm (int sig);
void handler_sigint (int sig);
void help ();
void setup_signal_handlers ();

typedef struct ping
{
  int seq;
  pid_t pid;
  int socket_fd;
  int socket_domain;
  int socket_type;
  int socket_protocol;
  char raw_echo_reply[ECHO_REQUEST_SIZE];
  char echo_request[ECHO_REQUEST_SIZE];
  char remote_host_ip[INET_ADDRSTRLEN];
  char canonical_domain_name[255];
  char *remote_host_domain_name;
  struct sockaddr_in sendto_remote_host;
  socklen_t sendto_remote_host_len;
  double current_rtt;
  double min_rtt;
  double max_rtt;
  double avg_rtt;
  double stddev_rtt;
  double rtt_sum;
  double rtt_sum2;
  int packets_transmitted;
  int packets_received;
} ft_ping;

typedef struct carla
{
  int icmp_sequence;
  double round_trip_time;
  int time_to_live;
} echo_reply;

extern ft_ping ping;

#endif