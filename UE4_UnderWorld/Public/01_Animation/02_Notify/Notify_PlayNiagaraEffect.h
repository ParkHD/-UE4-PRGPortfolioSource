// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimNotify_PlayNiagaraEffect.h"
#include "Notify_PlayNiagaraEffect.generated.h"

/**
 * 
 */
UCLASS()
class UE4_UNDERWORLD_API UNotify_PlayNiagaraEffect : public UAnimNotify_PlayNiagaraEffect
{
	GENERATED_BODY()
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)override;
	virtual UFXSystemComponent* SpawnEffect(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)override;

public:
	void SetScale(FVector scale);

protected:
	UPROPERTY()
		class APlayerCharacter* owner;
};
