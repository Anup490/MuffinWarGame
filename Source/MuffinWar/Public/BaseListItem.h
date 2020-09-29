// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "BaseListItem.generated.h"

/**
 * 
 */
UCLASS()
class MUFFINWAR_API UBaseListItem : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
	
};
