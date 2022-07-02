// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_Blackboard.h"
#include "Decorator_CheckDistance.generated.h"

/**
 * 
 */
UCLASS()
class UE4_UNDERWORLD_API UDecorator_CheckDistance : public UBTDecorator_Blackboard
{
	GENERATED_BODY()
protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	virtual FString GetStaticDescription() const override;
protected:
	UPROPERTY(EditAnywhere)
		float distance;				// °Å¸®
	UPROPERTY(EditAnywhere)
		bool bInversed = false;
};
