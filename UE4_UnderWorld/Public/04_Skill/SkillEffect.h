// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameplayTagContainer.h"
#include "SkillEffect.generated.h"

// ��� �Ǵ� ���������� Cost�ϴ���(��Ÿ�� / MP�Ҹ�)
UENUM(Blueprintable, Blueprintable)
enum class EEffectType : uint8 // Enum�̸� �տ� E�� �ٿ�����
{
	INSTANT,
	DURATION,
};


UCLASS()
class UE4_UNDERWORLD_API USkillEffect : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
		EEffectType effectType;

	UPROPERTY(EditAnywhere)
		FGameplayTag effectTag;
	UPROPERTY(EditAnywhere)
		float effectValue;			// cost��
	UPROPERTY(EditAnywhere)
		float effectTime;			// cooltime ��

	FTimerHandle endEffectTimer;
public:
	FGameplayTag& GetEffectTag() { return effectTag; }
	const float GetEffectValue() { return effectValue; }

protected:
	// Effect ���� -> ApplyEffect���� ����
	void ApplyDurationEffect(class ABaseCharacter* target);
	void ApplyInstantEffect(class ABaseCharacter* target);

	// Effect ����
	void RemoveEffect(class ABaseCharacter* target);
public:
	// Effect�� Ÿ�ٿ� �����Ѵ�.
	void ApplyEffect(class ABaseCharacter* target);

	// Cost�� ����� �ִ��� üũ�Ѵ�.
	bool CheckEffectValue(class ABaseCharacter* target);
};
