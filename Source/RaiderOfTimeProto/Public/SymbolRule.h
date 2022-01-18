// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Activable.h"
#include "MazeTypes.h"
#include "Obstilce.h"
#include "UObject/NoExportTypes.h"
#include "SymbolRule.generated.h"

/**
 * 
 */
UCLASS()
class RAIDEROFTIMEPROTO_API ASymbolRule : public AActivable
{
	GENERATED_BODY()
public:
	//UFUNCTION(BlueprintCallable)
	//TArray<AObstilce*> GetObsticles() const;

	UFUNCTION(BlueprintCallable)
	FSymbol GetSymbol() const;

	UFUNCTION(BlueprintCallable)
	void AddObsticle(AObstilce* obsticle);

	UFUNCTION(BlueprintCallable)
	void Clear();

	template <class... Types>
	static ASymbolRule* Create(UWorld* world, const Types&... args);

private:
 //TArray<AObstilce*> obsticles;
 FSymbol symbol;

	void Init(FSymbol newSymbol);
};

template <class... Types>
ASymbolRule* ASymbolRule::Create(UWorld* world, const Types&... args) {
  auto symbolRule = Cast<ASymbolRule>(world->SpawnActor(ASymbolRule::StaticClass()));
  if (!symbolRule) return nullptr;
	symbolRule->Init(args...);
  return symbolRule;
}
