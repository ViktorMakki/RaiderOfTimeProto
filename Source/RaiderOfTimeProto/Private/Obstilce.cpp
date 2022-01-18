// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstilce.h"

#include "LevelGenerator.h"

void AObstilce::SetSymbol(const FSymbol& newSymbol)
{
	symbol = newSymbol;
  if (SymbolChanged.IsBound()) SymbolChanged.Broadcast();
}

FSymbol AObstilce::GetSymbol() const
{ return symbol; }

