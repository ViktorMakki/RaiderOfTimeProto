// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Activable.h"
#include "MazeTypes.h"
#include "GameFramework/Actor.h"
#include "BP_Obstilce.generated.h"

UCLASS()
class RAIDEROFTIMEPROTO_API ABP_Obstilce : public AActivable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABP_Obstilce();

	UFUNCTION(BlueprintCallable)
  void SetSymbol(Symbol newSymbol);

protected:
  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  Symbol symbol;
};
