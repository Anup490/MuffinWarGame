// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlueprintBase.h"
#include "BaseAttackTask.generated.h"

/**
 * 
 */
UCLASS()
class MUFFINWAR_API UBaseAttackTask : public UBTTask_BlueprintBase
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable)
	void Attack(APawn* Pawn);
};
