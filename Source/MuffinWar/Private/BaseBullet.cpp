#include "BaseBullet.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

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

void ABaseBullet::Explode()
{
	Mesh->SetVisibility(false);
	if (bHasNotExploded) {
		bHasNotExploded = false;
		UNiagaraFunctionLibrary::SpawnSystemAttached(NiagaraExplode, Capsule, NAME_None, FVector(0.f), FRotator(0.f), EAttachLocation::Type::KeepRelativeOffset, true);
	}
	FTimerHandle Handle;
	GetWorldTimerManager().SetTimer(Handle, this, &ABaseBullet::Kill, 1.0f, false, 1.0f);
}

void ABaseBullet::Kill()
{
	Destroy();
}