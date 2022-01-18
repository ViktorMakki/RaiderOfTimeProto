// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeLevelGenerator.h"

#include "OGate.h"
#include "OTrap.h"

void AMazeLevelGenerator::Construct() {
  Destruct();
  tileMap =
      Cast<ATileMap>(GetWorld()->SpawnActor(ATileMap::StaticClass()));
  if (!tileMap) return;
  tileMap->SetSize(mazeSize);
  tileMap->tileSize = tileSize;

  mazeTileGenerator = Cast<AMazeTileTagGenerator>(
      GetWorld()->SpawnActor(AMazeTileTagGenerator::StaticClass()));
  if (!mazeTileGenerator) return;
  mazeTileGenerator->tileMap = tileMap;
  mazeTileGenerator->input = mazeSettings;

  mazeActorGenerator = Cast<AMazeGenerator>(
      GetWorld()->SpawnActor(AMazeGenerator::StaticClass()));
  if (!mazeActorGenerator) return;
  mazeActorGenerator->tileMap = tileMap;
  mazeActorGenerator->input = mazeActorSettings;

  gateSymbolGenerator = Cast<ASymbolGenerator>(
      GetWorld()->SpawnActor(ASymbolGenerator::StaticClass()));
  if (!gateSymbolGenerator) return;
  gateSymbolGenerator->obsticleType = AOGate::StaticClass();
  gateSymbolGenerator->symbolTypes = symbols;

  keyGenerator =
      Cast<AKeyGenerator>(GetWorld()->SpawnActor(AKeyGenerator::StaticClass()));
  if (!keyGenerator) return;
  keyGenerator->tileMap = tileMap;
  keyGenerator->input = keyActorSettings;

  trapGenerator = Cast<ATrapGenerator>(
      GetWorld()->SpawnActor(ATrapGenerator::StaticClass()));
  if (!trapGenerator) return;
  trapGenerator->tileMap = tileMap;
  trapGenerator->trapTypes = traps;

	trapSymbolGenerator = Cast<ASymbolGenerator>(
      GetWorld()->SpawnActor(ASymbolGenerator::StaticClass()));
  if (!trapSymbolGenerator) return;
	trapSymbolGenerator->obsticleType = AOTrap::StaticClass();
  trapSymbolGenerator->symbolTypes = symbols;

  level = Cast<ALevelGenerator>(
      GetWorld()->SpawnActor(ALevelGenerator::StaticClass()));
  if (!level) return;
  level->generators = {mazeTileGenerator,   mazeActorGenerator,
                       gateSymbolGenerator, keyGenerator,
                       trapGenerator,       trapSymbolGenerator};
  level->Construct();
}

void AMazeLevelGenerator::Destruct() {
  if (level) {
   level->Destruct();
   level->Destroy();
   level = nullptr;
  }
  if (trapSymbolGenerator) {
    trapSymbolGenerator->Destroy();
    trapSymbolGenerator = nullptr;
  }
  if (trapGenerator) {
    trapGenerator->Destroy();
    trapGenerator = nullptr;
  }
  if (keyGenerator) {
    keyGenerator->Destroy();
    keyGenerator = nullptr;
  }
  if (gateSymbolGenerator) {
    gateSymbolGenerator->Destroy();
    gateSymbolGenerator = nullptr;
  }
  if (mazeActorGenerator) {
	  mazeActorGenerator->Destroy();
    mazeActorGenerator = nullptr; 
  }
  if (mazeTileGenerator) {
    mazeTileGenerator->Destroy();
    mazeTileGenerator = nullptr;
  }
  if (tileMap) {
	  tileMap->Destroy();
    tileMap = nullptr;
  }
}

void AMazeLevelGenerator::BeginPlay()
{
	Super::BeginPlay();
  Construct();
}
