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

int32 FindNextGateIndex(const ATileMap* tileMap,
                        const TArray<FPathSegment>& path,
                        int32 startIndex)
{
  //first and last index is the startGate and the start
  for (int32 i = startIndex + 1; i < path.Num(); i++) {
    if (tileMap->GetTileTag(path[i].location) == static_cast<int32>(MazeTileType::GATE)) return i;
  }
  return -1;
}

FSymbol GetGateSymbol(const ATileMap* tileMap, const FIntPoint& location)
{
	auto actors = tileMap->GetConstActorsAt(location);
	for (const auto actor : actors) {
		auto gate = Cast<AOGate>(actor);
    if (gate) {
    	return gate->GetSymbol();
    }
	}
  return {};
}

TArray<FSymbol> ConstructRequiredKeys(ATileMap* tileMap, const FKeyGeneratorInput& input)
{
  const auto start =
      tileMap->GetFirstTileByTag(static_cast<int32>(MazeTileType::START));
  const auto goal =
      tileMap->GetFirstTileByTag(static_cast<int32>(MazeTileType::GOALGATE));
  const auto path = UMazePath::Create(tileMap, start.location, goal.location,
                                      SearchAlgorithm::DFS)
                        ->GetPathToGoal();
  if (path.Num() < 3) return {};

  int32 lastGateIndex = 0;
  int32 gateIndex = FindNextGateIndex(tileMap, path, 0);
  TArray<FSymbol> foundSymbols;

  while (gateIndex > 0 && gateIndex < path.Num()) {
    const FSymbol activableGateSymbol =
        GetGateSymbol(tileMap, path[gateIndex].location);
    if (!foundSymbols.Contains(activableGateSymbol)) {
      if (gateIndex - lastGateIndex < 2) continue;
      const auto keyLocation = path[FMath::RandRange(lastGateIndex, gateIndex)];
      AOKey* key = Cast<AOKey>(tileMap->SpawnActorAt(
          input.keyTypes[FMath::RandRange(0, input.keyTypes.Num() - 1)],
          keyLocation.location, keyLocation.directionToGoal));
      if (!key) continue;
      key->SetSymbolToActivate(activableGateSymbol);
      tileMap->SetTileTag(keyLocation.location,
                          static_cast<int32>(MazeTileType::OBSTICLE));
      if (!foundSymbols.IsEmpty()) {
        ASymbolRule* symbolActor = UUtilsLibrary::GetSymbolRule(
            tileMap->GetWorld(),
            foundSymbols[FMath::RandRange(0, foundSymbols.Num() - 1)]);
        if (!symbolActor) continue;
        symbolActor->AddObsticle(key);
      }
      foundSymbols.Add(activableGateSymbol);
    }
    lastGateIndex = gateIndex;
    gateIndex = FindNextGateIndex(tileMap, path, gateIndex);
  }

  return foundSymbols;
}

TArray<FSymbol> GetAllSymbols(UWorld* world) {
  TArray<AActor*> actors;
  UGameplayStatics::GetAllActorsOfClass(world, ASymbolRule::StaticClass(),
                                        actors);
  TArray<FSymbol> result;
  for (const auto actor : actors) {
    const auto symbol = Cast<ASymbolRule>(actor);
    if (!symbol) continue;
  	result.Add(symbol->GetSymbol());
  }
  return result;
}

TArray<FSymbol> GetNotFoundSymbols(UWorld* world, const TArray<FSymbol>& foundSymbols) {

  TArray<FSymbol> result;
  for (const auto symbol : GetAllSymbols(world)) {
    if (!foundSymbols.Contains(symbol))
      result.Add(symbol);
  }
  return result;
}

void SpawnRandomKey(ATileMap* tileMap, const TArray<UClass*>& keyTypes,
                    const FSymbol& toActivate, const FSymbol& enable) {
  const auto size = tileMap->Size();
  if (size.X == 0 || size.Y == 0) return;
  auto location = FIntPoint{FMath::RandRange(0, size.X - 1),
                            FMath::RandRange(0, size.Y - 1)};
  while (tileMap->GetTileTag(location) !=
         static_cast<int32>(MazeTileType::PATH)) {
    location = FIntPoint{FMath::RandRange(0, size.X - 1),
                         FMath::RandRange(0, size.Y - 1)};
  }
  AOKey* key = Cast<AOKey>(tileMap->SpawnActorAt(
      keyTypes[FMath::RandRange(0, keyTypes.Num() - 1)], location,
      UUtilsLibrary::GetRandomPathDirection(tileMap, location)));
  if (!key) return;
  key->SetSymbolToActivate(toActivate);
  tileMap->SetTileTag(location,
                      static_cast<int32>(MazeTileType::OBSTICLE));
  ASymbolRule* symbolActor =
      UUtilsLibrary::GetSymbolRule(tileMap->GetWorld(), enable);
  if (!symbolActor) return;
  symbolActor->AddObsticle(key);
}

//Creates keys for each symbol in toActivate
void SpawnRandomKeys(ATileMap* tileMap, const TArray<UClass*>& keyTypes, 
                     const TArray<FSymbol>& toActivate, const TArray<FSymbol>& enables)
{
  if (toActivate.IsEmpty() || enables.IsEmpty()) return;
  for (const FSymbol& toActivateSymbol : toActivate) {
    FSymbol enableSymbol;
    const int32 enableIndex = FMath::RandRange(0, enables.Num() - 1);
    for (int32 i = 0; i < enables.Num() || toActivateSymbol == enableSymbol; i++) {
      enableSymbol = enables[(enableIndex + i) % enables.Num()];
    }
    if (toActivateSymbol == enableSymbol) continue;
    SpawnRandomKey(tileMap, keyTypes, toActivateSymbol, enableSymbol);
  }
}

void AKeyGenerator::Construct()
{
  if (!tileMap) return;
	if (input.keyTypes.IsEmpty()) return;

  const auto foundSymbols = ConstructRequiredKeys(tileMap, input);
  const auto notFoundSymbols = GetNotFoundSymbols(GetWorld(), foundSymbols);
  auto allSymbols = GetAllSymbols(GetWorld());
  if (!notFoundSymbols.IsEmpty()) {
   SpawnRandomKeys(tileMap, input.keyTypes, notFoundSymbols, allSymbols);
  }
  int32 leftToSpawn = input.keyCount - allSymbols.Num();
  if (leftToSpawn < 1) return;
  Shuffle(allSymbols);
  const auto leftSymbols = Range(allSymbols, 0, leftToSpawn - 1);
  SpawnRandomKeys(tileMap, input.keyTypes, leftSymbols, allSymbols);
}
