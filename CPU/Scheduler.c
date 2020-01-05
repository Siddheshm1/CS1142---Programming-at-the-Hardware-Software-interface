#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

/* Name:                Siddhesh Mahadeshwar
 * Username:            sdmahade
 * Program Description: The objective of this program is to serve as a simulation of how the CPU would function in terms of
 *                      taking and handling jobs as it is given by the user. It will take standard file input and execute
 *                      the jobs by giving each job in the list equal time until each runs out. If only 1 job is left, it
 *                      will run the job solely until it has been finished. Once done, the program will output statistics
 *                      about the run such as CPU efficiency, running time, idle time, and other such data.
 */


// Stores information about a particular job on the system
// Do NOT modify!
typedef struct
{
    int id;                 // Unique numeric ID for this job
    int startTime;          // Time the job entered the system
    int totalCycles;        // Total CPU cycles required by this job
    int remainingCycles;    // How many cycles remaining before it is done
} Job;

// Node in the doubly linked list
// Do NOT modify!
typedef struct node
{
    Job job;                // Data about this particular job
    struct node* next;      // Pointer to the next node in the doubly linked list
    struct node* prev;      // Pointer to the prev node in the doubly linked list
} Node;

// Tracks information about the state of the CPU scheduler
// Do NOT modify!
typedef struct
{
    Node* head;             // Current head of the linked list
    int time;               // Current time of the simulation
} State;

// Executes one cycle of the CPU scheduling simulation.
// The current job at the head of the linked list gets one cycle of CPU time. ++
//
// If the current job is done, it should be removed from the list and the function prints: ++
//   t=A, B done, elapsed C, idle D%\n
//   where A is the current time of the simulation
//         B is the job ID of the completed job
//         C is how many cycles have elapsed since the job was first added (including this cycle)
//         D is the percentage of cycles in which this job was idle (some other job was executing)
//
// The head of the list should be advanced to the next node. ++
// The current time of the simulation should be advanced by one. ++
//
// Returns true if a job used the cycle, false if there were no available jobs.
bool executeCycle(State* state)
{
  // state->time++; // increments program time by 1

  if (state->head == NULL)
    {
	     state->time++;
	     return false;
    }

  if (state->head->job.remainingCycles != 0) // if the current job still needs time, decrement remainingCycles by 1
    {
      state->head->job.remainingCycles--;
    }

  if (state->head->job.remainingCycles == 0) // if the current job needs no time, remove that node from the list
    {
      struct node *temp1 = state->head;
      state->head->prev->next = state->head->next; // set current's prev's next to current's next
      state->head->next->prev = state->head->prev; // set current's next's prev to current's prev

      int elapsed = (state->time + 1) - state->head->job.startTime;
      double temp = ((double)state->head->job.totalCycles /(double) ((state->time + 1) - state->head->job.startTime)) * 100;
      double idle = 100 - temp;

      printf("t=%d, %d done, elapsed %d, idle %.2f%%\n", state->time, state->head->job.id, elapsed, idle);
      state->head = state->head->next; // set the head to the next node

      if(state->head != NULL)
        {

        if(state->head->job.remainingCycles == 0 &&  state->head->prev == state->head->next )
	         {
	           state->head = NULL;
	         }
        }
        free(temp1);
        temp1 = NULL;
      } else {
        state->head = state->head->next; // set the head to the next node
      }

  state->time++;
  return true;
}

// Adds a new job to the linked list.
// The job is added as the node before the current head of the list.
// Thus the new job has to wait until all existing jobs get scheduled.
//
// Returns true on succss, false otherwise (e.g. failure to allocate memory).
bool addJob(State* state, int jobID, int jobTime)
{
  struct node* newListNode = malloc(sizeof(struct node)); // allocating space for a new node --------------------------------
  if (newListNode == NULL) // if new node could not be made, return false
      {
        return false;
      }
  if (state->head == NULL) // conditioning to check if there is no node in the list
  {
    state->head = newListNode;
    newListNode->prev = newListNode;
    newListNode->next = newListNode;

  } else { // condition that executes if exception is not the case
    state->head->prev->next = newListNode;
    newListNode->prev = state->head->prev;
    newListNode->next = state->head;
    state->head->prev = newListNode;
  }
  newListNode->job.id = jobID; // setting ID of the new node
  newListNode->job.totalCycles = jobTime; // setting the total number of cycles for the new node
  newListNode->job.remainingCycles = jobTime; // setting remaining number of cycles for the new node
  newListNode->job.startTime = state->time;
  printf("t=%d, added %d\n", state->time, newListNode->job.id);
  return true;

}

