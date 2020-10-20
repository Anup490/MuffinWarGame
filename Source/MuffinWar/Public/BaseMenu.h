// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseMenu.generated.h"

/**
 * 
 */
class AMainGameMode;

UCLASS()
class MUFFINWAR_API UBaseMenu : public UUserWidget
{
	GENERATED_BODY()

protected:
	AMainGameMode* MainGameMode;

	UFUNCTION(BlueprintCallable)
	void OnClickStart();
public:	
	void RegisterOnStartCallback(AMainGameMode* GameMode);
};
