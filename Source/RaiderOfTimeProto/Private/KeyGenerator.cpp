// Fill out your copyright notice in the Description page of Project Settings.


#include "KeyGenerator.h"

#include "MazePath.h"
#include "OGate.h"
#include "OKey.h"
#include "SymbolRule.h"
#include "UtilsLibrary.h"
#include "Kismet/GameplayStatics.h"

void AKeyGenerator::Destruct()
{
}

const AOGate* FindPrevGate(const ATileMap* tileMap,
                     const TArray<FPathSegment>& path)
{

  if (path.Num() < 2) return nullptr;
  //first and last index is the startGate and the start
  for (int32 i = 1; i < path.Num() - 1; i++ ) {
    const auto* gate = Cast<AOGate>(Find<AActor>(tileMap->GetConstActorsAt(path[i].location), 
     [](const AActor* actor) {
     	 return Cast<AOGate>(actor) != nullptr;
     }));
    if (gate) return gate;
  }
  return nullptr;
}

void AKeyGenerator::Construct()
{
  if (!tileMap) return;
	if (input.keyTypes.IsEmpty()) return;
  TArray<AActor*> actors;
  UGameplayStatics::GetAllActorsOfClass(GetWorld(), AOGate::StaticClass(),actors);

  for (const auto* actor : actors) {
    const auto* gate = Cast<AOGate>(actor);
    if (!gate) continue;
    const auto start = tileMap->GetFirstTileByTag(static_cast<int32>(MazeTileType::START));
    const auto* path = UMazePath::Create(tileMap, tileMap->GetLocation(gate), start.location)->StepToGoal(1);
    const auto pathEndings = path->GetPathEndings();

    if (pathEndings.IsEmpty()) return;
    const int32 startIndex = FMath::RandRange(0, pathEndings.Num() - 1);
    int32 count = 1;
    auto keyLocationPath = pathEndings[startIndex];
    while (tileMap->GetTileTag(keyLocationPath.location) != static_cast<int32>(MazeTileType::PATH) && count < pathEndings.Num()) {
      keyLocationPath = pathEndings[(startIndex + count) % pathEndings.Num()];
      count++;
    }
    if (count == pathEndings.Num()) continue;
    tileMap->SetTileTag(keyLocationPath.location, static_cast<int32>(MazeTileType::OBSTICLE));

    auto keyPath = UMazePath::Create(tileMap, keyLocationPath.location, start.location)->GetPathToGoal();
    AOKey* key =Cast<AOKey>( tileMap->SpawnActorAt(
        input.keyTypes[FMath::RandRange(0, input.keyTypes.Num() - 1)],
        keyLocationPath.location, keyLocationPath.directionToGoal));
    if (!key) continue;
    key->SetSymbolToActivate(gate->GetSymbol());

    const auto* prevGate = FindPrevGate(tileMap, keyPath);
    if (!prevGate) continue;
    auto* symbol = UUtilsLibrary::GetSymbolRule(GetWorld(), prevGate->GetSymbol());
    if (!symbol) continue;
    symbol->AddObsticle(key);
  }
}
