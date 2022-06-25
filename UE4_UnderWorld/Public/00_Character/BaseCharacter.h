// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	AIM,	// ���� ��
	BLOCK,	// ��� ��
	SKILL,	// ��ų ��� ��
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
		class UChildActorComponent* WeaponChildActorComponent;	// ���ι��� ���� ������Ʈ
	UPROPERTY(VisibleAnywhere, Category = "Component")
		class UAudioComponent* AudioComponent;
public:
	class UStatusComponent* GetStatusComponent() { return StatusComponent; }
	class USkillComponent* GetSkillComponent() { return SkillComponent; }

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
public:
	EActionState GetActionState() { return actionState; }
	EMoveState GetMoveState() { return moveState; }

	virtual void SetActionState(EActionState state);
	virtual void SetMoveState(EMoveState state);
};
