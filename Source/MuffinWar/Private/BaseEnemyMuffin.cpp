// Fill out your copyright notice in the Description page of Project Settings.
#include "BaseEnemyMuffin.h"
#include "BaseBullet.h"
#include "MuffinWarCharacter.h"
#include "BaseEnemyAIController.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/BoxComponent.h"

ABaseEnemyMuffin::ABaseEnemyMuffin()
{
	PrimaryActorTick.bCanEverTick = true;
	Box = CreateDefaultSubobject<UBoxComponent>("Box");
	Box->SetupAttachment(GetCapsuleComponent());
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
	if (Cast<ABaseBullet>(OtherActor)) 
	{
		bIsDead = true;
		FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimer(TimerHandle, this, &ABaseEnemyMuffin::Kill, 1.0f, false, 1.0f);
	}
}

void ABaseEnemyMuffin::OnOverlapBegin(AActor* OtherActor)
{
	if (Cast<AMuffinWarCharacter>(OtherActor)) {
		bShouldAttack = true;
		NotifyController();
	}
}

void ABaseEnemyMuffin::OnOverlapEnd(AActor* OtherActor)
{
	if (Cast<AMuffinWarCharacter>(OtherActor)) 
	{
		bShouldAttack = false;
		NotifyController();
	}
}

void ABaseEnemyMuffin::Kill() 
{
	Destroy();
}

void ABaseEnemyMuffin::NotifyController()
{
	ABaseEnemyAIController* AIController = Cast<ABaseEnemyAIController>(GetController());
	if (AIController)
	{
		AIController->UpdateBlackBoardAttackStatus(bShouldAttack);
	}
}