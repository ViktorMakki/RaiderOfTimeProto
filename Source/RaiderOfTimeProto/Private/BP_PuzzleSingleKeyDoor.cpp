// Fill out your copyright notice in the Description page of Project Settings.


#include "BP_PuzzleSingleKeyDoor.h"

bool ABP_PuzzleSingleKeyDoor::ConstructPuzzle(const UMazePath* mazePath, ABP_Maze* maze)
{
  auto root = mazePath->GetRoot();
  auto leaf = mazePath->GetFarestLeaf();
  auto door = maze->SpawnActorAt(doorType, root.location, root.directionToGoal);
  auto key = maze->SpawnActorAt(keyType, root.location, root.directionToGoal);
  //TODO wire together obsticles
	return true;
}
