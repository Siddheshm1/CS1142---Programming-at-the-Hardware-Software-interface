/* Siddhesh Mahadeshwar
 * username: sdmahade
 * Program Description: This program is a typical application of the Greedy algorithm where the program takes in standard input (text file) from
 * the user and takes in the first 2 inputs as the dimensions of the 2-dimensional array and the remaining data points will be the data points
 * at respective locations in the 2-dimensional array/grid. The program will then run from the left to the right end of the array, trying to
 * find the most cost efficient way of reaching the other side/end of the so-called tunnel.
 */

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

int main (int argc, char** argv)
{

  if (argc < 2) {
  printf("Tunnel <start row> [verbose]\n");
  return 0;
  }

// initializing variables

  int startRow = atoi(argv[1]);
  int rows = 0;
  int columns = 0;
  int dataPoints;
  double totalValues = 0;
  int minDif = 0;
  int maxDif = 0;

// scanning from file for rows and columns
  scanf("%d", &rows);
  scanf("%d", &columns);

  dataPoints = rows * columns;

  int grid [columns][rows];

  if (startRow > rows){
  printf("Invalid starting row!\n");
  return 0;
  }

  int currentX = 0;
  int currentY = 0;
  int maxX = columns;
  int maxY = rows;
  int curLocation = 0;

  // error messages
  if (argc < 1){
    printf("Tunnel <start row> [verbose]");
    return 0;
  }

  if (startRow > rows){
    printf("Invalid starting row!");
    return 0;
  }

// looping to get all values into the array
  while(currentY < maxY)
    {
      while (currentX < maxX) {

	  scanf("%d", &curLocation);
	  grid[currentX][currentY] = curLocation;
	  currentX++;

	  if (maxDif == 0){
	    maxDif = curLocation;
	  }

	  if (minDif == 0){
	    minDif = curLocation;
	  }

	  if (curLocation > maxDif) {
	    maxDif = curLocation;
	  }

	  if (curLocation < minDif) {
	    minDif = curLocation;
	  }

	  totalValues += curLocation;


	}
      currentY++;
      currentX = 0;

    }


  int leftRight = 0; // columns
  int upDown = startRow ; // rows

  int cost = grid[leftRight][upDown];
  grid[leftRight][upDown]= 10;
  char next = 'a';
  int min = 11;

  int length = 0;

// printing out required data info
  printf("Data points: %d\n", dataPoints);
  printf("Avg difficulty: %.3f\n", (totalValues / dataPoints));
  printf("Min difficulty: %d\n", minDif);
  printf("Max difficulty: %d\n\n", maxDif);

// printing out first step only if meeting the requirements
  if (argc > 2 && atoi(argv[2]) != 0) {
  for (int j = 0; j < maxY; j++)
    {
      for (int i = 0; i < maxX; i ++)
	{
	  if (grid[i][j] == 10)
	    {
	      printf(".");
	    } else {
	    printf("%d", grid[i][j]);
	  }
	}
      printf("\n");
    }
  printf("\n");
  }



// loop for verbose command
  while (leftRight  < maxX - 1)
    {


      min = 11;

      // checking if east is 10 or a valid location to travel to
      if ((leftRight +1) < maxX && grid[leftRight + 1][upDown] !=10)
    {
      if (grid[leftRight + 1][upDown] < min)
        {
    min = grid[leftRight +1][upDown];
    next = 'e';
        }
    }


// checking if south is 10 or a valid location to travel to
    if ((upDown + 1) < maxY && grid[leftRight][upDown + 1] !=10)
  {

    if (grid[leftRight][upDown + 1] < min)
      {
  min = grid[leftRight][upDown + 1];
  next = 's';
      }
  }


// checking if north is 10 or a valid location to travel to
    if ((upDown -1) >= 0 && grid[leftRight][upDown - 1]!= 10 )
  	  {

  	    if (grid[leftRight][upDown - 1] < min)
  		    {
  		  min = grid[leftRight][upDown -1];
  		  next = 'n';
  		    }
  	  }


// checking if west is 10 or a valid location to travel to
    if ((leftRight - 1)>= 0 && grid[leftRight -1][upDown] != 10)
	   {

	  if (grid[leftRight -1][upDown] < min)
	    {
	      min = grid[leftRight -1][upDown];
	      next = 'w';
	    }
	   }

    if (min > 9)
    {
      break;
    }

// calculating cost in the loop
      cost = cost + min;


// determining which direction to choose based on previous validation statements
	    if (next == 'n')
	      {
		grid[leftRight][upDown -1] = 10;
		upDown = upDown - 1;
	      } else if ( next == 'e')
	      {
		grid[leftRight+ 1][upDown] = 10;
		leftRight = leftRight +1;
	      } else if ( next == 'w')
	      {
		grid[leftRight -1][upDown] = 10;
		leftRight = leftRight - 1;
	      } else
	      {
		grid[leftRight][upDown +1] = 10;
		upDown = upDown +1;
	      }


// calculating lengths
	    length = length + 1;



	    if (argc > 2 && atoi(argv[2]) != 0){
	    for (int j = 0; j < maxY; j++)
	      {
		for (int i = 0; i < maxX; i++)
		  {
		    if (grid[i][j] == 10) {
		      printf(".");
		    } else {
		    printf("%d", grid[i][j]);
		    }
		  }
		      printf("\n");
	      }
	  printf("\n");
	    }
    } // end of while looping

// prints only if verbose is not demanded, only final step is printed
  if(argc  < 3 || atoi(argv[2]) == 0) {
  for (int j = 0; j < maxY; j++)
    {
      for (int i = 0; i < maxX; i++)
	{
	  if (grid[i][j] == 10)
	    {
	      printf(".");

	    } else {
	    printf("%d", grid[i][j]);

	  }
	}
      printf("\n");
    }

  }

  if(argc  < 3 || atoi(argv[2]) == 0) {
    printf("\n");
  }

  //printf("\n");


// prints length and cost
  printf("Length = %d\n", length + 1);
  printf("Cost = %d\n\n", cost);

}
