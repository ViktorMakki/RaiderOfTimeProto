// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelGenerator.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ALevelGenerator::ALevelGenerator()
{
  level = this;
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ALevelGenerator::Construct()
{
  for (int32 i = 0; i < generators.Num(); i++) {
    if (generators[i]) generators[i]->Construct();
  }

  if (OnInitLevel.IsBound()) {
    OnInitLevel.Broadcast();
  }
}

void ALevelGenerator::Destruct()
{
  for (int32 i = generators.Num() - 1; i >= 0; i--) {
    if (generators[i]) generators[i]->Destruct();
	}
}

AActor* ALevelGenerator::level = nullptr;

AActor* ALevelGenerator::GetLevelGenerator() {
  return level;
}
