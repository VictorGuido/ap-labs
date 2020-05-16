//Victor Jaret Guido
//base64
#include <inttypes.h>
#include <string.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "logger.h"

#define WHITESPACE 64
#define EQUALS     65
#define INVALID    66
#define MAX_SIZE 1000000

//size_t MAX_SIZE = 1000000;
size_t file_size;
size_t progress;

// ENCODE AND DECODE FUNCTIONS RETRIEVED FROM: https://en.wikibooks.org/wiki/Algorithm_Implementation/Miscellaneous/Base64

int base64encode(const void* data_buf, size_t dataLength, char* result, size_t resultSize)
{
   const char base64chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
   const uint8_t *data = (const uint8_t *)data_buf;
   size_t resultIndex = 0;
   size_t x;
   uint32_t n = 0;
   int padCount = dataLength % 3;
   uint8_t n0, n1, n2, n3;

   /* increment over the length of the string, three characters at a time */
   for (x = 0; x < dataLength; x += 3) 
   {
      infof("Coded char count: %li\n", x);
      progress = x;

      /* these three 8-bit (ASCII) characters become one 24-bit number */
      n = ((uint32_t)data[x]) << 16; //parenthesis needed, compiler depending on flags can do the shifting before conversion to uint32_t, resulting to 0
      
      if((x+1) < dataLength)
         n += ((uint32_t)data[x+1]) << 8;//parenthesis needed, compiler depending on flags can do the shifting before conversion to uint32_t, resulting to 0
      
      if((x+2) < dataLength)
         n += data[x+2];

      /* this 24-bit number gets separated into four 6-bit numbers */
      n0 = (uint8_t)(n >> 18) & 63;
      n1 = (uint8_t)(n >> 12) & 63;
      n2 = (uint8_t)(n >> 6) & 63;
      n3 = (uint8_t)n & 63;
            
      /*
       * if we have one byte available, then its encoding is spread
       * out over two characters
       */
      if(resultIndex >= resultSize) return 1;   /* indicate failure: buffer too small */
      result[resultIndex++] = base64chars[n0];
      if(resultIndex >= resultSize) return 1;   /* indicate failure: buffer too small */
      result[resultIndex++] = base64chars[n1];

      /*
       * if we have only two bytes available, then their encoding is
       * spread out over three chars
       */
      if((x+1) < dataLength)
      {
         if(resultIndex >= resultSize) return 1;   /* indicate failure: buffer too small */
         result[resultIndex++] = base64chars[n2];
      }

      /*
       * if we have all three bytes available, then their encoding is spread
       * out over four characters
       */
      if((x+2) < dataLength)
      {
         if(resultIndex >= resultSize) return 1;   /* indicate failure: buffer too small */
         result[resultIndex++] = base64chars[n3];
      }

      progress = x; /////


   }

   /*
    * create and add padding that is required if we did not have a multiple of 3
    * number of characters available
    */
   if (padCount > 0) 
   { 
      for (; padCount < 3; padCount++) 
      { 
         if(resultIndex >= resultSize) return 1;   /* indicate failure: buffer too small */
         result[resultIndex++] = '=';
      } 
   }
   if(resultIndex >= resultSize) return 1;   /* indicate failure: buffer too small */
   result[resultIndex] = 0;
   return 0;   /* indicate success */
}


static const unsigned char d[] = {
    66,66,66,66,66,66,66,66,66,66,64,66,66,66,66,66,66,66,66,66,66,66,66,66,66,
    66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,62,66,66,66,63,52,53,
    54,55,56,57,58,59,60,61,66,66,66,65,66,66,66, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
    10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,66,66,66,66,66,66,26,27,28,
    29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,66,66,
    66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,
    66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,
    66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,
    66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,
    66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,
    66,66,66,66,66,66
};

int base64decode (char *in, size_t inLen, unsigned char *out, size_t outLen)
{ 
    char *end = in + inLen;
    char iter = 0;
    uint32_t buf = 0;
    size_t len = 0;
    size_t decodeCount = 0;
    
    while (in < end) {
	decodeCount++;
	infof("Decoded char count: %li\n", decodeCount);
	progress = decodeCount;

        unsigned char c = d[*in++];
        
        switch (c) {
        case WHITESPACE: continue;   /* skip whitespace */
        case INVALID:    return 1;   /* invalid input, return error */
        case EQUALS:                 /* pad character, end of data */
            in = end;
            continue;
        default:
            buf = buf << 6 | c;
            iter++; // increment the number of iteration
            /* If the buffer is full, split it into bytes */
            if (iter == 4) {
                if ((len += 3) > outLen) return 1; /* buffer overflow */
                *(out++) = (buf >> 16) & 255;
                *(out++) = (buf >> 8) & 255;
                *(out++) = buf & 255;
                buf = 0; iter = 0;

            }   
        }
    }
    if (iter == 3) {
        if ((len += 2) > outLen) return 1; /* buffer overflow */
        *(out++) = (buf >> 10) & 255;
        *(out++) = (buf >> 2) & 255;
    }
    else if (iter == 2) {
        if (++len > outLen) return 1; /* buffer overflow */
        *(out++) = (buf >> 4) & 255;
    }

    outLen = len; /* modify to reflect the actual output size */
    return 0;
}

static void
sigHandler(int sig)
{
    size_t percentage = (progress/(float)(file_size - 1)) * 100;
    infof("Progress: %li% (%li / % li)\n", percentage, progress, file_size);
    sleep(3);
}


int main(int argc, char **argv){

    if (argc < 3){

	infof("Usage: ./base64 --encode/decode <textfile.txt>\n");	
	return 1;

    }

    int j;

    FILE *fIn;
    FILE *fOut;

    fIn = fopen(argv[2], "r");
    

    if(!fIn){
	infof("Error opening the file\n");
    }

    size_t pos = ftell(fIn); 
    fseek(fIn, 0, SEEK_END);   
    file_size = ftell(fIn);
    fseek(fIn, pos, SEEK_SET); 

    char data[file_size + 1]; //
    fread(data, file_size + 1, 1 , fIn);

    char *exitFile = malloc(MAX_SIZE);        



    if (signal(SIGINT, sigHandler) == SIG_ERR){
        errorf("Error handling signals\n");
    }
    if (signal(30, sigHandler) == SIG_ERR){ //SIGINFO
        errorf("Error handling signals\n");
    }

    if(strcmp(argv[1], "--encode") == 0){

	base64encode(data, file_size, exitFile, MAX_SIZE);
	fOut = fopen("encoded.txt", "w");
	int results = fputs(exitFile, fOut);
	if (results == EOF) {
    	    errorf("Failed to write\n");
	}

    } else if(strcmp(argv[1], "--decode") == 0){

	base64decode(data, file_size, exitFile, MAX_SIZE);
	fOut = fopen("decoded.txt", "w");
	int results = fputs(exitFile, fOut);
	if (results == EOF){
	    errorf("Failed to write\n");
	}

    } else {

	infof("Usage: ./base64 --encode/decode <textfile.txt>\n");	
	return 1;

    }

    fclose(fIn);
    //fclose(fOut);

    return 0;
}
