#include <stdio.h>
#include "common.h"

//
void printhash(const u8 *restrict hash, const u32 size)
{
  for (int i = 0; i < size; i++)
    printf("%2.2x", hash[i]);
  
  printf("\n");
}

//Convert a u32 into 4 bytes - no implicit casting ! (little-endian)
void u32_to_u8_le(const u32 u, u8 *restrict b)
{
  b[3] = u >> 24;
  b[2] = u >> 16;
  b[1] = u >>  8;
  b[0] = u;
}

//Converts 4 bytes into a u32 - no implicit casting ! (little-endian)
u32 u8_to_u32_le(const u8 *restrict b)
{
  register u32 tmp = b[3];
  
  tmp = (tmp << 8) | b[2];
  tmp = (tmp << 8) | b[1];
  tmp = (tmp << 8) | b[0];
  
  return tmp;
}

//Convert u32 into 4 bytes (big-endian)
void u32_to_u8_be(const u32 u, u8 *restrict b)
{
  b[3] = u;
  b[2] = u >> 8;
  b[1] = u >> 16;
  b[0] = u >> 24;
} 

//Convert 4 bytes into a u32 (big-endian) 
u32 u8_to_u32_be(const u8 *restrict b)
{
  register u32 tmp = b[0];
  
  tmp = (tmp << 8) | b[1];
  tmp = (tmp << 8) | b[2];
  tmp = (tmp << 8) | b[3];
  
  return tmp;
}

//Convert u64 into 8 bytes (big-endian)
void u64_to_u8_be(const u64 u, u8 *restrict b)
{
  b[7] = u;
  b[6] = u >> 8;
  b[5] = u >> 16;
  b[4] = u >> 24;
  b[3] = u >> 32;
  b[2] = u >> 40;
  b[1] = u >> 48;
  b[0] = u >> 56;
} 

//Convert 8 bytes to u64 (big-endian)
u64 u8_to_u64_be(u8 *restrict b)
{
  register u64 tmp = b[0];
  
  tmp = (tmp << 8) | b[1];
  tmp = (tmp << 8) | b[2];
  tmp = (tmp << 8) | b[3];
  tmp = (tmp << 8) | b[4];
  tmp = (tmp << 8) | b[5];
  tmp = (tmp << 8) | b[6];
  tmp = (tmp << 8) | b[7];
  
  return tmp;
} 

//Convert u_int128 into 16 bytes (big-endian)
void u128_to_u8_be(const u128 u, u8 *restrict b)
{
  b[15] = u;
  b[14] = u >>   8;
  b[13] = u >>  16;
  b[12] = u >>  24;
  b[11] = u >>  32;
  b[10] = u >>  40;
  b[ 9] = u >>  48;
  b[ 8] = u >>  56;
  b[ 7] = u >>  64;
  b[ 6] = u >>  72;
  b[ 5] = u >>  80;
  b[ 4] = u >>  88;
  b[ 3] = u >>  96;
  b[ 2] = u >> 104;
  b[ 1] = u >> 112;
  b[ 0] = u >> 120;
} 
