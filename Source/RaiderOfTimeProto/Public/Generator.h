// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Generator.generated.h"

UCLASS()
class RAIDEROFTIMEPROTO_API AGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGenerator();

	UFUNCTION(BlueprintCallable, CallInEditor, category = "Generator")
	virtual void Construct();

	UFUNCTION(BlueprintCallable, CallInEditor, category = "Generator")
	virtual void Destruct();
	
};
