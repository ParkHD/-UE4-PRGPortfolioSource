// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameplayTagContainer.h"
#include "SkillEffect.generated.h"

// ��� �Ǵ� ���������� ȿ���� �ִ���
UENUM(Blueprintable, Blueprintable)
enum class EEffectType : uint8 // Enum�̸� �տ� E�� �ٿ�����
{
	INSTANT,		// ��� ����
	DURATION,		// ���� ����
};
// ȿ���� �� Ÿ��(����)
UENUM(BlueprintType)
enum class EEffectTarget : uint8 // Enum�̸� �տ� E�� �ٿ�����
{
	HP,				// HP
	MP,				// MP
	SP,				// Stamina
	DAMAGE,			// �����
	ATTACKSPEED,	// ���ݼӵ�
	SPEED,			// �̵��ӵ�
	COOLTIME		// ��Ÿ��
};

UCLASS(Blueprintable, Blueprintable)
class UE4_UNDERWORLD_API USkillEffect : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
		FGameplayTag effectTag;		// Tag

	UPROPERTY(EditAnywhere)
		EEffectType effectType;		// Ÿ��(��� ����, ���� ����)
	UPROPERTY(EditAnywhere)
		EEffectTarget effectTarget;	// ��� ȿ���� �ο��� ������(����)

	UPROPERTY(EditAnywhere)
		float effectValue;			// cost ��
	UPROPERTY(EditAnywhere)
		float effectTime;			// ���ӽð�(��Ÿ��) ��

	FTimerHandle endEffectTimer;	// ����ȿ�� ���� Ÿ�̸�
public:
	FGameplayTag& GetEffectTag() { return effectTag; }
	float GetEffectValue() const { return effectValue; }
	float GetEffectTime() const { return effectTime; }
protected:
	// Effect ���� -> ApplyEffect���� ����
	// ���� ȿ�� ����
	void ApplyDurationEffect(class ABaseCharacter* target);
	// ��� ȿ�� ����
	void ApplyInstantEffect(class ABaseCharacter* target);

	// Effect ����
	void RemoveEffect(class ABaseCharacter* target);
public:
	// Effect�� Ÿ�ٿ� �����Ѵ�.
	void ApplyEffect(class ABaseCharacter* target);
	// Cost�� ����� �ִ��� üũ�Ѵ�.
	bool CheckEffectValue(class ABaseCharacter* target);
};
