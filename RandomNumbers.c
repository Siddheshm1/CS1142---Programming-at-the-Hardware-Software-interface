// Siddhesh Mahadeshwar
// username: sdmahade
// This program prints out random numbers in binary bits and base 10 bits based on the input parameters provided by the user

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

// checks if sufficient inputs are provided
int main(int argc, char** argv){
  // part 1: check if the input is valid
  if(argc < 5){
    printf("RandomNumbers <bits> <seed> <tap bit> <numbers>\n");
    return 0;
  }
  //Initialize Values
  int bits  =  atoi(argv[1]);
  int seed  =  atoi(argv[2]);
  int tapBit  =  atoi(argv[3]);
  int numbers =  atoi(argv[4]);

  long maxBitSize = pow(2, bits) - 1; // finds maximum value from unsigned bits

  // makes sure all inputs are valid
  if( bits < 0 || bits > 31 || seed < 0 || seed > maxBitSize || tapBit < 0 || tapBit >= bits ){
    printf("Invalid input!\n");
    return 0;
  }
 
 
  // Part 2 

  bool binaryBits[bits]; // initializes boolean array
  int remainder = seed;
  long div = (maxBitSize+1)/2;
  int j = bits-1;

  for(int i = 0; i < bits; i++){
    binaryBits[i] = true;               // sets ith element to true   
  }
 
  while (div > 0){
    if (div <= remainder){
      binaryBits[j] = true;             // sets ith element to true
 
      remainder -= div;                 // remainder = remainder - divisor
    }
    else{
      binaryBits[j]=false;              // sets jth element to false
 
    }
    div = div/2;
    j--;                                // decrements j
  }

  for(int i = bits-1; i >= 0; i--){
    printf("%d", binaryBits[i]);
  }

  printf("%s%d\n", " = ", seed); // print statement


  // part 3

  // initializes variables
  int MSB  =  0;
  int tempA  =  0;
  int tempNum  =  0;


  // main while loop for bit shifting  
  while(numbers-1 > 0){
    MSB = binaryBits[bits-1];       
    tempNum = 0;                    
    tempA = MSB ^ binaryBits[tapBit];

   
    for (int k = bits -1; k> 0; k--){
      binaryBits[k] = binaryBits[k - 1]; 
    }

    binaryBits[0] = tempA;               
    
    for (int l = bits -1; l >= 0; l--){
      printf("%d", binaryBits[l]);   
    }
    
    
    for (int y = bits -1; y >= 0; y--){
      if (binaryBits[y]){
	tempNum += pow(2, y);        
      }
    }


    // print statement for formatting
    printf("%s%d\n", " = ", tempNum);         
    numbers--;
  }

}
