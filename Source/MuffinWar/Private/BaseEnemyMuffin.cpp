// Fill out your copyright notice in the Description page of Project Settings.
#include "BaseEnemyMuffin.h"
#include "BaseBullet.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ABaseEnemyMuffin::ABaseEnemyMuffin()
{
	PrimaryActorTick.bCanEverTick = true;
	bIsDead = false;
	bShouldAttack = false;
}

void ABaseEnemyMuffin::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseEnemyMuffin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseEnemyMuffin::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

bool ABaseEnemyMuffin::IsDead() const
{
	return bIsDead;
}

bool ABaseEnemyMuffin::ShouldAttack() const
{
	return bShouldAttack;
}

void ABaseEnemyMuffin::SetAttackFlag(bool bAttack)
{
	bShouldAttack = bAttack;
}

void ABaseEnemyMuffin::OnHit(AActor* OtherActor)
{
	if (Cast<ABaseBullet>(OtherActor)) {
		bIsDead = true;
		FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimer(TimerHandle, this, &ABaseEnemyMuffin::Kill, 1.0f, false, 1.0f);
	}
}

void ABaseEnemyMuffin::Kill() 
{
	Destroy();
}