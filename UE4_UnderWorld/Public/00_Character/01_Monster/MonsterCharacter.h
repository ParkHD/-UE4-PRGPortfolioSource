// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "00_Character/BaseCharacter.h"
#include "MonsterCharacter.generated.h"

/**
 * 
 */
UCLASS()
class UE4_UNDERWORLD_API AMonsterCharacter : public ABaseCharacter
{
	GENERATED_BODY()
	
protected:
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
public:
	UPROPERTY(EditAnywhere) // TSubclassOf �������� �����ҋ� <>�ȿ� class�� ���ð���
		TSubclassOf<class UWidgetComponent> damageTextWidgetComponentClass;
};
