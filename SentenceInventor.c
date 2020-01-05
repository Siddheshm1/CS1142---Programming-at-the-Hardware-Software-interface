// Siddhesh Mahadeshwar
// Username: sdmahade
// This program takes in certain parameters as specified in the source code and prints out as many randomly generated sentences as asked for by the user.

#include <stdio.h>
#include <stdlib.h>

int main (int argc, char** argv)
{
  // checks if enough inputs have been provided
  if (argc < 5)
    {
      printf("SentenceInventor <number> <probability> <seed> <word1> [word2] ...\n");
      return 0;
    }

  // initializes variables
  int nOfSentences = atoi(argv[1]);
  double probOfAnother = atof(argv[2]);
  int seed = atoi(argv[3]);
  int nOfWords = argc - 4;
  int counter [nOfSentences];
  double total = 0;
  

  // first for loop to set all array values to 0
  for (int i = 0; i < nOfSentences;i++)
    {
      counter[i] = 0;
    }
  
  srand(seed);

  // main loop which randomizes and prints sentences
  for (int i = 0; i < nOfSentences; i++)
    {
      int wordIndex = rand()% nOfWords; // randomizes
      printf("%s",argv[wordIndex +  4]);
      counter[i] = counter[i] +1; // increments counter for number of words in a sentence

      // adds subsquent words to the sentence
      while( (((double)rand())/RAND_MAX )< probOfAnother  )
	{
	  int  randIndex = rand()% nOfWords;
	  printf(" %s",argv[randIndex + 4]);
	  counter [i] = counter[i] + 1;
	}    
	     printf(".\n");
    }     
	    

   for (int i = 0; i < nOfSentences; i++)
     {
       total = total + counter[i];  
     }
    
   // produces the average
   double average = total/(double)nOfSentences;
   // print statements
  printf("Total Sentences = %d \n", nOfSentences);
  printf("Average words per sentence = %.2f\n\n",average);
}
