// Fill out your copyright notice in the Description page of Project Settings.


#include "BP_PuzzleSingleKeyDoor.h"

ABP_Obsticle* Cast(AActor* actor)
{
  return Cast<ABP_Obsticle, AActor>(actor);
}

bool ABP_PuzzleSingleKeyDoor::ConstructPuzzle(const UMazePath* puzzlePath, ABP_Maze* maze)
{
  auto root = puzzlePath->GetRoot();
  auto leafs = puzzlePath->GetPathEndings();
  if (leafs.Num() < 3) return false;

  int32 index = FMath::RandRange(0, leafs.Num() - 1);
  while (maze->GetTileType(leafs[index].location) == MazeTileType::PATHTOGOAL && leafs.Num() > 0) {
    leafs.RemoveAt(index);
  	index = (index + 1) % leafs.Num();
  }

  if (leafs.Num() == 0) return false;

  auto door = Cast(maze->SpawnActorAt(doorType, root.location, root.directionToGoal));
  auto key = Cast(maze->SpawnActorAt(keyType, leafs[index].location, leafs[index].directionToGoal));
  key->Enable();
  door->Enable();

  key->onActivate.AddDynamic(door, &ABP_Obsticle::Activate);
	return true;
}
