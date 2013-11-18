/* this file gets replaced with our own driver when we grade your submission.
 * So do what you want here but realize it won't persist when we grade it.
 */

#include <stdio.h>
#include <stdlib.h>
#include "KeccakF1600.h"
#include "Keccak_r1024.h"


int main(){

 unsigned char *mess = 
        "\x83\xAF\x34\x27\x9C\xCB\x54\x30\xFE\xBE\xC0\x7A\x81\x95\x0D\x30"
        "\xF4\xB6\x6F\x48\x48\x26\xAF\xEE\x74\x56\xF0\x07\x1A\x51\xE1\xBB"
        "\xC5\x55\x70\xB5\xCC\x7E\xC6\xF9\x30\x9C\x17\xBF\x5B\xEF\xDD\x7C"
        "\x6B\xA6\xE9\x68\xCF\x21\x8A\x2B\x34\xBD\x5C\xF9\x27\xAB\x84\x6E"
        "\x38\xA4\x0B\xBD\x81\x75\x9E\x9E\x33\x38\x10\x16\xA7\x55\xF6\x99"
        "\xDF\x35\xD6\x60\x00\x7B\x5E\xAD\xF2\x92\xFE\xEF\xB7\x35\x20\x7E"
        "\xBF\x70\xB5\xBD\x17\x83\x4F\x7B\xFA\x0E\x16\xCB\x21\x9A\xD4\xAF"
        "\x52\x4A\xB1\xEA\x37\x33\x4A\xA6\x64\x35\xE5\xD3\x97\xFC\x0A\x06"
        "\x5C\x41\x1E\xBB\xCE\x32\xC2\x40\xB9\x04\x76\xD3\x07\xCE\x80\x2E"
        "\xC8\x2C\x1C\x49\xBC\x1B\xEC\x48\xC0\x67\x5E\xC2\xA6\xC6\xF3\xED"
        "\x3E\x5B\x74\x1D\x13\x43\x70\x95\x70\x7C\x56\x5E\x10\xD8\xA2\x0B"
        "\x8C\x20\x46\x8F\xF9\x51\x4F\xCF\x31\xB4\x24\x9C\xD8\x2D\xCE\xE5"
        "\x8C\x0A\x2A\xF5\x38\xB2\x91\xA8\x7E\x33\x90\xD7\x37\x19\x1A\x07"
        "\x48\x4A\x5D\x3F\x3F\xB8\xC8\xF1\x5C\xE0\x56\xE5\xE5\xF8\xFE\xBE"
        "\x5E\x1F\xB5\x9D\x67\x40\x98\x0A\xA0\x6C\xA8\xA0\xC2\x0F\x57\x12"
        "\xB4\xCD\xE5\xD0\x32\xE9\x2A\xB8\x9F\x0A\xE1";



 unsigned char *Z_ref=
   "\xB4\xF0\x1B\xAB\x85\x19\x45\x9E\x87\xC6\x80\xB5\x63\xC6\x45\xF3"
   "\x05\x2D\x63\xA2\x55\x5D\x64\x9E\xB1\xD6\xAD\xEA\x45\xF4\x23\x1B"
   "\xB2\x9D\x16\x3E\x0C\x83\x02\xE5\xAC\x33\x43\x9C\xE8\x1F\x5C\xB7"
   "\x6E\x81\x61\x7C\x31\xF0\xEF\x5F\x0F\x03\x54\x94\x29\x7B\x6B\x9B"
   "\x6C\xD1\x9D\x75\xE2\x63\x3A\x8F\x8E\xC3\x3B\x3E\x2D\x71\x06\x35"
   "\xEF\xAC\xC0\x10\x96\x07\x1A\xF5\xA0\x63\xA6\xF5\xE9\x09\x87\xA8"
   "\x2F\xD3\xB1\xE6\xE0\x64\x8F\xE2\xCD\x43\xF6\x55\xC1\xC1\xB9\x48"
   "\x1D\xDB\xDD\xBF\x48\xD5\xA6\x1E\x08\x5B\xF3\x8E\xCD\xFD\x80\x65";


 unsigned char *Z=Hash(mess,251);

 //Check the validity of the tag.
  int x;
  int count=1;
  for(int i=0;i<128;i++){
    if(Z[i]!=Z_ref[i]){
	count=0;
      }
  }
  if(count==0){
    printf("FAIL\n");
  }
  else{
    printf("PASS\n");
  }

 
}