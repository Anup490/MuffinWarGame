// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BaseEnemyMuffinAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class MUFFINWAR_API UBaseEnemyMuffinAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsFalling;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsJumping;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsAttacking;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsDead;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float fSpeed;
public:
	UBaseEnemyMuffinAnimInstance();
	void NativeUpdateAnimation(float fDeltaSeconds) override;
};
