// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Activable.h"
#include "MazeTypes.h"
#include "BP_Obstilce.h"
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
	UFUNCTION(BlueprintCallable)
	TArray<ABP_Obstilce*> GetObsticles() const;

	UFUNCTION(BlueprintCallable)
	void AddObsticle(ABP_Obstilce* obsticle);

	template <class... Types>
	static ASymbolRule* Create(const Types&... args);

private:
 TArray<ABP_Obstilce*> obsticles;
 Symbol symbol;

	void Init(Symbol newSymbol);
};

template <class... Types>
ASymbolRule* ASymbolRule::Create(const Types&... args) {
  auto symbolRule = NewObject<ASymbolRule>();
  symbolRule->Init(args...);
  return symbolRule;
}
