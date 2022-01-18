// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Obstilce.h"
#include "SymbolRule.h"
#include "OKey.generated.h"

/**
 * 
 */
UCLASS()
class RAIDEROFTIMEPROTO_API AOKey : public AObstilce
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void SetSymbolToActivate(const FSymbol& activableSymbol);
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ASymbolRule* symbolToActivate;
};
