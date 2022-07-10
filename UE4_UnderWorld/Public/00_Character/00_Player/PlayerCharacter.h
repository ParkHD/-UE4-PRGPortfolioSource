// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "00_Character/BaseCharacter.h"
#include "PlayerCharacter.generated.h"

DECLARE_DELEGATE_OneParam(FShakeDelegate, float);

UCLASS()
class UE4_UNDERWORLD_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
protected:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Camera)
		class UCameraComponent* Camera;									// ī�޶�
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Camera)
		class USpringArmComponent* SpringArm;							// ������ ��
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Particle)
		class UParticleSystemComponent* ChargingParticleComponent;		// ��¡ ��ƼŬ

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Component)
		class UQuickSlotComponent* QuickSlotComponent;					// ������ ������Ʈ
public:
	class UQuickSlotComponent* GetQuickSlotComponent() { return QuickSlotComponent; }
public:
	// ���ݹ�ư �Է��� �Ǿ��°�
	bool bInputComboAttack = false;
	// ��ų ��¡ Ÿ��
	float chargingTime = 0.f;
public:
	const float GetChargingTime() { return chargingTime; }
protected:

	UPROPERTY(EditAnywhere, Category = Montage)
		class UAnimMontage* DashMontage;		// �뽬 ��Ÿ��

private:
	// Ű ���� �Լ�
	// �յ� �̵�
	void MoveForward(float newAxisValue);
	// ���� ������ �̵�
	void MoveRight(float newAxisValue);
	// ī�޶� ���Ʒ� �̵�
	void LookUp(float newAxisValue);
	// ī�޶� ���� ������ �̵�
	void Turn(float newAxisValue);
	// �뽬
	void Dash();
	// ����
	void PressAttack();
	// ������ ��� �Լ�
#pragma region QuickSlotKey
	void PressQuickSlot1();
	void ReleaseQuickSlot1();
	void PressQuickSlot2();
	void ReleaseQuickSlot2();
	void PressQuickSlot3();
	void ReleaseQuickSlot3();
	void PressQuickSlot4();
	void ReleaseQuickSlot4();
	void PressQuickSlot5();
	void ReleaseQuickSlot5();
	void PressQuickSlot6();
	void ReleaseQuickSlot6();
	void PressQuickSlot7();
	void ReleaseQuickSlot7();
	void PressQuickSlot8();
	void ReleaseQuickSlot8();
	void PressQuickSlot9();
	void ReleaseQuickSlot9();
	void PressQuickSlot10();
	void ReleaseQuickSlot10();
	void PressQuickSlot11();
	void ReleaseQuickSlot11();
	void PressQuickSlot12();
	void ReleaseQuickSlot12();
	void PressQuickSlot13();
	void ReleaseQuickSlot13();
	void PressQuickSlot14();
	void ReleaseQuickSlot14();
	void PressQuickSlot15();
	void ReleaseQuickSlot15();
	void PressQuickSlot16();
	void ReleaseQuickSlot16();
#pragma endregion
	// ��ų â ����
	void PressSkillWindow();

public:
	// �÷��̾� ī�޶� ����ŷ
	void CameraShakeDemo(float Scale);

	// Character State ����
	// MoveState SetUp
	virtual void SetMoveState(EMoveState state) override;
	// ActionState SetUp
	virtual void SetActionState(EActionState state) override;
	// AttackState SetUp
	virtual void SetAttackState(EAttackState state) override;

	virtual void TakeStun(float stunTime) override;
	virtual void TakeAirborne(float airbornePower, float stunTime) override;
	virtual void StandUp() override;
private:
	// ī�޶� ����ũ BP
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UCameraShakeBase> CamSake;
};

