// Fill out your copyright notice in the Description page of Project Settings.


#include "BP_Obstilce.h"

// Sets default values
ABP_Obstilce::ABP_Obstilce()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ABP_Obstilce::SetSymbol(Symbol newSymbol)
{ symbol = newSymbol; }

