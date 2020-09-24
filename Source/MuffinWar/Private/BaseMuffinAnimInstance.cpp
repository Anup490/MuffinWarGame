// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseMuffinAnimInstance.h"

UBaseMuffinAnimInstance::UBaseMuffinAnimInstance() {
	bIsFalling = false;
	bIsJumping = true;
	fSpeed = 0;
}

void UBaseMuffinAnimInstance::NativeUpdateAnimation(float fDeltaSeconds) {
	AActor* Actor = GetOwningActor();
	if (Actor) {
		fSpeed = Actor->GetVelocity().Size();
		bIsJumping = Actor->GetVelocity().Z > 0;
		bIsFalling = Actor->GetVelocity().Z < 0;
	}
}
