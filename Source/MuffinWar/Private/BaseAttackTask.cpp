// Fill out your copyright notice in the Description page of Project Settings.
#include "BaseAttackTask.h"
#include "BaseEnemyMuffin.h"

void UBaseAttackTask::Attack(APawn* Pawn)
{
	ABaseEnemyMuffin* Muffin = Cast<ABaseEnemyMuffin>(Pawn);
	if (Muffin) {
		Muffin->SetAttackFlag(true);
	}
}