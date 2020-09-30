// Fill out your copyright notice in the Description page of Project Settings.
#include "BaseEnemyMuffinAnimInstance.h"
#include "BaseEnemyMuffin.h"

UBaseEnemyMuffinAnimInstance::UBaseEnemyMuffinAnimInstance() 
{
	bIsFalling = false;
	bIsJumping = false;
	bIsAttacking = false;
	bIsDead = false;
	fSpeed = 0;
}

void UBaseEnemyMuffinAnimInstance::NativeUpdateAnimation(float fDeltaSeconds) 
{
	AActor* Actor = GetOwningActor();
	if (Actor) 
	{
		fSpeed = Actor->GetVelocity().Size();
		bIsJumping = Actor->GetVelocity().Z > 0;
		bIsFalling = Actor->GetVelocity().Z < 0;
	}
	ABaseEnemyMuffin* Muffin = Cast<ABaseEnemyMuffin>(Actor);
	if (Muffin) 
	{
		bIsDead = Muffin->IsDead();
		bIsAttacking = Muffin->ShouldAttack();
	}
}