// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SymbolRule.h"
#include "TileMap.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

#include "UtilsLibrary.generated.h"

//Finds first value in array
template <class Type>
Type* Find(const TArray<Type*> array, std::function<bool(const Type*)> IsEqual)
{
  for (const auto& item : array) {
    if (IsEqual(item)) return item;
  }
  return nullptr;
}

template <class Type>
Type Find(const TArray<Type> array,
           std::function<bool(const Type&)> IsEqual) {
  for (const auto& item : array) {
    if (IsEqual(item)) return item;
  }
  return Type();
}

template <class Type>
void Shuffle(TArray<Type>& array) {
  const int32 NumShuffles = array.Num() - 1;
  for (int32 i = 0; i < NumShuffles; ++i) {
    int32 SwapIdx = FMath::RandRange(i, NumShuffles);
    array.Swap(i, SwapIdx);
  }
}

/**
 * 
 */
UCLASS()
class RAIDEROFTIMEPROTO_API UUtilsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
  UFUNCTION(BlueprintCallable)
	static Direction4 GetRandomDirection();

  UFUNCTION(BlueprintCallable)
  static TArray<Direction4> GetAvailableDirectionsInMaze(const FIntPoint& point,
                                                         const ATileMap* maze);

	UFUNCTION(BlueprintCallable)
	static Direction4 GetRandomPathDirection(const ATileMap* tileMap, const FIntPoint& location);

	UFUNCTION(BlueprintCallable)
  static UClass* GetRandomType(const TArray<UClass*> types);

	UFUNCTION(BlueprintCallable)
  static ASymbolRule* GetSymbolRule(const UWorld* world, const FSymbol symbol);
};
