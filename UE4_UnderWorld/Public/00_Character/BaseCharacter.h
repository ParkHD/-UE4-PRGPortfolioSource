// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

// �̵� ����
UENUM(BlueprintType)
enum class EMoveState : uint8 // Enum�̸� �տ� E�� �ٿ�����
{
	NORMAL,	// �⺻����
	IDLE,	// �⺻����
	RUN,	// �ٴ»���
	JUMP,	// ����
	FLY,	// �����ִ� ����
};
// �ൿ ����
UENUM(BlueprintType)
enum class EActionState : uint8 // Enum�̸� �տ� E�� �ٿ�����
{
	NORMAL,	// �⺻����
	DASH,	// ȸ�� ��
	ATTACK,	// ���� ��
	BLOCK,	// ��� ��
	SKILL,	// ��ų ��� ��
	MAX,
};
// �ൿ ����
UENUM(BlueprintType)
enum class EAttackState : uint8 // Enum�̸� �տ� E�� �ٿ�����
{
	NORMAL,	// �⺻����
	ATTACK,
	COOLTIME,
	CHARGING,
	MAX,
};
// ĳ���� ����
UENUM(BlueprintType)
enum class ECharacterState : uint8 // Enum�̸� �տ� E�� �ٿ�����
{
	NORMAL,	// �⺻����
	STUN,
	AIRBORNE
};
UENUM(BlueprintType)
enum class EAttackType : uint8
{
	NORMAL,		// �⺻ ����
	KNOCKBACK,	// �˹� ����
	AIRBORNE,	// ��� ����
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
		class UChildActorComponent* WeaponChildActorComponent;	// ���ι��� ���� ������Ʈ
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Mesh)
		class USkeletalMeshComponent* WeaponSkeletalMesh;		// ���� ���̷�Ż

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
		float hitstopModifier = 0.08f;			// HitStop �ð�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
		float falloffDistance = 2000.f;			// ���� ��ȿ ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
		USoundBase* hitSound;					// �ǰ� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
		class UAnimMontage* hitMontage;			// �ǰ� ��Ÿ��
	// ��Ÿ�� ����
	UPROPERTY(EditAnywhere, Category = "Animation")
		class UAnimMontage* AttackMontage;		// ���� ��Ÿ��
	UPROPERTY(EditAnywhere, Category = "Animation")
		class UAnimMontage* DeadMontage;		// Dead ��Ÿ��
	UPROPERTY(EditAnywhere, Category = "Animation")
		class UAnimMontage* StandUpMontage;		// StandUp ��Ÿ��

	bool isDead = false;

	UPROPERTY(EditAnywhere)
		FGenericTeamId myTeam;					// TeamID

	UPROPERTY(EditAnywhere)
		bool isBoss = false;			// ������ ĳ���� �ΰ�

	FTimerHandle standUpTimer;			// StandUp Ÿ�̸�
	FTimerHandle StunTimerHandle;		// ���� Ÿ�̸�
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

	// �� ����
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
