// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemyAIController.h"

void ABaseEnemyAIController::ActivateAI(UBehaviorTree* Tree) 
{
	RunBehaviorTree(Tree);
}