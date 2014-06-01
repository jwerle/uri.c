uri.c
=====

URI Component encoder/decoder

## install

```sh
$ clib install littlstar/uri.c
```

## usage

```c
#include <uri/uri.h
```

or

```c
#include <uri.h>
```

```c

#include <stdio.h>
#include <string.h>
#include "uri.h"

int
main (void) {
  char *enc = NULL;
  char *dec = NULL;

  enc = uri_encode("Betty's favorite language is Français");
  printf("%s\n", enc); // Betty%27s%20favorite%20language%20is%20Fran%C3%A7ais

  dec = uri_decode(enc);
  printf("%s\n", dec); // Betty's favorite language is Français
  return 0;
}
```

## api

Encodes a URI component by replacing each
instance of certain characters by one, two, three, or four escape
sequences representing the UTF-8 encoding of the character

```c
char *
uri_encode (const char *);
```

Decodes a URI component source from `uri_encode`

```c
char *
uri_decode (const char *);
```

## license

MIT
