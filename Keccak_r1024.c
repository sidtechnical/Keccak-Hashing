/**** Assignment -2 's code starts here*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "KeccakF1600.h"
#include "Keccak_r1024.h"

unsigned int R = 1024, w = 64;

// DO NOT MODIFY THE HEADING OF THIS FUNCTION
unsigned char* Hash(unsigned char* message, unsigned int length)
 {
        //Initialization and padding
        // Step 1 S[x,y] = 0

        unsigned long** S = malloc(5 * sizeof(unsigned long));  //defining the state array S
        int x;
        for (x = 0; x < 5; x++) 
	{
                S[x] = malloc(5 * sizeof(unsigned long));       // Allocating the required memory for  S array
        }

        //Here I am initializing  and assignning  the Value 0 to the state array S
        S[0][0] = 0;
        S[1][0] = 0;
        S[2][0] = 0;
        S[3][0] = 0;
        S[4][0] = 0;

        S[0][1] = 0;
        S[1][1] = 0;
        S[2][1] = 0;
        S[3][1] = 0;
        S[4][1] = 0;

        S[0][2] = 0;
        S[1][2] = 0;
	 S[2][2] = 0;
        S[3][2] = 0;
        S[4][2] = 0;

        S[0][3] = 0;
        S[1][3] = 0;
        S[2][3] = 0;
        S[3][3] = 0;
        S[4][3] = 0;

        S[0][4] = 0;
        S[1][4] = 0;
        S[2][4] = 0;
        S[3][4] = 0;
        S[4][4] = 0;

/* ------------------------------------------------------------------------------------------------------------------- */

        //P = M || 0x01 || 0x00 || … || 0x00

	//P = P xor (0x00 || … || 0x00 || 0x80)

        unsigned int how_many_blocks, padding_length, padding_byte;     //Declaring the variables used.

        how_many_blocks = (length / 128) + 1;  // calculating how many blocks are required for the padding length

        padding_length = how_many_blocks;

        padding_byte = 128 - (length % 128); // Calculating how many Bytes of _Padding is required

        unsigned char* padded_msg = malloc(length + padding_byte);

        memcpy(padded_msg, message, 251);       //Copying the message to an array called padded_msg which will be padded in later stages

        //If there is just one byte to be padded then the  last byte will be padded as 0x81
        if (padding_byte == 1)
	 {
                memcpy(padded_msg + length, "\x81", 1);
         } 
	else 
	{
                memcpy(padded_msg + length, "\x01", 1);         //In other cases, first byte to be padded is  0x01

		int i, pbpl;
                pbpl = (padding_byte + length) - 1;
                for (i = length + 1; i < pbpl; i++) {
                        memcpy(padded_msg + i, "\x00", 1);      //All the other bytes untill last byte will be padded as 0x00
                }
                memcpy(padded_msg + i, "\x80", 1);              //Last byte will padded as 0x80
        }

/*--------------------------------------  Making the P-Blocks of length 128 bytes-------------------------------------------------*/


        // Here the padded _msg will be divided into different blocks of 128 bytes each

        int k = 0;

        unsigned long** P = malloc(padding_length * sizeof(unsigned long));     //Defining the array P
        for (x = 0; x < padding_length; x++)
         {
                P[x] = malloc(16 * sizeof(unsigned long));                      //Allocating required memory to P
 	 }
        for (int i = 0; i < padding_length; i++) 
        {
                for (int j = 0; j < 16; j++,k+=8) 
                {
                        unsigned char* temp_array = malloc(sizeof(unsigned long)); //a temporary arry for copying
                        memcpy(temp_array, padded_msg + k, 8);                    //Copying the padded_msg byte by byte
                        memcpy(&P[i][j], temp_array, 8);                          // In very time temp_array is copied to array P
                }
        }

/* --------------------------------------------------------------------------------------------------------------------------------*/

        // Absorbing phase
        //  forall block Pi in P
        //    S[x,y] = S[x,y] xor Pi[x+5*y],          forall (x,y) such that x+5*y < r/w
        //    S = Keccak-f[r+c](S)

        for (int m = 0; m < padding_length; m++) 
	{
	 for (int x = 0; x < 5; x++)
		       {
                        for (int y = 0; y < 5; y++) {
                                if ((x + (5 * y)) < (R/w)) // Defined R =1024 and w = 64  globally
                                {
                                        S[x][y] ^= P[m][x + (5 * y)];
                                }
                        }
                }
          S = KeccakF(S);        //In each iteration the function state array S is fed to KeaackF from 1st assignment and 
                                 //not to  KeccakF_bytes function
        }


/* -----------------------------------------------   Squeezing phase ------- ----------------------------------------------------*/


        /* Z = Z || S[x,y] */
// Here the  array Z  is concatenated with S from previous step.
        unsigned char* Z = malloc(R / 8);
	int c = 0;
        for (int a = 0; a < 5; a++) 
	   {
                for (int b = 0; b < 5; b++, c+=8)
                 {
                        if (c < (R / 8)) 
                        {
                                memcpy(Z + c, &S[b][a], 8);
                        }
                 }
           }
  return Z;
 }

