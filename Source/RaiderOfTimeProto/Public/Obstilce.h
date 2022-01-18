// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Activable.h"
#include "MazeTypes.h"
#include "Obstilce.generated.h"

UDELEGATE(BlueprintCallable)
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSymbolChanged);

UCLASS()
class RAIDEROFTIMEPROTO_API AObstilce : public AActivable
{
	GENERATED_BODY()
	
public:	
	UFUNCTION(BlueprintCallable)
  void SetSymbol(const FSymbol& newSymbol);

	UFUNCTION(BlueprintCallable)
  FSymbol GetSymbol() const;

	UPROPERTY(BlueprintAssignable)
	FSymbolChanged SymbolChanged;

protected:

  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  FSymbol symbol;
};
