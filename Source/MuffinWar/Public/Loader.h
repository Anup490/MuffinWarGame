// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Loader.generated.h"
/**
 *
 */
UCLASS()
class MUFFINWAR_API ULoader : public UObject
{
	GENERATED_BODY()
public:
	ULoader();
	void ShowLoadingScreen();
};
