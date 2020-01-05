#include "Action.h"
#include <stdlib.h>
#include <stdio.h>

/*
* Username: sdmahade
* Name: Siddhesh Mahadeshwar
* File Description: This action file is responsible for returning a valid response to 
* 					a command that will be given by the user.
*/

// Converts the action taken as a parameter from the user and converts it into an action type 
Action actionFromChar(char ch)
{
	switch (ch)
	{
		default: return ActionInvalid;
		break;
		case 'w': return ActionNorth;
		break;
		case 's': return ActionSouth;
		break;
		case 'a': return ActionWest;
		break;
		case 'd': return ActionEast;
		break;
		case 'q': return ActionQuit;
		break;
	}

}
