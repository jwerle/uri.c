
/**
 * `encode.c' - uri.c
 *
 * copyright (c) 2014 joseph werle
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "uri.h"

#define IN_URANGE(a,b,c) (a >= (unsigned int) b && a <= (unsigned int) c)

char *
uri_encode (const char *src) {
  int i = 0;
  size_t size = 0;
  size_t len = 0;
  char *enc = NULL;
  char tmp[4];
  char ch = 0;

  // alloc
  enc = (char *) malloc(0);
  if (NULL == enc) { return NULL; }

  // chars length
  len = strlen(src);

#define push(c) (                                           \
    enc = (char *) realloc(enc, (size + 1) * sizeof(char)), \
    enc[size++] = c                                         \
)

  // encode
  while (len--) {
    ch = src[i++];
    // if high surrogate ensure next is
    // low surrogate for valid surrogate
    // pair
    if (IN_URANGE(ch, 0xD800, 0xDBFF)) {
      if (!IN_URANGE(src[i], 0xDC00, 0xDFFF)) {
        // @TODO - handle with malformed uri error
        break;
      }
    }

    // alpha capital/small
    if (IN_URANGE(ch, 0x0041, 0x005A) ||
        IN_URANGE(ch, 0x061, 0x007A)) {
      push(ch);
      continue;
    }

    // decimal digits
    if (IN_URANGE(ch, 0x0030, 0x0039)) {
      push(ch);
      continue;
    }

    // reserved chars
    // - _ . ! ~ * ' ( )
    if ('-' == ch || '_' == ch || '.' == ch ||
        '!' == ch || '~' == ch || '*' == ch ||
        '(' == ch || ')' == ch ) {
      push(ch);
      continue;
    }

    // encode
    sprintf(tmp, "%%%x", ch & 0xff);

    // prefix
    push(tmp[0]);

    // codec
    push(toupper(tmp[1]));
    push(toupper(tmp[2]));
  }

  enc[size] = '\0';

#undef push

  return enc;
}

#undef IN_URANGE
