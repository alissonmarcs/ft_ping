#include "ft_ping.h"

ft_ping ping;

int
main (int argc, char *argv[])
{
  int option, v_flag, help_flag;

  option = v_flag = help_flag = 0;
  while ((option = getopt (argc, argv, "v?")) != -1)
    {
      if (option == '?')
        help ();
      else if (option == 'v')
        v_flag = 1;
    }

  if (optind == argc)
    {
      dprintf (2, "ft_ping: missing host operand\n"
                  "Try 'ft_ping -?' for more information.\n");
      exit (1);
    }

  setup_signal_handlers ();

  ping.pid = getpid () & 0xffff;

  resolve_hostname (argv[optind]);

  printf ("PING %s (%s): 56 data bytes\n", ping.canonical_domain_name,
          ping.remote_host_ip);

  ping.socket_fd
      = socket (ping.socket_domain, ping.socket_type, ping.socket_protocol);
  if (ping.socket_fd < 0)
    FATAL_ERROR ("socket()");

  handler_sigalarm (SIGALRM);
  endless_loop ();
}