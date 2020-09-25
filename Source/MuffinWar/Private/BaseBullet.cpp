#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "BaseBullet.h"

ABaseBullet::ABaseBullet()
{
	PrimaryActorTick.bCanEverTick = true;
	Capsule = CreateDefaultSubobject<UCapsuleComponent>("Capsule");
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Projectile = CreateDefaultSubobject<UProjectileMovementComponent>("Projectile");
	Mesh->SetupAttachment(Capsule);
	ParticleSystem = 0;
}

void ABaseBullet::SaveParticleSystem(UParticleSystem* ExplosionParticleSystem) 
{
	ParticleSystem = ExplosionParticleSystem;
}

void ABaseBullet::BeginPlay()
{
	Super::BeginPlay();
	Capsule->OnComponentHit.AddDynamic(this, &ABaseBullet::OnHit);
}

void ABaseBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseBullet::OnHit(
	UPrimitiveComponent* HitComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	FVector NormalImpulse,
	const FHitResult& Hit
) 
{
	Explode();
}

void ABaseBullet::Explode() 
{
	Destroy();
	if (ParticleSystem) {
		UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),ParticleSystem,GetActorLocation(),FRotator(0, 0, 0),FVector(1, 1, 1),true,EPSCPoolMethod::None,true
		);
	}
}