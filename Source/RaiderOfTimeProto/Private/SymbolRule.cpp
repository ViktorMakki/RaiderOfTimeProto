// Fill out your copyright notice in the Description page of Project Settings.


#include "SymbolRule.h"

TArray<ABP_Obstilce*> ASymbolRule::GetObsticles() const
{ return obsticles; }

void ASymbolRule::AddObsticle(ABP_Obstilce* obsticle) {
  obsticle->SetSymbol(symbol);
  obsticles.Add(obsticle);
  onActivate.AddDynamic(obsticle, &AActivable::Enable);
  onDeactivate.AddDynamic(obsticle, &AActivable::Disable);
}

void ASymbolRule::Init(Symbol newSymbol) { symbol = newSymbol; }
