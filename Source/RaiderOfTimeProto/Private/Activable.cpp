// Fill out your copyright notice in the Description page of Project Settings.


#include "Activable.h"

void AActivable::Activate()
{
	if (isEnable && !isActive) {
	  isActive = true;
      if(onActivate.IsBound()) {
		  onActivate.Broadcast(); 
      }  
	}
}
void AActivable::Deactivate()
{
  if (isActive) {
    isActive = false;
    if (onDeactivate.IsBound()) {
      onDeactivate.Broadcast();
    }
  }
}

bool AActivable::IsActive() const
{ return isActive; }

void AActivable::Enable()
{
  if (!isEnable) {
    isEnable = true;
    if (onEnable.IsBound()) {
      onEnable.Broadcast();
    }
  }
}

void AActivable::Disable()
{
  if (isEnable) {
    Deactivate();
    isEnable = false;
    if (onDisable.IsBound()) {
      onDisable.Broadcast();
    }
  }
}

bool AActivable::IsEnabled() const
{ return isEnable; }