// Prints out the jobs currently in the linked list in order of next execution.
// Output format is:
//   t=A, print B:C D:E ...
//   where A is the current time of the simulation
//         B is the ID of the job at the head of the list
//         C is the remaining cycles for the job at the head of the list
//         D is the ID of the next job to be scheduled
//         E is the remaining cycles of the next job to be schedule
//         ... and so on for all jobs in the list
void printJobs(const State* state)
{
  struct node* tempNode = state->head; // makes a temp node that saves the original state->head
  printf("t=%d, print ", state->time);
  if(state->head == NULL)
  {
    printf("\n");
    return;
  }

  int firstID = state->head->job.id; // store original state's ID for later reference

  do
    {
      printf("%d:%d ", tempNode->job.id, tempNode->job.remainingCycles);
      tempNode = tempNode->next;
    } while (firstID != tempNode->job.id);
  printf("\n");

}

// Remove all remaining jobs from the linked list, deallocating the associated memory.
// Also results in the head of the list being changed to NULL.
//
// Returns the number of removed jobs (0 if list is empty).
int freeJobs(State* state)
{
  int count = 0; // counter for number of freed jobs

  if (state->head == NULL)
  {
    return count;
  }

  int firstID = state->head->prev->job.id;

  struct node* temp2 = state->head;

  if (temp2->next == temp2)
    {
      count++;
      free(temp2);
      return count;

    }
  do // do while loop to free jobs when called on non-exception cases
      {

      struct node* temp3 = temp2;
      temp2 = temp2->next;
      free(temp3);
      count++;
      } while (firstID != temp2->job.id);
  free(temp2);
  count++;

  state->head = NULL; // sets head to null after all jobs have been freed

  return count; // returns the number of freed jobs

}

// Main program that simulates scheduling jobs on a CPU.
// Input is via standard input.
// Input consists of a string command followed by 0 or more integer arguments depending on the command.
// Do NOT modify the main function!
int main(void)
{
    // State struct keeps track of the head of the linked list and the current time of the simulation
    State state;
    state.head = NULL;
    state.time = 0;

    // String literals that are used in the input
    const char* COMMAND_RUN = "run";
    const char* COMMAND_ADD = "add";
    const char* COMMAND_PRINT = "print";

    // Variables used to read in data depending ont he command
    char command[100];
    int cycles = 0;
    int id = 0;
    int jobTime = 0;

    // Used to keep track of how often the CPU was busy or idle
    int busyCycles = 0;
    int idleCycles = 0;

    while (scanf("%99s", command) == 1)
    {
        if (strcmp(command, COMMAND_RUN) == 0)
        {
            // After the run command should come a positive number of cycles to execute
            if ((scanf("%d", &cycles) == 1) && (cycles > 0))
            {
                for (int i = 0; i < cycles; i++)
                {
                    if (executeCycle(&state))
                    {
                        busyCycles++;
                    }
                    else
                    {
                        idleCycles++;
                    }
                }
            }
            else
            {
                printf("Invalid run command\n");
                return 1;
            }
        }
        else if (strcmp(command, COMMAND_ADD) == 0)
        {
            // After the add command should come the process ID and a positive job time
            if ((scanf("%d %d", &id, &jobTime) == 2) && (jobTime > 0))
            {
                if (!addJob(&state, id, jobTime))
                {
                    printf("Failed to add job\n");
                    return 1;
                }
            }
            else
            {
                printf("Invalid add command\n");
                return 1;
            }
        }
        else if (strcmp(command, COMMAND_PRINT) == 0)
        {
            printJobs(&state);
        }
        else
        {
            printf("Unknown command = %s\n", command);
            return 1;
        }
    }

    // Compute how many cycles the CPU was busy
    double utilization = (double) busyCycles / (idleCycles + busyCycles) * 100.0;
    printf("t=%d, end, CPU busy %.2f%%\n", state.time, utilization);

    // Deallocate any remaining jobs in the system
    printf("t=%d, freed %d remaining jobs\n", state.time, freeJobs(&state));

    return 0;
}
