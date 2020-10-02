// Copyright Epic Games, Inc. All Rights Reserved.

#include "MuffinWarGameMode.h"
#include "MuffinWarCharacter.h"
#include "MuffinWarGameInstance.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"

AMuffinWarGameMode::AMuffinWarGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	bIsGamePaused = false;
}

void AMuffinWarGameMode::InitializeWidgets(
	TSubclassOf<class UUserWidget> PauseMenuWidgetClass,
	TSubclassOf<class UUserWidget> LoadingScreenWidgetClass, 
	TSubclassOf<class UUserWidget> GameOverWidgetClass
)
{
	PauseMenuWidget = CreateWidget<UUserWidget>(GetWorld(), PauseMenuWidgetClass);
	LoadScreenWidget = CreateWidget<UUserWidget>(GetWorld(), LoadingScreenWidgetClass);
	GameOverWidget = CreateWidget<UUserWidget>(GetWorld(), GameOverWidgetClass);
}

void AMuffinWarGameMode::PauseGame(AMuffinWarCharacter* Player)
{
	bIsGamePaused = UGameplayStatics::SetGamePaused(GetWorld(),true);
	MuffinWarCharacter = Player;
	if (bIsGamePaused && PauseMenuWidget)
	{
		PauseMenuWidget->AddToViewport();
		UGameplayStatics::GetPlayerController(this, 0)->bShowMouseCursor = true;
	}
}

bool AMuffinWarGameMode::IsGamePaused()
{
	return bIsGamePaused;
}

void AMuffinWarGameMode::OnPlayerDeath()
{
	if (GameOverWidget)
	{
		GameOverWidget->AddToViewport();
		UGameplayStatics::GetPlayerController(this, 0)->bShowMouseCursor = true;
	}
}

void AMuffinWarGameMode::UnpauseGame()
{
	bIsGamePaused = !(UGameplayStatics::SetGamePaused(GetWorld(), false));
	if (!bIsGamePaused && PauseMenuWidget)
	{
		UGameplayStatics::GetPlayerController(this, 0)->bShowMouseCursor = false;
		PauseMenuWidget->RemoveFromViewport();
		if (MuffinWarCharacter)
		{
			MuffinWarCharacter->ResumeHUDDisplay();
		}
	}
}

void AMuffinWarGameMode::QuitGame()
{
	UMuffinWarGameInstance* MuffinGame = Cast<UMuffinWarGameInstance>(GetGameInstance());
	if (MuffinGame && LoadScreenWidget)
	{
		LoadScreenWidget->AddToViewport();
		MuffinGame->LoadMenu();
	}
}
