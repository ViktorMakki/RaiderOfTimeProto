// Fill out your copyright notice in the Description page of Project Settings.


#include "BP_Obsticle.h"

// Sets default values
ABP_Obsticle::ABP_Obsticle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void ABP_Obsticle::Activate()
{
	if (isEnable && !isActive) {
	  isActive = true;
      if(onActivate.IsBound()) {
		  onActivate.Broadcast(); 
      }  
	}
}
void ABP_Obsticle::Deactivate()
{
  if (isActive) {
    isActive = false;
    if (onDeactivate.IsBound()) {
      onDeactivate.Broadcast();
    }
  }
}

bool ABP_Obsticle::IsActive() const
{ return isActive; }

void ABP_Obsticle::Enable()
{
  if (!isEnable) {
    isEnable = true;
    if (onEnable.IsBound()) {
      onEnable.Broadcast();
    }
  }
}

void ABP_Obsticle::Disable()
{
  if (isEnable) {
    isEnable = false;
    if (onDisable.IsBound()) {
      onDisable.Broadcast();
    }
  }
}

bool ABP_Obsticle::IsEnabled() const
{ return isEnable; }


