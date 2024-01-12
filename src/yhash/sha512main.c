#include <stdio.h>
#include <string.h>

#include "yhash.h"

int main(int argc, char **argv)
{
  if (argc < 2)
    return printf("%s [STRING]\n", argv[0]), 0;

  u64 len = strlen(argv[1]);
  u8 hash[SHA512_HASH_SIZE] __attribute__((aligned(ALIGN)));
  
  sha512hash(argv[1], strlen(argv[1]), hash);
  
  printhash(hash, SHA512_HASH_SIZE);
  
  return 0;
}
