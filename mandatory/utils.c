#include "ft_ping.h"

void fatal_error (const char *msg, const char *file, long line)
{
  fprintf (stderr, "Fatal error: %s in %s:%ld: %s\n", msg, file, line, strerror (errno));
  exit (EXIT_FAILURE);
}