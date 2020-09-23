// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "MainGameMode.generated.h"

/**
 * 
 */
UCLASS()
class MUFFINWAR_API AMainGameMode : public AGameModeBase
{
	GENERATED_BODY()
protected: 
	UFUNCTION(BlueprintCallable)
	void ShowLoadingScreen(TSubclassOf<UUserWidget> UserWidgetClass);
};
