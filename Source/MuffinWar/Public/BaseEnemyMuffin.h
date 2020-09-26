// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BaseEnemyMuffin.generated.h"

UCLASS()
class MUFFINWAR_API ABaseEnemyMuffin : public APawn
{
	GENERATED_BODY()

	bool bIsDead;
	void Kill();
protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	class UCapsuleComponent* Capsule;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* SkeletalMesh;

	UFUNCTION(BlueprintCallable)
	void OnHit(AActor* OtherActor);
	virtual void BeginPlay() override;
public:	
	ABaseEnemyMuffin();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	bool IsDead() const;
};
