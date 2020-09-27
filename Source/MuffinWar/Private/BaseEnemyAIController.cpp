// Fill out your copyright notice in the Description page of Project Settings.
#include "BaseEnemyAIController.h"
#include "MuffinWarCharacter.h"
#include "BaseEnemyMuffin.h"
#include "Perception/AIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

#define BLACKBOARD_KEY "Player"

ABaseEnemyAIController::ABaseEnemyAIController() 
{
	Perception = CreateDefaultSubobject<UAIPerceptionComponent>("Perception");
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
	for (AActor* Actor : PerceivedActors) {
		Player = Cast<AMuffinWarCharacter>(Actor);
		if (Player) {
			GetBlackboardComponent()->SetValueAsObject(BLACKBOARD_KEY, Player);
			break;
		}
	}
	if (!Player) {
		GetBlackboardComponent()->SetValueAsObject(BLACKBOARD_KEY, nullptr);
		ABaseEnemyMuffin* Muffin = Cast<ABaseEnemyMuffin>(GetCharacter());
		if (Muffin) {
			Muffin->SetAttackFlag(false);
		}
	}
}