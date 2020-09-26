// Fill out your copyright notice in the Description page of Project Settings.
#include "BaseEnemyMuffin.h"
#include "BaseBullet.h"
#include "Components/CapsuleComponent.h"

ABaseEnemyMuffin::ABaseEnemyMuffin()
{
	PrimaryActorTick.bCanEverTick = true;
	Capsule = CreateDefaultSubobject<UCapsuleComponent>("Capsule");
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Skeletal Mesh");
	SkeletalMesh->SetupAttachment(Capsule);
	bIsDead = false;
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