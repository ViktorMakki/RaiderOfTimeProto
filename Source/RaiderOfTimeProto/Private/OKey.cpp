// Fill out your copyright notice in the Description page of Project Settings.


#include "OKey.h"

#include "Kismet/GameplayStatics.h"
#include "UtilsLibrary.h"

void AOKey::SetSymbolToActivate(const FSymbol& activableSymbol) {
  ASymbolRule* symbolActor = UUtilsLibrary::GetSymbolRule(GetWorld(), activableSymbol);
  if (!symbolActor) return;
  symbolToActivate = symbolActor;
  if (SymbolChanged.IsBound()) SymbolChanged.Broadcast();
}

ASymbolRule* AOKey::GetSymbolToActivate() const
{ return symbolToActivate; }
