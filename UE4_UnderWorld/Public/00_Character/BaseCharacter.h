// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
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
	COOLTIME,
	CHARGING,
	MAX,
};
// 캐릭터 상태
UENUM(BlueprintType)
enum class ECharacterState : uint8 // Enum이름 앞에 E꼭 붙여야함
{
	NORMAL,	// 기본상태
	STUN,
	AIRBORNE
};
UENUM(BlueprintType)
enum class EAttackType : uint8
{
	NORMAL,		// 기본 공격
	KNOCKBACK,	// 넉백 공격
	AIRBORNE,	// 에어본 공격
};
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDead);

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
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Mesh)
		class USkeletalMeshComponent* WeaponSkeletalMesh;		// 무기 스켈레탈

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
	virtual float CustomTakeDamage(EAttackType type, float DamageAmount, FDamageEvent const& DamageEvent, 
		AController* EventInstigator, AActor* DamageCauser, float value);

public:
	void BeginHitStop();
	void EndHitStop();
	FTimerHandle hitstopTimerHandle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "hitstop")
		float hitstopModifier = 0.08f;			// HitStop 시간
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
		float falloffDistance = 2000.f;			// 사운드 유효 범위
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
		USoundBase* hitSound;					// 피격 사운드
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
		class UAnimMontage* hitMontage;			// 피격 몽타주
	// 몽타주 관련
	UPROPERTY(EditAnywhere, Category = "Animation")
		class UAnimMontage* AttackMontage;		// 공격 몽타주
	UPROPERTY(EditAnywhere, Category = "Animation")
		class UAnimMontage* DeadMontage;		// Dead 몽타주
	UPROPERTY(EditAnywhere, Category = "Animation")
		class UAnimMontage* StandUpMontage;		// StandUp 몽타주

	bool isDead = false;

	UPROPERTY(EditAnywhere)
		FGenericTeamId myTeam;					// TeamID

	UPROPERTY(EditAnywhere)
		bool isBoss = false;			// 보스형 캐릭터 인가

	FTimerHandle standUpTimer;			// StandUp 타이머
	FTimerHandle StunTimerHandle;		// 스턴 타이머
protected:
	EActionState actionState;
	EMoveState moveState;
	EAttackState attackState;
	ECharacterState characterState;
public:
	EActionState GetActionState() { return actionState; }
	EMoveState GetMoveState() { return moveState; }
	EAttackState GetAttackState() { return attackState; }
	ECharacterState GetCharacterState() { return characterState; }

	virtual void SetActionState(EActionState state);
	virtual void SetMoveState(EMoveState state);
	virtual void SetAttackState(EAttackState state);
	virtual void SetCharacterState(ECharacterState state);

	virtual void TakeStun(float stunTime);
	virtual void TakeAirborne(float airbornePower, float stunTime);
	UFUNCTION()
		virtual void OnDead();

	virtual void InitState();

	// 팀 설정
	virtual void SetGenericTeamId(const FGenericTeamId& TeamID);
	virtual FGenericTeamId GetGenericTeamId() const { return myTeam; }
protected:
	virtual void LaunchMesh(float zValue, float interpSpeed);
	virtual void StandUp();
public:
	FOnDead OnDeadEvent;


	bool isAirborne = false;
	bool isLevitate = false;
};
