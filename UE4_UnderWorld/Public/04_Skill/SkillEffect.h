// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameplayTagContainer.h"
#include "SkillEffect.generated.h"

// 즉시 또는 지속적으로 효과를 주는지
UENUM(Blueprintable, Blueprintable)
enum class EEffectType : uint8 // Enum이름 앞에 E꼭 붙여야함
{
	INSTANT,		// 즉시 적용
	DURATION,		// 지속 적용
};
// 효과를 줄 타겟(스텟)
UENUM(BlueprintType)
enum class EEffectTarget : uint8 // Enum이름 앞에 E꼭 붙여야함
{
	HP,				// HP
	MP,				// MP
	SP,				// Stamina
	DAMAGE,			// 대미지
	ATTACKSPEED,	// 공격속도
	SPEED,			// 이동속도
	COOLTIME		// 쿨타임
};

UCLASS(Blueprintable, Blueprintable)
class UE4_UNDERWORLD_API USkillEffect : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
		FGameplayTag effectTag;		// Tag

	UPROPERTY(EditAnywhere)
		EEffectType effectType;		// 타입(즉시 적용, 지속 적용)
	UPROPERTY(EditAnywhere)
		EEffectTarget effectTarget;	// 어디에 효과를 부여할 것인지(스텟)

	UPROPERTY(EditAnywhere)
		float effectValue;			// cost 값
	UPROPERTY(EditAnywhere)
		float effectTime;			// 지속시간(쿨타임) 값

	FTimerHandle endEffectTimer;	// 지속효과 관리 타이머
public:
	FGameplayTag& GetEffectTag() { return effectTag; }
	float GetEffectValue() const { return effectValue; }
	float GetEffectTime() const { return effectTime; }
protected:
	// Effect 적용 -> ApplyEffect에서 관리
	// 지속 효과 적용
	void ApplyDurationEffect(class ABaseCharacter* target);
	// 즉시 효과 적용
	void ApplyInstantEffect(class ABaseCharacter* target);

	// Effect 삭제
	void RemoveEffect(class ABaseCharacter* target);
public:
	// Effect를 타겟에 적용한다.
	void ApplyEffect(class ABaseCharacter* target);
	// Cost가 충분히 있는지 체크한다.
	bool CheckEffectValue(class ABaseCharacter* target);
};
