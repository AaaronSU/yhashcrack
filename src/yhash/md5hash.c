#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"

#define swap()							\
  {								\
    temp = D;							\
    D = C;							\
    C = B;							\
    B += lrot(A + F + *(md5_k + i) + *(M + g), *(s + i));	\
    A = temp;							\
  }

//
const u32 s[64] __attribute__((aligned(ALIGN))) = { 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,    //0  - 15
						    5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20,    //16 - 31
						    4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,    //32 - 47
						    6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21 };  //48 - 63

//k[i] = floor(abs(sin(i + 1) * 2^32))
const u32 md5_k[64] __attribute__((aligned(ALIGN))) = { 0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
							  0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
							  0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
							  0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
							  0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
							  0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
							  0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
							  0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
							  0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
							  0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
							  0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
							  0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
							  0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
							  0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
							  0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
							  0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391 };

//len ==> number of bytes (length)
void md5hash(const u8 *restrict msg, const u64 len, u8 *restrict hash)
{
  u8 *newmsg = NULL;
  u64 newlen = len, g;
  u32 M[16] __attribute__((aligned(ALIGN))), F, A, B, C, D, temp, 
      a0 = 0x67452301, b0 = 0xEFCDAB89, c0 = 0x98BADCFE, d0 = 0x10325476;
  
  //Padding !
  
  while ((++newlen & 63) != 56) 
    ;
  
  newmsg = malloc(newlen + 8); //8 => 2 u32 (len) - Replace with aligned malloc 
  memcpy(newmsg, msg, len);    //Replace with fast memcpy
  
  *(newmsg + len) = 0x80; //Padding with '1' bit
  
  for (u32 i = len + 1; i < newlen; i++) //Padding with '0' bit
    *(newmsg + i) = 0x00;
  
  //u_int2byte_le(len << 3 , newmsg + newlen); //Padding with len
  u32_to_u8_le(len << 3 , newmsg + newlen); //Padding with len
  //u_int2byte_le(len >> 29, newmsg + newlen + 4); //(len << 3) >> 32 ==> len >> 29
  u32_to_u8_le(len >> 29, newmsg + newlen + 4); //(len << 3) >> 32 ==> len >> 29
  
  //Hashing !
  
  for (u32 block = 0; block < newlen; block += 64) //Iterating over 512-bit (64-byte) sized blocks
    {
      break16(u8_to_u32_le, M, newmsg + block);
      
      A = a0, B = b0, C = c0, D = d0;
            
      //Break the loop to avoid index range check 
      for (u32 i = 0; i < 16; i++)
	{
	  //F = (B & C) | ((~B) & D) works too.
	  F = D ^ (B & (C ^ D)), g = i;
	  swap();
	}
 
      for (u32 i = 16; i < 32; i++)
	{
	  //F = (D & B) | ((~D) & C) works too.
	  F = C ^ (D & (B ^ C)), g = ((i << 2) + i + 1) & 15;
	  swap();
	}
      
      for (u32 i = 32; i < 48; i++)
	{
	  F = B ^ C ^ D, g = ((i << 1) + i + 5) & 15; 
	  swap();
	}
      
      for (u32 i = 48; i < 64; i++)
	{
	  F = C ^ (B | (~D)), g = ((i << 2) + (i << 1) + i) & 15;
	  swap();
	}
      
      a0 += A;
      b0 += B;
      c0 += C;
      d0 += D;
    }
  
  u32_to_u8_le(a0, hash);
  u32_to_u8_le(b0, hash + 4);
  u32_to_u8_le(c0, hash + 8);
  u32_to_u8_le(d0, hash + 12);
  
  free(newmsg);
}
