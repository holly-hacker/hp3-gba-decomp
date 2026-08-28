/* newlib's bzero, identical in newlib 1.8.2 through 1.10.0; 1.11.0 widened
   the first parameter to void *.
   https://sourceware.org/pub/newlib/ -- licence: COPYING.NEWLIB. */

#include <stddef.h>

void
bzero (char *b, size_t length)
{
  while (length--)
    *b++ = 0;
}
