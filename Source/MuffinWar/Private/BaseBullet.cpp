#include "BaseBullet.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"

ABaseBullet::ABaseBullet()
{
	PrimaryActorTick.bCanEverTick = true;
	Capsule = CreateDefaultSubobject<UCapsuleComponent>("Capsule");
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Projectile = CreateDefaultSubobject<UProjectileMovementComponent>("Projectile");
	Mesh->SetupAttachment(Capsule);
	bHasNotExploded = true;
}

void ABaseBullet::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseBullet::OnHit(UParticleSystem* ParticleSystem) 
{
	Explode(ParticleSystem);
}

void ABaseBullet::Explode(UParticleSystem* ParticleSystem)
{
	if (bHasNotExploded) {
		bHasNotExploded = false;
		UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(), ParticleSystem, GetActorLocation(), FRotator(0, 0, 0), FVector(1, 1, 1), true, EPSCPoolMethod::None, true
		);
	}
	FTimerHandle Handle;
	GetWorldTimerManager().SetTimer(Handle, this, &ABaseBullet::Kill, 1.0f, false, 1.0f);
}

void ABaseBullet::Kill()
{
	Destroy();
}