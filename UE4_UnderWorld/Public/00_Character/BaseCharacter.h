// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

// 이동 상태
UENUM(BlueprintType)
enum class EMoveState : uint8 // Enum이름 앞에 E꼭 붙여야함
{
	NORMAL,	// 기본상태
	IDLE,	// 기본상태
	RUN,	// 뛰는상태
	JUMP,	// 점프
	FLY,	// 날고있는 상태
};
// 행동 상태
UENUM(BlueprintType)
enum class EActionState : uint8 // Enum이름 앞에 E꼭 붙여야함
{
	NORMAL,	// 기본상태
	DASH,	// 회피 중
	ATTACK,	// 공격 중
	BLOCK,	// 방어 중
	SKILL,	// 스킬 사용 중
	MAX,
};
// 행동 상태
UENUM(BlueprintType)
enum class EAttackState : uint8 // Enum이름 앞에 E꼭 붙여야함
{
	NORMAL,	// 기본상태
	ATTACK,
	CHARGING,
	MAX,
};
UCLASS()
class UE4_UNDERWORLD_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Component")
		class UStatusComponent* StatusComponent;
	UPROPERTY(VisibleAnywhere, Category = "Component")
		class USkillComponent* SkillComponent;
	UPROPERTY(VisibleAnywhere)
		class UChildActorComponent* WeaponChildActorComponent;	// 메인무기 액터 컴포넌트
	UPROPERTY(VisibleAnywhere, Category = "Component")
		class UAudioComponent* AudioComponent;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		class UWidgetComponent* HPBarWidgetComponent;			// BPBarWidget
public:
	class UStatusComponent* GetStatusComponent() { return StatusComponent; }
	class USkillComponent* GetSkillComponent() { return SkillComponent; }
	class UWidgetComponent* GetHPBarWidgetComponent() { return HPBarWidgetComponent; }
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:
	void BeginHitStop();
	void EndHitStop();
	FTimerHandle hitstopTimerHandle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "hitstop")
		float hitstopModifier = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
		float falloffDistance = 2000.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
		USoundBase* hitSound;

protected:
	EActionState actionState;
	EMoveState moveState;
	EAttackState attackState;
public:
	EActionState GetActionState() { return actionState; }
	EMoveState GetMoveState() { return moveState; }
	EAttackState GetAttackState() { return attackState; }

	virtual void SetActionState(EActionState state);
	virtual void SetMoveState(EMoveState state);
	virtual void SetAttackState(EAttackState state);

	virtual void InitState();
};
