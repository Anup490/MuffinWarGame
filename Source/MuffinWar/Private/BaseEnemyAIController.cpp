// Fill out your copyright notice in the Description page of Project Settings.
#include "BaseEnemyAIController.h"
#include "MuffinWarCharacter.h"
#include "BaseEnemyMuffin.h"
#include "Perception/AIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

#define BLACKBOARD_KEY_PLAYER "Player"
#define BLACKBOARD_KEY_ATTACK "Attack"

ABaseEnemyAIController::ABaseEnemyAIController() 
{
	Perception = CreateDefaultSubobject<UAIPerceptionComponent>("Perception");
}

void ABaseEnemyAIController::UpdateBlackBoardAttackStatus(bool bShouldAttack) {
	GetBlackboardComponent()->SetValueAsBool(BLACKBOARD_KEY_ATTACK, bShouldAttack);
}

void ABaseEnemyAIController::ActivateAI(UBehaviorTree* Tree) 
{
	RunBehaviorTree(Tree);
}

void ABaseEnemyAIController::DetectPlayer()
{
	TArray<AActor*> PerceivedActors;
	AMuffinWarCharacter* Player = 0;
	Perception->GetCurrentlyPerceivedActors(nullptr, PerceivedActors);
	for (AActor* Actor : PerceivedActors) 
	{
		Player = Cast<AMuffinWarCharacter>(Actor);
		if (Player) 
		{
			GetBlackboardComponent()->SetValueAsObject(BLACKBOARD_KEY_PLAYER, Player);
			break;
		}
	}
	if (!Player) 
	{
		GetBlackboardComponent()->SetValueAsObject(BLACKBOARD_KEY_PLAYER, nullptr);
		ABaseEnemyMuffin* Muffin = Cast<ABaseEnemyMuffin>(GetCharacter());
		if (Muffin) 
		{
			Muffin->SetAttackFlag(false);
		}
	}
}