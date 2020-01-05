#include "Map.h"
#include "Tile.h"
#include "Avatar.h"
#include "Action.h"
#include <stdlib.h>
#include <stdio.h>

/*
* Username: sdmahade
* Name: Siddhesh Mahadeshwar
* File Description: This file is responisble for all the functions related to the map such as initializing the map, uninitializing 
* 		    if necessary, displaying it, processing movement, and finding out how many gems are still available on the map. 
*/

// This function initializes the map and returns true if successful, false, if not. 
bool mapInit(Map* map, const char* filename)
{
	FILE* fp = fopen(filename, "r");
	if (fp == NULL)
	{
		return false;
	}

	fscanf(fp,"%d %d", &map->rows, &map->cols);
	fscanf(fp,"%d %d", &map->avatarRow, &map->avatarCol);

	map->tiles = (Tile**)malloc(sizeof(Tile*) * map->rows);
	for (int i = 0; i < map->rows; i++)
	{
		map->tiles[i] = (Tile*)malloc(sizeof(Tile) * map->cols);
	}	

	char ch[2];
	
	for (int j = 0; j < map->rows; j++)
	{
		for (int k = 0; k< map->cols; k++)
		{
			fscanf(fp,"%s", ch);
			map->tiles[j][k] = tileFromChar(ch[0]);
		}
	}

	fclose(fp);
return true;
}

// Responsible for uninitializing the map if called
void mapUninit(Map* map)
{
	for (int i = map->rows -1; i >= 0; i--)
	{
		free(map->tiles[i]);
	}
	free(map->tiles);

}

// Displays the entire map when called
void mapDisplay(const Map* map)
{
	for (int j = 0; j < map->rows; j++)
	{
		for (int k = 0; k < map->cols; k++)
		{
			if (j == map->avatarRow && k == map->avatarCol)
			{
			printf("@");
			} else {
			tileDisplay(map->tiles[j][k]);
			}
		}
	printf("\n");
	}	
}

