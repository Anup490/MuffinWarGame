// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseEnemyMuffin.generated.h"

UCLASS()
class MUFFINWAR_API ABaseEnemyMuffin : public ACharacter
{
	GENERATED_BODY()

	bool bIsDead;
	bool bShouldAttack;
	void Kill();
protected:
	UFUNCTION(BlueprintCallable)
	void OnHit(AActor* OtherActor);
	virtual void BeginPlay() override;
public:	
	ABaseEnemyMuffin();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	bool IsDead() const;
	bool ShouldAttack() const;
	void SetAttackFlag(bool bAttack);
};
