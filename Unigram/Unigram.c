/* Name: Siddhesh Mahadeshwar
*  Username: sdmahade
*  Program Description: The program will read in a text file from standard input.
*  For each unique word encountered, it will count how many times that word has
*  occurred. A simple maximum likelihood estimate for the unigram probability of
*  a word is to take the number of times you've seen a word divided by the total
*  number of words you've encountered.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

// We assue all words are no more than 63 characters long.
// This requires 64 characters in any array that holds a word since we need 1 for null.
// Instead of sprinkling the magic number 64 everywhere in your code, you should instead
// use the following constant:
#define WORD_ARRAY_SIZE 64

// Function prototypes, this allows the function implementations to appear in any order in the file
// You will be implementing these three functions.
unsigned int hashString(char* str);
double calcUnigramLogProb(unsigned int count, unsigned long total);
void stripUpper(char* str);

// Function prototypes for the test functions we have provided
void testHashString();
void testCalcUnigramLogProb();
void testStripUpper();
void mustBePositive();
void errorMessage();
void nextLine();
void calculationPrint(double calc, char* calc2);
void mainPrint(char* calc1, unsigned int calc2, int calc3, int calc4, int calc5);
void defaultPrint();

// Hash a null-terminated string to an unsigned int.
// Implement as in Java's hashCode for String s, calculates this equation:
//   s[0]*31^(n-1) + s[1]*31^(n-2) + ... + s[n-1]  (^ denotes exponentiation)
//
// You can follow the Java source code in this discussion: http://tinyurl.com/pqg2al5
//
// NOTE: While the above equation uses exponentiation, it is quite expensive and
// unnecessary to call the pow() function for each character. Also you will not get
// the same answer as us for long strings. You can do the calculation using only
// multiplication and addition. HINT: Can you reorder the calculation?
unsigned int hashString(char* str)
{
  int value = 0;

  for (unsigned int i = 0; i < strlen(str); i++)
  {
    value = value*31+str[i];
  }

  return value;
}

// Calculate log probability of a word occurring count times in total words of data.
// Result is in log base 10.
double calcUnigramLogProb(unsigned int count, unsigned long total)
{
  //return log10f((double)count/(double)total);

  double temp1 = (double)count;
  double temp2 = (double)total;
  return log10(temp1) - log10(temp2);
}


// Strip the null-terminated string str of characters that aren't letters or apostrophe.
// Converts all lowercase letters to uppercase.
// This operates in place on the string str.
void stripUpper(char* str)
{

  // initializing variables
  int x, y;
  x = 0;
  y = 0;

  // while loop to check and correct letters if lower case and validate if they are letters
  while (str[x] != 0)
    {
      if(str[x] > 96 && str[x] < 123)
	     {
	  str[x] = str[x] - 32;
	     }

      if((str[x] > 64 && str[x] < 91) || str[x] == 39)
	     {
	  x++;
	     }
      else{
	       y = x;

	        while(str[y] != 0)
	         {
	            str[y] = str[y+1];
	            y++;
	         }
          }
    }
}

// Test function for the hashString function.
// Do NOT change this function.
void testHashString()
{
   char tests[][WORD_ARRAY_SIZE] = {"BAD", "DAB", "GOODFELLOWS", "WRITERSHIP", "a", "A", "abcdefghijklmnopqrstuvwxyz", "1234567890!@#$%^&*()", ""};

   int i = 0;
   while (strlen(tests[i]) > 0)
   {
      printf("\"%s\" -> %u\n", tests[i], hashString(tests[i]));
      i++;
   }
}

// Test function for the calcUnigramLogProb function.
// Do NOT change this function.
void testCalcUnigramLogProb()
{
   const int SIZE = 8;
   unsigned int  counts[] = { 5 ,  50 ,   1,    1,   1234,   0 , 100 , 1};
   unsigned long totals[] = {10 , 100 , 100, 2000, 567890, 123 , 100 , 1};

   for (int i = 0; i < SIZE; i++)
   {
      printf("%5u %7lu -> %9.6f\n", counts[i], totals[i], calcUnigramLogProb(counts[i], totals[i]));
   }
}

// Test function for the stripUpper function.
// Do NOT change this function.
void testStripUpper()
{
   char tests[][WORD_ARRAY_SIZE] = {"bad", "BAD", "BaD", "CAN'T", "well-done", "!L00K-", "1234567890", ""};

   int i = 0;
   while (strlen(tests[i]) > 0)
   {
      printf("\"%s\" -> ", tests[i]);
      stripUpper(tests[i]);
      printf("\"%s\" (len %zu)\n", tests[i], strlen(tests[i]));
      i++;
   }
}


// helper print functions for clarity in main method code and practice
void mustBePositive()
{
  printf("Table size must be positive!\n");
}

void errorMessage()
{
  printf("ERROR: hash table is full!\n\n");
}

void nextLine()
{
  printf("\n");
}

void calculationPrint(double calc, char* calc2)
{
  printf("%9.6f %s\n", calc, calc2);
}


void mainPrint (char* calc1, unsigned int calc2, int calc3, int calc4, int calc5)
{
  printf("%s -> hash %u, bucket %d, stored at %d, count %d\n", calc1, calc2, calc3, calc4, calc5);
}

void defaultPrint()
{
  printf("Usage: Unigram <hash table size> [debug]\n\n");
  testHashString();
  printf("\n");
  testCalcUnigramLogProb();
  printf("\n");
  testStripUpper();
}

int main(int argc, char** argv)
{

  // prints this out if no input is given
  if(argc <= 1)
    {
      defaultPrint();
      return 0;
    }

  // initializing variables
   int bucket = 0;
   int startL = 0;
   int temp1 = 0;
   int tableSize = atoi(argv[1]);

   char hashTable[tableSize][WORD_ARRAY_SIZE];
   // initializing all element holders in 2D array to null terminator / 0
   for (int i = 0; i < tableSize; i++)
     {
       for (int j = 0; j < WORD_ARRAY_SIZE; j++)
	      {
	   hashTable[i][j] = 0;
	      }
     }

     // initializing word array to 0/null terminator
   char word[WORD_ARRAY_SIZE];
   for (int i = 0; i < WORD_ARRAY_SIZE; i++)
      {
         word[i] = 0;
      }

   int frequency[tableSize];
   for (int i = 0; i < tableSize; i++)
     {
       frequency[i] = 0;
     }


   // If no command line input we print out a help message and also run test functions
   if (tableSize < 1)
     {
       mustBePositive();
       return 0;
     }

  int cTotal = 0; // counter

  while(scanf("%63s", word) > 0)
    {
      stripUpper(word);
      if (strlen(word) < 1)
	     {
	        continue;
	     }

      bucket = (hashString(word) % tableSize);
      startL = bucket;

      while ((strcmp(word,hashTable[bucket]) != 0 && (frequency[bucket] > 0)))
	     {
	        bucket++;

	         if (bucket >= tableSize)
	          {
	             bucket = 0;
	          }

	         if (bucket == startL)
	          {
	             errorMessage();
	             return 0;
	          }
	     }

	if(frequency[bucket] == 0)
	  {
	    strcpy(hashTable[bucket], word);
	  }
	frequency[bucket]++;
	cTotal++;


// printing out for verbose
	if (argc > 2 && atoi(argv[2]) != 0)
	  {
	    mainPrint(hashTable[bucket],hashString(hashTable[bucket]), startL, bucket, frequency[bucket]);
	  }
  }

// print out non-verbose values - probabilities
while (temp1 < tableSize)
  {
    if (temp1 >= 0 && hashTable[temp1][0] != 0)
      {
	       calculationPrint(calcUnigramLogProb(frequency[temp1],cTotal), hashTable[temp1]);
	    }
    temp1++;
  }
 nextLine();
 return 0;
}
