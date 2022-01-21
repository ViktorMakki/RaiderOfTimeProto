// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Activable.generated.h"

UDELEGATE(BlueprintCallable)
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FActivate);

UDELEGATE(BlueprintCallable)
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDeactivate);

UDELEGATE(BlueprintCallable)
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEnable);

UDELEGATE(BlueprintCallable)
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDisable);

UCLASS()
class RAIDEROFTIMEPROTO_API AActivable : public AActor
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintAssignable)
	FActivate onActivate;

	UPROPERTY(BlueprintAssignable)
	FDeactivate onDeactivate;

	UPROPERTY(BlueprintAssignable)
	FEnable onEnable;

	UPROPERTY(BlueprintAssignable)
	FDisable onDisable;

	UFUNCTION(BlueprintCallable)
	void Activate();

	UFUNCTION(BlueprintCallable)
	void Deactivate();

	UFUNCTION(BlueprintCallable)
	bool IsActive() const;

	UFUNCTION(BlueprintCallable)
	void Enable();

	UFUNCTION(BlueprintCallable)
	void Disable();

	UFUNCTION(BlueprintCallable)
	bool IsEnabled() const;

private:
	bool isActive = false;
	bool isEnable = true;
};
