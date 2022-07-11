// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interface_InterAction.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInterface_InterAction : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class UE4_UNDERWORLD_API IInterface_InterAction
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// Å¸°ÙÀÇ ÀÌ¸§
	virtual const FText GetName() { return FText::GetEmpty(); };
	// Å¸°Ù°ú interaction ÇÔ¼ö
	virtual void InterAction(class APlayerCharacter* caller) {};
};