// Responsible for handling the avatar's movement on the map including all movements and checking which tiles are being encountered
bool mapMoveAvatar(Map* map, Avatar* avatar, Action action)
{
	
	if (action == ActionNorth)
	{

		if (map->avatarRow-1 < 0)
		{
			return false;
		}

		if (tilePassable(map->tiles[(map->avatarRow)-1][map->avatarCol]) == false && map->tiles[(map->avatarRow)-1][map->avatarCol] == TileWall)
		{
			
			return false;
		}
		
		if (map->tiles[map->avatarRow-1][map->avatarCol] == TileGem)
		{
			avatarAddGem(avatar);
			map->tiles[map->avatarRow-1][map->avatarCol] = TileEmpty;
		}	

		if (map->tiles[map->avatarRow-1][map->avatarCol] == TileKey)
		{
			avatarAddKey(avatar);
			map->tiles[map->avatarRow-1][map->avatarCol] = TileEmpty;
		}

		if (map->tiles[map->avatarRow-1][map->avatarCol] == TileEmpty)
		{
			map->avatarRow--;
			return true;
		}

		if (map->tiles[map->avatarRow-1][map->avatarCol] == TileWall)
		{
			map->tiles[map->avatarRow-1][map->avatarCol] = TileSecretPassage;
			map->avatarRow--;
			return true;
		}

		if (map->tiles[map->avatarRow-1][map->avatarCol] == TileLockedDoor && avatar->keys > 0)
		{
			map->tiles[map->avatarRow-1][map->avatarCol] = TileDoor;
			avatar->keys--;	
		}	
		map->avatarRow--;
	}

	if (action == ActionEast)
	{

		if (map->avatarCol+1 > map->cols -1)
		{
			return false;
		}

		if (tilePassable(map->tiles[(map->avatarRow)][map->avatarCol+1]) == false && map->tiles[(map->avatarRow)][map->avatarCol+1] == TileWall)
		{
			
			return false;
		}
		
		if (map->tiles[map->avatarRow][map->avatarCol+1] == TileGem)
		{
			map->tiles[map->avatarRow][map->avatarCol+1] = TileEmpty;
			avatarAddGem(avatar);
		}	

		if (map->tiles[map->avatarRow][map->avatarCol+1] == TileKey)
		{
			map->tiles[map->avatarRow][map->avatarCol+1] = TileEmpty;
			avatarAddKey(avatar);
		}

		if (map->tiles[map->avatarRow][map->avatarCol+1] == TileEmpty)
		{
			map->avatarCol++;
			return true;
		}

		if (map->tiles[map->avatarRow][map->avatarCol+1] == TileWall)
		{
			map->tiles[map->avatarRow][map->avatarCol+1] = TileSecretPassage;
			map->avatarCol++;
			return true;
		}

		if (map->tiles[map->avatarRow][map->avatarCol+1] == TileLockedDoor && avatar->keys > 0)
		{
			map->tiles[map->avatarRow][map->avatarCol+1] = TileDoor;
			avatar->keys--;	
		}	
		map->avatarCol++;
	}

	if (action == ActionWest)
	{

		if (map->avatarCol-1 < 0)
		{
			return false;
		}

		if (tilePassable(map->tiles[(map->avatarRow)][map->avatarCol-1]) == false && map->tiles[(map->avatarRow)][map->avatarCol-1] == TileWall)
		{
			
			return false;
		}
		
		if (map->tiles[map->avatarRow][map->avatarCol-1] == TileGem)
		{
			map->tiles[map->avatarRow][map->avatarCol-1] = TileEmpty;
			avatarAddGem(avatar);
		}	

		if (map->tiles[map->avatarRow][map->avatarCol-1] == TileKey)
		{
			map->tiles[map->avatarRow][map->avatarCol-1] = TileEmpty;
			avatarAddKey(avatar);
		}

		if (map->tiles[map->avatarRow][map->avatarCol-1] == TileEmpty)
		{
			map->avatarCol--;
			return true;
		}

		if (map->tiles[map->avatarRow][map->avatarCol-1] == TileWall)
		{
			map->tiles[map->avatarRow][map->avatarCol-1] = TileSecretPassage;
			map->avatarCol--;
			return true;
		}

		if (map->tiles[map->avatarRow][map->avatarCol-1] == TileLockedDoor && avatar->keys > 0)
		{
			map->tiles[map->avatarRow][map->avatarCol-1] = TileDoor;
			avatar->keys--;	
		}	
		map->avatarCol--;
	}

	if (action == ActionSouth)
	{

		
		
		
		if (map->avatarRow+1 > map->rows-1)
		{
			return false;
		}

		if (tilePassable(map->tiles[(map->avatarRow)+1][map->avatarCol]) == false && map->tiles[(map->avatarRow)+1][map->avatarCol] == TileWall)
		{
			
			return false;
		}
		
		if (map->tiles[map->avatarRow+1][map->avatarCol] == TileGem)
		{
			map->tiles[map->avatarRow+1][map->avatarCol] = TileEmpty;
			avatarAddGem(avatar);
		}	

		if (map->tiles[map->avatarRow+1][map->avatarCol] == TileKey)
		{
			map->tiles[map->avatarRow+1][map->avatarCol] = TileEmpty;
			avatarAddKey(avatar);
		}

		if (map->tiles[map->avatarRow+1][map->avatarCol] == TileEmpty)
		{
			map->avatarRow++;
			return true;
		}

		if (map->tiles[map->avatarRow+1][map->avatarCol] == TileWall)
		{
			map->tiles[map->avatarRow+1][map->avatarCol] = TileSecretPassage;
			map->avatarRow++;
			return true;
		}

		if (map->tiles[map->avatarRow+1][map->avatarCol] == TileLockedDoor && avatar->keys > 0)
		{
			map->tiles[map->avatarRow+1][map->avatarCol] = TileDoor;
			avatar->keys--;	
		}	


		map->avatarRow++;
	}

	if (action == ActionQuit)
		{
			return false;
		}

	if (action == ActionInvalid)
		{
			return false;
		}

return true;	
}

// Responisble for returning how many gems are left on the map which must be reached before finishing the game or moving to the next level
int mapGemsRemaining(const Map* map)
{
	int countGems = 0;
	for (int j = 0; j < map->rows; j++)
	{
		for (int k = 0; k < map->cols; k++)
		{
			if(map->tiles[j][k] == TileGem)
			{
				countGems++;
			}
		}
	}
return countGems;
}


