// Fill out your copyright notice in the Description page of Project Settings.


#include "SymbolGenerator.h"
#include <UtilsLibrary.h>

#include "Kismet/GameplayStatics.h"

void ASymbolGenerator::Destruct()
{
}

void ASymbolGenerator::Construct()
{
  if (symbolTypes.IsEmpty()) return;
  TArray<AActor*> obsticles;
  UGameplayStatics::GetAllActorsOfClass(GetWorld(), obsticleType,obsticles);
  for (auto* actor : obsticles) {
    auto obsticle = Cast<AObstilce>(actor);
    if (obsticle) {
      const auto symbolType =symbolTypes[FMath::RandRange(0, symbolTypes.Num() - 1)];
      auto symbol = UUtilsLibrary::GetSymbolRule(GetWorld(), symbolType);
      if (!symbol) {
        symbol = ASymbolRule::Create(GetWorld(),symbolType);
      }
      if (!symbol) return;
      symbol->AddObsticle(obsticle);
    }
  }
}
