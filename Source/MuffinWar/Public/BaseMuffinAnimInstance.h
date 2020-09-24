// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BaseMuffinAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class MUFFINWAR_API UBaseMuffinAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	bool bIsFalling;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsJumping;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float fSpeed;
public:
	UBaseMuffinAnimInstance();
	void NativeUpdateAnimation(float fDeltaSeconds) override;
};
