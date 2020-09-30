// Fill out your copyright notice in the Description page of Project Settings.
#include "BaseHUD.h"
#include "MuffinWarCharacter.h"

void UBaseHUD::OnHealthFinish()
{
	AMuffinWarCharacter* Player = Cast<AMuffinWarCharacter>(GetOwningPlayer()->GetCharacter());
	if (Player && !(Player->IsDead()))
	{
		Player->Kill();
	}
}