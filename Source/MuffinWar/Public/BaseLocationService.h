// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlueprintBase.h"
#include "BaseLocationService.generated.h"

UCLASS()
class MUFFINWAR_API UBaseLocationService : public UBTService_BlueprintBase
{
	GENERATED_BODY()

	static constexpr float fNavigableRadius = 250;
protected:
	UFUNCTION(BlueprintCallable)
	void OnActivate(APawn* Pawn);
};
