// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BaseEnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class MUFFINWAR_API ABaseEnemyAIController : public AAIController
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable)
	void ActivateAI(UBehaviorTree* Tree);
};
