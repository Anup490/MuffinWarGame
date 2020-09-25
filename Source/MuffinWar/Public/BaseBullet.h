#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseBullet.generated.h"

class UCapsuleComponent;
class UStaticMeshComponent;
class UProjectileMovementComponent;
class UParticleSystem;

UCLASS()
class MUFFINWAR_API ABaseBullet : public AActor
{
	GENERATED_BODY()

	void Explode(UParticleSystem* ParticleSystem);
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCapsuleComponent* Capsule;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UProjectileMovementComponent* Projectile;

	UFUNCTION(BlueprintCallable)
	void OnHit(UParticleSystem* ParticleSystem);
	
	virtual void BeginPlay() override;
public:	
	ABaseBullet();
	virtual void Tick(float DeltaTime) override;
};
