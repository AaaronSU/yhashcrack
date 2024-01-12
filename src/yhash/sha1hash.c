#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"

#define swap()					\
  {						\
    temp = lrot(A, 5) + F + E + g + M[i];	\
    E = D;					\
    D = C;					\
    C = lrot(B, 30);				\
    B = A;					\
    A = temp;					\
  }  						
    
//
void sha1hash(u8 *restrict msg, const u64 len, u8 *restrict hash)
{
  u8 *newmsg = NULL;
  u64 newlen = len;
  u32 M[80] __attribute__((aligned(ALIGN))), F, A, B, C, D, E, temp, g,  
      a0 = 0x67452301, b0 = 0xEFCDAB89, c0 = 0x98BADCFE, d0 = 0x10325476, e0 = 0xC3D2E1F0;
  
  //Padding !
  
  while ((++newlen & 63) != 56);
  
  newmsg = malloc(newlen + 8); //8 => u64 - Replace with aligned malloc 
  memcpy(newmsg, msg, len);    //Replace with fast memcpy
  
  *(newmsg + len) = 0x80; //Padding with '1' bit
  
  for (u32 i = len + 1; i < newlen; i++) //Padding with '0' bit
    *(newmsg + i) = 0x00;
  
  u64_to_u8_be(len << 3, newmsg + newlen);
  
  //Hashing
  
  for (u32 block = 0; block < newlen; block += 64)
    {
      break16(u8_to_u32_be, M, newmsg + block);
      
      //
      for (u32 i = 16; i < 80; i++)
	M[i] = lrot((M[i - 3] ^ M[i - 8] ^ M[i - 14] ^ M[i - 16]), 1);
      
      //Vectorizable !
      /* for (u32 i = 32; i < 80; i++) */
      /* 	M[i] = lrot(M[i - 6] ^ M[i - 16] ^ M[i - 28] ^ M[i - 32], 2); */
      
      A = a0, B = b0, C = c0, D = d0, E = e0;
      
      //Break the loop to avoid index range check 
      for (u32 i = 0; i < 20; i++)
	{
	  F = (B & C) | ((~B) & D), g = 0x5A827999;
	  swap();
	}
      
      for (u32 i = 20; i < 40; i++)
	{
	  F = B ^ C ^ D, g = 0x6ED9EBA1;
	  swap();
	}
      
      for (u32 i = 40; i < 60; i++)
	{
	  F = (B & C) | (B & D) | (C & D), g = 0x8F1BBCDC;
	  swap();
	}
      
      for (u32 i = 60; i < 80; i++)
	{
	  F = B ^ C ^ D, g = 0xCA62C1D6;
	  swap();
	}
      
      a0 += A;
      b0 += B;
      c0 += C;
      d0 += D;
      e0 += E;
    }
  
  u32_to_u8_be(a0, hash     );
  u32_to_u8_be(b0, hash +  4);
  u32_to_u8_be(c0, hash +  8);
  u32_to_u8_be(d0, hash + 12);
  u32_to_u8_be(e0, hash + 16);
  
  free(newmsg);
}
