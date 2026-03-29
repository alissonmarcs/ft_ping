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
    missing_host_error ();

  setup_signal_handlers ();

  ping.pid = getpid () & 0xffff;

  resolve_hostname (argv[optind]);

  ping.socket_fd
      = socket (ping.socket_domain, ping.socket_type, ping.socket_protocol);
  if (ping.socket_fd < 0)
    {
      dprintf (2, "ft_ping: Lacking privilege for icmp socket.\n");
      exit (1);
    }

  printf ("PING %s (%s): 56 data bytes", ping.canonical_domain_name,
          ping.remote_host_ip);
  if (v_flag)
    printf ("id %#x = %d\n", ping.pid, ping.pid);
  else
    printf ("\n");

  handler_sigalarm (SIGALRM);
  endless_loop ();
}