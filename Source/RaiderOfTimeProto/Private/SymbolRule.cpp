// Fill out your copyright notice in the Description page of Project Settings.


#include "SymbolRule.h"

//TArray<AObstilce*> ASymbolRule::GetObsticles() const
//{ return obsticles; }

FSymbol ASymbolRule::GetSymbol() const
{ return symbol; }

void ASymbolRule::AddObsticle(AObstilce* obsticle) {
  if (!obsticle) return;
  obsticle->SetSymbol(symbol);
  onActivate.AddDynamic(obsticle, &AActivable::Enable);
  onDeactivate.AddDynamic(obsticle, &AActivable::Disable);
}

void ASymbolRule::Clear()
{
	if (onActivate.IsBound()) onActivate.Clear();
	if(onDeactivate.IsBound()) onDeactivate.Clear();
	onActivate = {};
	onDeactivate = {};
	//obsticles.Reset();
}

void ASymbolRule::Init(FSymbol newSymbol) { symbol = newSymbol; }
