// Copyright Epic Games, Inc. All Rights Reserved.
#include "MuffinWarCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "BaseBullet.h"
#include "BaseEnemyMuffin.h"
#include "BaseHUD.h"
#include "MuffinWarGameMode.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

#define MATERIAL_PARAMETER "EffectColor"

AMuffinWarCharacter::AMuffinWarCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
	Scene = CreateDefaultSubobject<USceneComponent>("Scene");
	Scene->SetupAttachment(RootComponent);

	BulletClass = 0;
	InputComponent = 0;
	bIsShooting = false;
	bIsDead = false;
}

void AMuffinWarCharacter::ResumeHUDDisplay()
{
	ShowHUD();
}

void AMuffinWarCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMuffinWarCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMuffinWarCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AMuffinWarCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AMuffinWarCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AMuffinWarCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AMuffinWarCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AMuffinWarCharacter::OnResetVR);
	
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &AMuffinWarCharacter::StartShooting);
	PlayerInputComponent->BindAction("Shoot", IE_Released, this, &AMuffinWarCharacter::StopShooting);

	InputComponent = PlayerInputComponent;
}

void AMuffinWarCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AMuffinWarCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	Jump();
}

void AMuffinWarCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	StopJumping();
}

void AMuffinWarCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	if (!bIsDead)
	{
		AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		SetActorRotation(YawRotation);
	}
}

void AMuffinWarCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	if (!bIsDead)
	{
		AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
	}
}

void AMuffinWarCharacter::MoveForward(float Value)
{
	if (!bIsDead)
	{
		if ((Controller != NULL) && (Value != 0.0f))
		{
			// find out which way is forward
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			// get forward vector
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			AddMovementInput(Direction, Value);
		}
	}
}

void AMuffinWarCharacter::MoveRight(float Value)
{
	if (!bIsDead)
	{
		if ((Controller != NULL) && (Value != 0.0f))
		{
			// find out which way is right
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			// get right vector 
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
			// add movement in that direction
			AddMovementInput(Direction, Value);
		}
	}
}

void AMuffinWarCharacter::StartShooting() 
{
	bIsShooting = true;
	SpawnBullet();
}

void AMuffinWarCharacter::StopShooting() 
{
	bIsShooting = false;
}

void AMuffinWarCharacter::SaveBulletClass(UClass* Class) 
{
	BulletClass = Class;
}

void AMuffinWarCharacter::SpawnBullet() 
{
	if (BulletClass)
	{
		FVector Location = Scene->GetComponentLocation();
		FRotator Rotation = Scene->GetComponentRotation();
		GetWorld()->SpawnActor<ABaseBullet>(BulletClass, Location, Rotation, FActorSpawnParameters());
	}
}

bool AMuffinWarCharacter::IsShooting() const
{
	return bIsShooting;
}

void AMuffinWarCharacter::OnOverlapBegin(AActor* OtherActor, UPrimitiveComponent* OtherComponent)
{
	if (!bIsDead)
	{
		ABaseEnemyMuffin* Enemy = Cast<ABaseEnemyMuffin>(OtherActor);
		if (Enemy && !(Enemy->IsDead()) && Cast<UBoxComponent>(OtherComponent))
		{
			GetWorldTimerManager().SetTimer(TimerHandle, this, &AMuffinWarCharacter::OnOverlap, 1.0f, true, 0.01f);
		}
	}
}

void AMuffinWarCharacter::OnOverlapEnd(AActor* OtherActor, class UPrimitiveComponent* OtherComponent)
{
	if (Cast<ABaseEnemyMuffin>(OtherActor) && Cast<UBoxComponent>(OtherComponent))
	{
		if (GetWorldTimerManager().IsTimerActive(TimerHandle))
		{
			GetWorldTimerManager().ClearTimer(TimerHandle);
		}
	}
}

void AMuffinWarCharacter::OnPauseButtonPressed()
{
	AMuffinWarGameMode* GameMode = Cast<AMuffinWarGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameMode)
	{
		if (GameMode->IsGamePaused())
		{
			GameMode->UnpauseGame();
			ShowHUD();
		}
		else
		{
			RemoveHUD();
			GameMode->PauseGame();
		}
	}
}

void AMuffinWarCharacter::OnOverlap() 
{
	GetMesh()->SetVectorParameterValueOnMaterials(MATERIAL_PARAMETER, To4DVector(DamageColor));
	DamageMuffin();
	FTimerHandle Handle;
	GetWorldTimerManager().SetTimer(Handle, this, &AMuffinWarCharacter::RestoreColor, 0.5f);
}

void AMuffinWarCharacter::RestoreColor()
{
	GetMesh()->SetVectorParameterValueOnMaterials(MATERIAL_PARAMETER, To4DVector(OriginalColor));
}

FVector4 AMuffinWarCharacter::To4DVector(FLinearColor Color)
{
	return FVector4(Color.R, Color.G, Color.B, Color.A);
}

void AMuffinWarCharacter::Kill()
{
	if (!bIsDead)
	{
		bIsDead = true;	
		if (InputComponent)
		{
			InputComponent->ClearActionBindings();
		}
		AMuffinWarGameMode* GameMode = Cast<AMuffinWarGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		if (GameMode)
		{
			RemoveHUD();
			GameMode->OnPlayerDeath();
		}
	}
}

bool AMuffinWarCharacter::IsDead() const
{
	return bIsDead;
}