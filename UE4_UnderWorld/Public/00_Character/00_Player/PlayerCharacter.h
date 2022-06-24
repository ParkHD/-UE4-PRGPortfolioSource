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


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
protected:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Mesh)
		class USkeletalMeshComponent* WeaponSkeletalMesh;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Camera)
		class UCameraComponent* Camera;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Camera)
		class USpringArmComponent* SpringArm;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Camera)
		class UParticleSystemComponent* particleSys;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Camera)
		class UNiagaraComponent* niagaraSys;
	//UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	//	class UNiagaraComponent* clickNiagaraComponent;	// 클릭 Particle 관리 컴포넌트

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Component)
		class UQuickSlotComponent* QuickSlotComponent;
public:
	class UQuickSlotComponent* GetQuickSlotComponent() { return QuickSlotComponent; }
public:
	// 공격버튼 입력이 되었는가
	bool bInputComboAttack = false;

	bool bPressChargingSkill = false;
protected:
	float chargingTime = 0.f;
public:
	const float GetChargingTime() { return chargingTime; }
protected:
	UPROPERTY(EditAnywhere)
		float DashPlaySpeed = 1.f;
	UPROPERTY(EditAnywhere)
		float DashSpeed = 1000.f;

	UPROPERTY(EditAnywhere, Category = Montage)
		class UAnimMontage* AttackMontage;
	UPROPERTY(EditAnywhere, Category = Montage)
		class UAnimMontage* DashMontage;
	UPROPERTY(EditAnywhere, Category = Montage)
		class UAnimMontage* SkillMontage;
	UPROPERTY(EditAnywhere, Category = Montage)
		class UAnimMontage* SkillMontage2;
private:
	void MoveForward(float newAxisValue);
	void MoveRight(float newAxisValue);
	void LookUp(float newAxisValue);
	void Turn(float newAxisValue);


	void ReleaseMove();
	void Dash();
	void PressAttack();
	void ReleaseAttack();
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


	void PressSkillWindow();
protected:
	void TurnToCursor();
public:
	void CameraShakeDemo(float Scale);
	void InitChargingSkill();

	virtual void SetMoveState(EMoveState state) override;
	virtual void SetActionState(EActionState state) override;

private:
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UCameraShakeBase> CamSake;
};


