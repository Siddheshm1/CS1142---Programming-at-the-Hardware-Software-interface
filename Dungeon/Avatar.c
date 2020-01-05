#include "Avatar.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
* Username: sdmahade
* Name: Siddhesh Mahadeshwar
* File Description: This file is responsible for all the actions related to managing the
* 					avatar of the user. It has functions such as creating and initializing
*					the avatar and displaying it.
*/

// Initializes all required data for the avatar
void avatarInit(Avatar* avatar, const char* name)
{
	avatar->name = (char*) malloc(((int)strlen(name) + 1) * sizeof(char));
	strcpy(avatar->name, name);
	avatar->keys = 0;
	avatar->gems = 0;
}

// Uninitializes all the data for the avatar, frees all mallocs
void avatarUninit(Avatar* avatar)
{
	free(avatar->name);
}

// Handles if the avatar encounters a key, increments key count, and returns a boolean
bool avatarUseKey(Avatar* avatar)
{
	if (avatar->keys > 0)
		{
			avatar->keys--;
			return true;
		}
	
	return false;
}

// Handles if the avatar encounters a key and increments key count
void avatarAddKey(Avatar* avatar)
{
	avatar->keys++;

}

// Handles if the avatar encounters a gem and increments gem count
void avatarAddGem(Avatar* avatar)
{
	avatar->gems++;

}

// Displays the avatar's statistics when called
void avatarDisplay(const Avatar* avatar)
{
	printf("%s's inventory: gems %d, keys %d\n", avatar->name, avatar->gems, avatar->keys);

}
